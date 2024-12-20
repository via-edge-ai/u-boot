// SPDX-License-Identifier: GPL-2.0
/*
 * MT6357 regulator driver
 *
 * Copyright (c) 2022 BayLibre, SAS.
 * Author: Julien Masson <jmasson@baylibre.com>
 */

#include <dm.h>
#include <power/regulator.h>
#include <power/mt6357.h>
#include <power/pmic.h>

enum mt6357_regulator_type {
	MT6357_REG_TYPE_RANGE = 0,
	MT6357_REG_TYPE_TABLE,
	MT6357_REG_TYPE_FIXED,
};

struct linear_range {
	unsigned int min;
	unsigned int min_sel;
	unsigned int max_sel;
	unsigned int step;
};

struct regulator_desc {
	const char *name;
	const char *of_match;
	enum mt6357_regulator_type type;
	int id;
	unsigned int n_voltages;
	const unsigned int *volt_table;
	const struct linear_range *linear_ranges;
	int n_linear_ranges;
	unsigned int min_uV;
	unsigned int vsel_reg;
	unsigned int vsel_mask;
	unsigned int enable_reg;
	unsigned int enable_mask;
};

/*
 * MT6357 regulators' information
 *
 * @desc: standard fields of regulator description.
 * @vselon_reg: Register sections for hardware control mode of bucks
 * @vselctrl_reg: Register for controlling the buck control mode.
 * @vselctrl_mask: Mask for query buck's voltage control mode.
 */
struct mt6357_regulator_info {
	struct regulator_desc desc;
	const u32 *index_table;
	unsigned int n_table;
	u32 vsel_shift;
	u32 da_vsel_reg;
	u32 da_vsel_mask;
	u32 da_vsel_shift;
};

/* Initialize struct linear_range for regulators */
#define REGULATOR_LINEAR_RANGE(_min_uV, _min_sel, _max_sel, _step_uV)	\
{									\
	.min		= _min_uV,					\
	.min_sel	= _min_sel,					\
	.max_sel	= _max_sel,					\
	.step		= _step_uV,					\
}

#define MT6357_BUCK(match, vreg, min, max, step,			\
		    volt_ranges, vosel_reg, vosel_mask, _da_vsel_mask)	\
	[MT6357_ID_##vreg] = {						\
		.desc = {						\
			.name = #vreg,					\
			.of_match = of_match_ptr(match),		\
			.type = MT6357_REG_TYPE_RANGE,			\
			.id = MT6357_ID_##vreg,				\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.linear_ranges = volt_ranges,			\
			.n_linear_ranges = ARRAY_SIZE(volt_ranges),	\
			.vsel_reg = vosel_reg,				\
			.vsel_mask = vosel_mask,			\
			.enable_reg = MT6357_BUCK_##vreg##_CON0,	\
			.enable_mask = BIT(0),				\
		},							\
		.da_vsel_reg = MT6357_BUCK_##vreg##_DBG0,		\
		.da_vsel_mask = vosel_mask,				\
		.da_vsel_shift = 0,					\
	}

#define MT6357_LDO(match, vreg, ldo_volt_table,				\
		   ldo_index_table, enreg, vosel,			\
		   vosel_mask)						\
	[MT6357_ID_##vreg] = {						\
		.desc = {						\
			.name = #vreg,					\
			.of_match = of_match_ptr(match),		\
			.type = MT6357_REG_TYPE_TABLE,			\
			.id = MT6357_ID_##vreg,				\
			.n_voltages = ARRAY_SIZE(ldo_volt_table),	\
			.volt_table = ldo_volt_table,			\
			.vsel_reg = vosel,				\
			.vsel_mask = vosel_mask << 8,			\
			.enable_reg = enreg,				\
			.enable_mask = BIT(0),				\
		},							\
		.index_table = ldo_index_table,				\
		.n_table = ARRAY_SIZE(ldo_index_table),			\
	}

#define MT6357_LDO1(match, vreg, min, max, step, volt_ranges,		\
		    enreg, vosel, vosel_mask)				\
	[MT6357_ID_##vreg] = {						\
		.desc = {						\
			.name = #vreg,					\
			.of_match = of_match_ptr(match),		\
			.type = MT6357_REG_TYPE_RANGE,			\
			.id = MT6357_ID_##vreg,				\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.linear_ranges = volt_ranges,			\
			.n_linear_ranges = ARRAY_SIZE(volt_ranges),	\
			.vsel_reg = vosel,				\
			.vsel_mask = vosel_mask,			\
			.enable_reg = enreg,				\
			.enable_mask = BIT(0),				\
		},							\
		.da_vsel_reg = MT6357_LDO_##vreg##_DBG0,		\
		.da_vsel_mask = 0x7f,					\
		.da_vsel_shift = 8,					\
	}

#define MT6357_REG_FIXED(match, vreg, volt)			\
	[MT6357_ID_##vreg] = {					\
		.desc = {					\
			.name = #vreg,				\
			.of_match = of_match_ptr(match),	\
			.type = MT6357_REG_TYPE_FIXED,		\
			.id = MT6357_ID_##vreg,			\
			.n_voltages = 1,			\
			.enable_reg = MT6357_LDO_##vreg##_CON0,	\
			.enable_mask = BIT(0),			\
			.min_uV = volt,				\
		},						\
	}

static int range_find_value(const struct linear_range *r, unsigned int sel,
			    unsigned int *val)
{
	if (!val || sel < r->min_sel || sel > r->max_sel)
		return -EINVAL;

	*val = r->min + r->step * (sel - r->min_sel);
	return 0;
}

static int range_find_selector(const struct linear_range *r, int val,
			       unsigned int *sel)
{
	int ret = -EINVAL;
	int num_vals = r->max_sel - r->min_sel + 1;

	if (val >= r->min &&
	    val <= r->min + r->step * (num_vals - 1)) {
		if (r->step) {
			*sel = r->min_sel + ((val - r->min) / r->step);
			ret = 0;
		} else {
			*sel = r->min_sel;
			ret = 0;
		}
	}
	return ret;
}

static int mt6357_get_enable(struct udevice *dev)
{
	struct mt6357_regulator_info *info = dev_get_priv(dev);
	int ret;

	ret = pmic_reg_read(dev->parent, info->desc.enable_reg);
	if (ret < 0)
		return ret;

	return ret & info->desc.enable_mask ? true : false;
}

static int mt6357_set_enable(struct udevice *dev, bool enable)
{
	struct mt6357_regulator_info *info = dev_get_priv(dev);

	return pmic_clrsetbits(dev->parent, info->desc.enable_reg,
			       info->desc.enable_mask,
			       enable ? info->desc.enable_mask : 0);
}

static int mt6357_get_value(struct udevice *dev)
{
	struct mt6357_regulator_info *info = dev_get_priv(dev);
	unsigned int val_uV = -EINVAL;
	int selector, idx, ret;
	const u32 *pvol;

	switch (info->desc.type) {
	case MT6357_REG_TYPE_RANGE:
		selector = pmic_reg_read(dev->parent, info->da_vsel_reg);
		if (selector < 0)
			return selector;

		selector = (selector & info->da_vsel_mask) >> info->da_vsel_shift;
		ret = range_find_value(info->desc.linear_ranges, selector, &val_uV);
		if (ret < 0)
			return ret;

		break;
	case MT6357_REG_TYPE_TABLE:
		selector = pmic_reg_read(dev->parent, info->desc.vsel_reg);
		if (selector < 0)
			return selector;

		selector = (selector & info->desc.vsel_mask) >> 8;
		pvol = info->index_table;
		for (idx = 0; idx < info->desc.n_voltages; idx++) {
			if (pvol[idx] == selector) {
				val_uV = info->desc.volt_table[idx];
				break;
			}
		}
		break;
	case MT6357_REG_TYPE_FIXED:
		val_uV = info->desc.min_uV;
		break;
	default:
		val_uV = -EINVAL;
		break;
	}

	return val_uV;
}

static int mt6357_set_value(struct udevice *dev, int uvolt)
{
	struct mt6357_regulator_info *info = dev_get_priv(dev);
	int idx, ret = -EINVAL;
	int selector = 0;	/* coverity: uninitialized variable */
	const u32 *pvol;

	switch (info->desc.type) {
	case MT6357_REG_TYPE_RANGE:
		ret = range_find_selector(info->desc.linear_ranges, uvolt,
					  &selector);
		if (ret < 0)
			return ret;

		ret = pmic_clrsetbits(dev->parent, info->desc.vsel_reg,
				      info->desc.vsel_mask,
				      selector);
		break;
	case MT6357_REG_TYPE_TABLE:
		pvol = info->desc.volt_table;
		for (idx = 0; idx < info->desc.n_voltages; idx++) {
			if (pvol[idx] == uvolt) {
				selector = info->index_table[idx];
				break;
			}
		}

		ret = pmic_clrsetbits(dev->parent, info->desc.vsel_reg,
				      info->desc.vsel_mask,
				      selector << 8);
		break;
	default:
		break;
	}

	return ret;
}

static const int vxo22_voltages[] = {
	2200000,
	2400000,
};

static const int vefuse_voltages[] = {
	1200000,
	1300000,
	1500000,
	1800000,
	2800000,
	2900000,
	3000000,
	3300000,
};

static const int vcn33_voltages[] = {
	3300000,
	3400000,
	3500000,
};

static const int vcama_voltages[] = {
	2500000,
	2800000,
};

static const int vcamd_voltages[] = {
	1000000,
	1100000,
	1200000,
	1300000,
	1500000,
	1800000,
};

static const int vldo28_voltages[] = {
	2800000,
	3000000,
};

static const int vdram_voltages[] = {
	1100000,
	1200000,
};

static const int vsim_voltages[] = {
	1700000,
	1800000,
	2700000,
	3000000,
	3100000,
};

static const int vibr_voltages[] = {
	1200000,
	1300000,
	1500000,
	1800000,
	2000000,
	2800000,
	3000000,
	3300000,
};

static const int vmc_voltages[] = {
	1800000,
	2900000,
	3000000,
	3300000,
};

static const int vmch_voltages[] = {
	2900000,
	3000000,
	3300000,
};

static const int vemc_voltages[] = {
	2900000,
	3000000,
	3300000,
};

static const int vusb_voltages[] = {
	3000000,
	3100000,
};

static const int vmc_idx[] = {
	4, 10, 11, 13,
};

static const int vmch_idx[] = {
	2, 3, 5,
};

static const int vemc_idx[] = {
	2, 3, 5,
};

static const int vusb_idx[] = {
	3, 4,
};

static const int vxo22_idx[] = {
	0, 2,
};

static const int vefuse_idx[] = {
	0, 1, 2, 4, 9, 10, 11, 13,
};

static const int vcn33_idx[] = {
	1, 2, 3,
};

static const int vcama_idx[] = {
	7, 10,
};

static const int vcamd_idx[] = {
	4, 5, 6, 7, 9, 12,
};

static const int vldo28_idx[] = {
	1, 3,
};

static const int vdram_idx[] = {
	1, 2,
};

static const int vsim_idx[] = {
	3, 4, 8, 11, 12,
};

static const int vibr_idx[] = {
	0, 1, 2, 4, 5, 9, 11, 13,
};

static const struct linear_range buck_volt_range1[] = {
	REGULATOR_LINEAR_RANGE(518750, 0, 0x7f, 6250),
};

static const struct linear_range buck_volt_range2[] = {
	REGULATOR_LINEAR_RANGE(500000, 0, 0x7f, 6250),
};

static const struct linear_range buck_volt_range3[] = {
	REGULATOR_LINEAR_RANGE(500000, 0, 0x3f, 50000),
};

static const struct linear_range buck_volt_range4[] = {
	REGULATOR_LINEAR_RANGE(1200000, 0, 0x7f, 12500),
};

/* The array is indexed by id(MT6357_ID_XXX) */
static struct mt6357_regulator_info mt6357_regulators[] = {
	/* Bucks */
	MT6357_BUCK("buck-vcore", VCORE, 518750, 1312500, 6250,
		    buck_volt_range1, MT6357_BUCK_VCORE_ELR0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vproc", VPROC, 518750, 1312500, 6250,
		    buck_volt_range1, MT6357_BUCK_VPROC_ELR0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vmodem", VMODEM, 500000, 1293750, 6250,
		    buck_volt_range2, MT6357_BUCK_VMODEM_ELR0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vpa", VPA, 500000, 3650000, 50000,
		    buck_volt_range3, MT6357_BUCK_VPA_CON1, 0x3f, 0x3f),
	MT6357_BUCK("buck-vs1", VS1, 1200000, 2787500, 12500,
		    buck_volt_range4, MT6357_BUCK_VS1_ELR0, 0x7f, 0x7f),

	/* LDOs */
	MT6357_LDO("ldo-vcama", VCAMA, vcama_voltages, vcama_idx,
		   MT6357_LDO_VCAMA_CON0, MT6357_VCAMA_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vcamd", VCAMD, vcamd_voltages, vcamd_idx,
		   MT6357_LDO_VCAMD_CON0, MT6357_VCAMD_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vcn33-bt", VCN33_BT, vcn33_voltages, vcn33_idx,
		   MT6357_LDO_VCN33_CON0_0, MT6357_VCN33_ANA_CON0, 0x3),
	MT6357_LDO("ldo-vcn33-wifi", VCN33_WIFI, vcn33_voltages, vcn33_idx,
		   MT6357_LDO_VCN33_CON0_1, MT6357_VCN33_ANA_CON0, 0x3),
	MT6357_LDO("ldo-vdram", VDRAM, vdram_voltages, vdram_idx,
		   MT6357_LDO_VDRAM_CON0, MT6357_VDRAM_ELR_2, 0x3),
	MT6357_LDO("ldo-vefuse", VEFUSE, vefuse_voltages, vefuse_idx,
		   MT6357_LDO_VEFUSE_CON0, MT6357_VEFUSE_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vemc", VEMC, vemc_voltages, vemc_idx,
		   MT6357_LDO_VEMC_CON0, MT6357_VEMC_ANA_CON0, 0x7),
	MT6357_LDO("ldo-vibr", VIBR, vibr_voltages, vibr_idx,
		   MT6357_LDO_VIBR_CON0, MT6357_VIBR_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vldo28", VLDO28, vldo28_voltages, vldo28_idx,
		   MT6357_LDO_VLDO28_CON0_0, MT6357_VLDO28_ANA_CON0, 0x3),
	MT6357_LDO("ldo-vmc", VMC, vmc_voltages, vmc_idx,
		   MT6357_LDO_VMC_CON0, MT6357_VMC_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vmch", VMCH, vmch_voltages, vmch_idx,
		   MT6357_LDO_VMCH_CON0, MT6357_VMCH_ANA_CON0, 0x7),
	MT6357_LDO("ldo-vsim1", VSIM1, vsim_voltages, vsim_idx,
		   MT6357_LDO_VSIM1_CON0, MT6357_VSIM1_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vsim2", VSIM2, vsim_voltages, vsim_idx,
		   MT6357_LDO_VSIM2_CON0, MT6357_VSIM2_ANA_CON0, 0xf),
	MT6357_LDO("ldo-vusb33", VUSB33, vusb_voltages, vusb_idx,
		   MT6357_LDO_VUSB33_CON0_0, MT6357_VUSB33_ANA_CON0, 0x7),
	MT6357_LDO("ldo-vxo22", VXO22, vxo22_voltages, vxo22_idx,
		   MT6357_LDO_VXO22_CON0, MT6357_VXO22_ANA_CON0, 0x3),

	MT6357_LDO1("ldo-vsram-proc", VSRAM_PROC, 518750, 1312500, 6250,
		    buck_volt_range1, MT6357_LDO_VSRAM_PROC_CON0,
		    MT6357_LDO_VSRAM_CON0, 0x7f),
	MT6357_LDO1("ldo-vsram-others", VSRAM_OTHERS, 518750, 1312500, 6250,
		    buck_volt_range1, MT6357_LDO_VSRAM_OTHERS_CON0,
		    MT6357_LDO_VSRAM_CON1, 0x7f),

	MT6357_REG_FIXED("ldo-vaud28", VAUD28, 2800000),
	MT6357_REG_FIXED("ldo-vaux18", VAUX18, 1800000),
	MT6357_REG_FIXED("ldo-vcamio18", VCAMIO, 1800000),
	MT6357_REG_FIXED("ldo-vcn18", VCN18, 1800000),
	MT6357_REG_FIXED("ldo-vcn28", VCN28, 2800000),
	MT6357_REG_FIXED("ldo-vfe28", VFE28, 2800000),
	MT6357_REG_FIXED("ldo-vio18", VIO18, 1800000),
	MT6357_REG_FIXED("ldo-vio28", VIO28, 2800000),
	MT6357_REG_FIXED("ldo-vrf12", VRF12, 1200000),
	MT6357_REG_FIXED("ldo-vrf18", VRF18, 1800000),
};

static int mt6357_regulator_probe(struct udevice *dev)
{
	struct mt6357_regulator_info *priv = dev_get_priv(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(mt6357_regulators); i++) {
		if (!strcmp(dev->name, mt6357_regulators[i].desc.of_match)) {
			*priv = mt6357_regulators[i];
			return 0;
		}
	}

	return -ENOENT;
}

static const struct dm_regulator_ops mt6357_regulator_ops = {
	.get_value  = mt6357_get_value,
	.set_value  = mt6357_set_value,
	.get_enable = mt6357_get_enable,
	.set_enable = mt6357_set_enable,
};

U_BOOT_DRIVER(mt6357_regulator) = {
	.name	   = MT6357_REGULATOR_DRIVER,
	.id	   = UCLASS_REGULATOR,
	.ops	   = &mt6357_regulator_ops,
	.probe	   = mt6357_regulator_probe,
	.priv_auto = sizeof(struct mt6357_regulator_info),
};

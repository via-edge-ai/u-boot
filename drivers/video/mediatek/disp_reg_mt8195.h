/* SPDX-License-Identifier: GPL-2.0
 *
 * MediaTek mt8195 display register base
 *
 * Copyright (c) 2023 MediaTek Inc.
 * Author: Tommy Chen <tommyyl.chen@mediatek.com>
 */

#ifndef __MT_DISP_REG
#define __MT_DISP_REG

/* Global Config */
#define TOPCKGEN_BASE					(0x10000000)
#define APMIXEDSYS_BASE					(0x1000c000)

/* TOPCKGEN registers */
#define CLK_CFG_UPDATE_1				(TOPCKGEN_BASE + 0x8)
#define HF_FEDP_CK_UPDATE				BIT(8)
#define CLK_CFG_10_SET					(TOPCKGEN_BASE + 0x9c)
#define CLK_CFG_10_CLR					(TOPCKGEN_BASE + 0xa0)
#define CLK_HF_FEDP_CK_SEL_MASK				0xf
#define CLK_HF_FEDP_CK_SEL_SHIFT			0
#define PDN_HF_FEDP_CK					BIT(7)

/* TVPDLL Control Registers */
#define TVDPLL_CON0					(APMIXEDSYS_BASE + 0x0a0)
#define RG_TVDPLL1_CK_EN				BIT(20)
#define RG_TVDPLL1_BW					BIT(16) | BIT(15) | BIT(14)
#define RG_TVDPLL1_SDM_FRA_EN				BIT(13)
#define RG_TVDPLL1_GLITCH_FREE_EN			BIT(12)
#define RG_TVDPLL1_EN					BIT(9)
#define RG_TVDPLL1_CK_VPROC_EN				BIT(8)

#define TVDPLL_CON2					(APMIXEDSYS_BASE + 0x0a8)
#define RG_TVDPLL1_POSDIV_SHIFT				24
#define	RG_TVDPLL1_POSDIV_DIV_1				0x0
#define	RG_TVDPLL1_POSDIV_DIV_2				0x1
#define	RG_TVDPLL1_POSDIV_DIV_4				0x2
#define	RG_TVDPLL1_POSDIV_DIV_8				0x3
#define	RG_TVDPLL1_POSDIV_DIV_16			0x4
#define RG_TVDPLL1_SDM_PCW_MASK				0x3fffff

#define TVDPLL_CON4					(APMIXEDSYS_BASE + 0x0b0)
#define RG_TVDPLL1_SDM_ISO_EN				BIT(1)
#define RG_TVDPLL1_SDM_PWR_ON				BIT(0)

#define CLOCK_594MHZ					594000000
#define CLOCK_297MHZ					(CLOCK_594MHZ >> 1)
#define CLOCK_148MHZ					(CLOCK_594MHZ >> 2)
#define CLOCK_74MHZ					(CLOCK_594MHZ >> 3)
#define CLOCK_2376MHZ					(CLOCK_594MHZ << 2)
#define CLOCK_1MHZ					1000000
#define CLOCK_26MHZ_FACTOR				26

/* MIPI TX Config */
#define MIPI_TX0_CONFIG_BASE				(0x11c80000)
#define MIPI_TX1_CONFIG_BASE				(0x11c90000)

/* VDOSYS */
#define OVL0_BASE					(0x1c000000)
#define DISP_WDMA0_BASE					(0x1c001000)
#define DISP_RDMA0_BASE					(0x1c002000)
#define COLOR0_BASE					(0x1c003000)
#define CCORR0_BASE					(0x1c004000)
#define DISP_AAL0_BASE					(0x1c005000)
#define DISP_GAMMA0_BASE				(0x1c006000)
#define DITHER0_BASE					(0x1c007000)
#define DSI0_BASE					(0x1c008000)
#define DISP_DSC_BASE					(0x1c009000)
#define OVL1_BASE					(0x1c00a000)
#define DISP_WDMA1_BASE					(0x1c00b000)
#define DISP_RDMA1_BASE					(0x1c00c000)
#define COLOR1_BASE					(0x1c00d000)
#define CCORR1_BASE					(0x1c00e000)
#define DISP_AAL1_BASE					(0x1c00f000)
#define DISP_GAMMA1_BASE				(0x1c010000)
#define DITHER1_BASE					(0x1c011000)
#define DSI1_BASE					(0x1c012000)
#define DISP_MERGE0_BASE				(0x1c014000)
#define DISP_DP_INTF_BASE				(0x1c015000)
#define MM_MUTEX_BASE					(0x1c016000)
#define VDOSYS0_CONFIG_BASE				(0x1c01a000)
#define VDOSYS1_CONFIG_BASE				(0x1c100000)

/* VPPSYS0 */
#define VPP0_CONFIG_BASE				(0x14000000)
/* No Use Display Module */
#define DISP_SPLIT0_BASE				(0xffffffff)
#define DISP_POSTMASK0_BASE				(0xffffffff)

/* APB Module disp_dpi */
#define DPI0_BASE					(0x1c111000)
#define DPI1_BASE					(0x1c112000)
/* APB Module edp/dp */
#define DP_INTF0_BASE					(0x1c015000)
#define EDPTX_BASE					(0x1c500000)
#define DP_INTF1_BASE					(0x1c113000)
#define DPTX_BASE					(0x1c600000)

/* APB Module disp_pwm */
#define DISP_PWM0_BASE					(0x1100e000)
#define DISP_PWM1_BASE					(0x1100f000)

/* APB Module smi_larb0 */
#define SMI_LARB0_BASE					(0x1c018000)

/* APB Module smi_larb5 */
#define SMI_LARB1_BASE					(0x1c019000)

/* APB Module smi_larb */
#define SMI_LARB2_BASE					(0x16010000)

/* APB Module smi */
#define SMI_COMMON_BASE					(0x1c01b000)

/* APB Module smi_subcom0 */
#define SMI_SUBCOM0_BASE				(0x14120000)

/* APB Module smi_subcom1 */
#define SMI_SUBCOM1_BASE				(0x14121000)

/* APB Module smi_larb */
#define SMI_LARB5_BASE					(0x1502f000)

#define DISP_INDEX_OFFSET				(OVL1_BASE - OVL0_BASE)
#define DISP_RDMA_INDEX_OFFSET				(DISP_RDMA1_BASE - DISP_RDMA0_BASE)
#define DISP_COLOR_INDEX_OFFSET				(COLOR1_BASE - COLOR0_BASE)
#define DISP_CCORR_INDEX_OFFSET				(CCORR1_BASE - CCORR0_BASE)
#define DISP_GAMMA_INDEX_OFFSET				(DISP_GAMMA1_BASE - DISP_GAMMA0_BASE)
#define DISP_AAL_INDEX_OFFSET				(DISP_AAL1_BASE - DISP_AAL0_BASE)
#define DISP_DITHER_INDEX_OFFSET			(DITHER1_BASE - DITHER0_BASE)
#define DISP_MDP_AAL_INDEX_OFFSET			(0)
#define DISP_POSTMASK_INDEX_OFFSET			(0)

#define DISPSYS_OVL0_BASE				OVL0_BASE
#define DISPSYS_OVL1_BASE				OVL1_BASE
#define DISPSYS_RDMA0_BASE				DISP_RDMA0_BASE
#define DISPSYS_RDMA1_BASE				DISP_RDMA1_BASE
#define DISPSYS_WDMA0_BASE				DISP_WDMA0_BASE
#define DISPSYS_WDMA1_BASE				DISP_WDMA1_BASE
#define DISPSYS_COLOR0_BASE				COLOR0_BASE
#define DISPSYS_COLOR1_BASE				COLOR1_BASE
#define DISPSYS_AAL0_BASE				DISP_AAL0_BASE
#define DISPSYS_AAL1_BASE				DISP_AAL1_BASE
#define DISPSYS_GAMMA0_BASE				DISP_GAMMA0_BASE
#define DISPSYS_GAMMA1_BASE				DISP_GAMMA1_BASE
#define DISPSYS_DSI0_BASE				DSI0_BASE
#define DISPSYS_DSI1_BASE				DSI1_BASE
#define DISPSYS_MIPITX0_BASE				MIPI_TX0_CONFIG_BASE
#define DISPSYS_MIPITX1_BASE				MIPI_TX1_CONFIG_BASE
#define DISPSYS_DITHER0_BASE				DITHER0_BASE
#define DISPSYS_DITHER1_BASE				DITHER1_BASE
#define DISPSYS_POSTMASK0_BASE				DISP_POSTMASK0_BASE
#define DISPSYS_SPLIT0_BASE				DISP_SPLIT0_BASE
#define DISPSYS_PWM0_BASE				DISP_PWM0_BASE
#define DISPSYS_MUTEX_BASE				MM_MUTEX_BASE
#define DISPSYS_SMI_LARB0_BASE				SMI_LARB0_BASE
#define DISPSYS_SMI_LARB1_BASE				SMI_LARB1_BASE
#define DISPSYS_SMI_COMMON_BASE				SMI_COMMON_BASE
#define DISPSYS_SMI_SUBCOM0_BASE			SMI_SUBCOM0_BASE
#define DISPSYS_SMI_SUBCOM1_BASE			SMI_SUBCOM1_BASE
#define DISPSYS_CCORR0_BASE				CCORR0_BASE
#define DISPSYS_CCORR1_BASE				CCORR1_BASE
#define DISPSYS_MERGE0_BASE				DISP_MERGE0_BASE
#define DISPSYS_DSC_BASE				DISP_DSC_BASE
#define DISPSYS_DP_INTF_BASE				DISP_DP_INTF_BASE

/* OVL */
#define DISP_REG_OVL_EN					(DISPSYS_OVL0_BASE + 0x00c)
#define DISP_REG_OVL_EN_ENABLE				BIT(0)

#define DISP_REG_OVL_ROI_SIZE				(DISPSYS_OVL0_BASE + 0x020)
#define DISP_REG_OVL_ROI_HEIGHT_SHIFT			16
#define DISP_REG_OVL_ROI_HEIGHT_MASK			0x1fff
#define DISP_REG_OVL_ROI_WIDTH_MASK			0x1fff

#define DISP_REG_OVL_DATAPATH_CON			(DISPSYS_OVL0_BASE + 0x024)
#define DISP_REG_OVL_DATAPATH_OUTPUT_CLAMP		BIT(26)
#define DISP_REG_OVL_DATAPATH_LAYER_SMI_ID_EN		BIT(0)

#define DISP_REG_OVL_ROI_BGCLR				(DISPSYS_OVL0_BASE + 0x028)
#define DISP_REG_OVL_ROI_BGCLR_ALPHA			0xff000000

#define DISP_REG_OVL_SRC_CON				(DISPSYS_OVL0_BASE + 0x02c)
#define DISP_REG_OVL_SRC_CON_L0_EN			BIT(0)

#define DISP_REG_OVL_L0_CON				(DISPSYS_OVL0_BASE + 0x030)
#define DISP_REG_OVL_L0_CON_CLRFMT_MAN			BIT(23)
#define DISP_REG_OVL_L0_CON_CLRFMT_BGR565		0x0
#define DISP_REG_OVL_L0_CON_CLRFMT_BGR888		0x1
#define DISP_REG_OVL_L0_CON_CLRFMT_BGRA8888		0x2
#define DISP_REG_OVL_L0_CON_CLRFMT_SHIFT		12
#define DISP_REG_OVL_L0_CON_CLRFMT_ALPHA_VALUE		0xff

#define DISP_REG_OVL_L0_SRC_SIZE			(DISPSYS_OVL0_BASE + 0x038)
#define DISP_REG_OVL_L0_SRC_HEIGHT_SHIFT		16
#define DISP_REG_OVL_L0_SRC_HEIGHT_MASK			0x1fff
#define DISP_REG_OVL_L0_SRC_WIDTH_MASK			0x1fff

#define DISP_REG_OVL_L0_OFFSET				(DISPSYS_OVL0_BASE + 0x03c)
#define DISP_REG_OVL_L0_PITCH				(DISPSYS_OVL0_BASE + 0x044)
#define DISP_REG_OVL_RDMA0_CTRL				(DISPSYS_OVL0_BASE + 0x0c0)
#define DISP_REG_OVL_RDMA0_EN				BIT(0)

#define DISP_REG_OVL_L0_ADDR				(DISPSYS_OVL0_BASE + 0xf40)

/* AAL */
#define DISP_AAL_EN					(DISPSYS_AAL0_BASE + 0x000)
#define DISP_AAL_EN_ENABLE				BIT(0)

#define DISP_AAL_RESET					(DISPSYS_AAL0_BASE + 0x004)
#define DISP_AAL_INTEN					(DISPSYS_AAL0_BASE + 0x008)
#define DISP_AAL_INTSTA					(DISPSYS_AAL0_BASE + 0x00c)
#define DISP_AAL_STATUS					(DISPSYS_AAL0_BASE + 0x010)
#define DISP_AAL_CFG					(DISPSYS_AAL0_BASE + 0x020)
#define DISP_AAL_CF_8BIT_SWITCH				BIT(8)
#define DISP_AAL_CF_CG_DISABLE				BIT(4)
#define DISP_AAL_CF_RELAY_MODE				BIT(0)

#define DISP_AAL_IN_CNT					(DISPSYS_AAL0_BASE + 0x024)
#define DISP_AAL_OUT_CNT				(DISPSYS_AAL0_BASE + 0x028)
#define DISP_AAL_CHKSUM					(DISPSYS_AAL0_BASE + 0x02c)
#define DISP_AAL_SIZE					(DISPSYS_AAL0_BASE + 0x030)
#define DISP_AAL_SHADOW_CTL				(DISPSYS_AAL0_BASE + 0x0B0)
#define DISP_AAL_DUMMY_REG				(DISPSYS_AAL0_BASE + 0x0c0)
#define DISP_AAL_CFG_MAIN				(DISPSYS_AAL0_BASE + 0x200)
#define DISP_AAL_MAX_HIST_CONFIG_00			(DISPSYS_AAL0_BASE + 0x204)
#define DISP_AAL_CABC_00				(DISPSYS_AAL0_BASE + 0x20c)
#define DISP_AAL_CABC_02				(DISPSYS_AAL0_BASE + 0x214)
#define DISP_AAL_CABC_04				(DISPSYS_AAL0_BASE + 0x21c)
#define DISP_AAL_STATUS_00				(DISPSYS_AAL0_BASE + 0x224)
/* 00 ~ 32: max histogram */
#define DISP_AAL_STATUS_32				(DISPSYS_AAL0_BASE + 0x2a4)
/* bit 8: dre_gain_force_en */
#define DISP_AAL_DRE_GAIN_FILTER_00			(DISPSYS_AAL0_BASE + 0x354)
#define DISP_AAL_DRE_FLT_FORCE(idx)			(DISPSYS_AAL0_BASE + 0x358 + (idx) * 4)
#define DISP_AAL_DRE_CRV_CAL_00				(DISPSYS_AAL0_BASE + 0x344)
#define DISP_AAL_DRE_MAPPING_00				(DISPSYS_AAL0_BASE + 0x3b0)
#define DISP_AAL_CABC_GAINLMT_TBL(idx)			(DISPSYS_AAL0_BASE + 0x40c + (idx) * 4)
#define DISP_AAL_OUTPUT_SIZE				(DISPSYS_AAL0_BASE + 0x4d8)
#define DISP_AAL_OUTPUT_WIDTH_SHIFT			16
#define DISP_AAL_OUTPUT_WIDTH_MASK			0x1fff
#define DISP_AAL_OUTPUT_HEIGHT_MASK			0x1fff


/* PWM */
#define DISP_PWM_EN_OFF					(0x00)
#define DISP_PWM_COMMIT_OFF				(0x0c)
#define DISP_PWM_CON_0_OFF				(0x18)
#define DISP_PWM_CON_1_OFF				(0x1c)

/* COLOR */
#define DISP_COLOR_CFG_MAIN				(DISPSYS_COLOR0_BASE + 0x400)
#define DISP_COLOR_CFG_MAIN_8BIT_SWITCH			BIT(25)
#define DISP_COLOR_CFG_MAIN_ALL_BYPASS			BIT(7)

#define DISP_COLOR_PXL_CNT_MAIN				(DISPSYS_COLOR0_BASE + 0x404)
#define DISP_COLOR_LINE_CNT_MAIN			(DISPSYS_COLOR0_BASE + 0x408)
#define DISP_COLOR_START				(DISPSYS_COLOR0_BASE + 0xc00)
#define DISP_COLOR_START_DISP_8BIT_YUV			BIT(4)
#define DISP_COLOR_START_DISP_COLOR_OUT_SEL		BIT(1)
#define DISP_COLOR_START_DISP_COLOR_START		BIT(0)

#define DISP_COLOR_INTERNAL_IP_WIDTH			(DISPSYS_COLOR0_BASE + 0xc50)
#define DISP_COLOR_INTERNAL_IP_WIDTH_MASK		0x1fff

#define DISP_COLOR_INTERNAL_IP_HEIGHT			(DISPSYS_COLOR0_BASE + 0xc54)
#define DISP_COLOR_INTERNAL_IP_HEIGHT_MASK		0x1fff

#define DISP_COLOR_CM1_EN				(DISPSYS_COLOR0_BASE + 0xc60)
#define DISP_COLOR_CM1_EN_ENABLE			0x0

#define DISP_COLOR_CM2_EN				(DISPSYS_COLOR0_BASE + 0xca0)
#define DISP_COLOR_CM2_EN_ENABLE			0x0

#define DISP_REG_COLOR_SHADOW_CTRL			(DISPSYS_COLOR0_BASE + 0xcb0)

/* CCORR */
#define DISP_REG_CCORR_EN				(DISPSYS_CCORR0_BASE + 0x000)
#define DISP_REG_CCORR_EN_ENABLE			BIT(0)

#define DISP_REG_CCORR_CFG				(DISPSYS_CCORR0_BASE + 0x020)
#define DISP_REG_CCORR_CFG_8BIT				BIT(10)
#define DISP_REG_CCORR_CFG_RELAY_MODE_DISABLE		BIT(0)

#define DISP_REG_CCORR_IN_CNT				(DISPSYS_CCORR0_BASE + 0x024)
#define DISP_REG_CCORR_OUT_CNT				(DISPSYS_CCORR0_BASE + 0x028)
#define DISP_REG_CCORR_SIZE				(DISPSYS_CCORR0_BASE + 0x030)
#define DISP_REG_CCORR_SIZE_WIDTH_SHIFT			16
#define DISP_REG_CCORR_SIZE_WIDTH_MASK			0x1fff
#define DISP_REG_CCORR_SIZE_HEIGHT_MASK			0x1fff

#define DISP_REG_CCORR_SHADOW_CTRL			(DISPSYS_CCORR0_BASE + 0x0a0)

/* GAMMA */
#define DISP_REG_GAMMA_EN				(DISPSYS_GAMMA0_BASE + 0x000)
#define DISP_REG_GAMMA_EN_ENABLE			BIT(0)

#define DISP_REG_GAMMA_CFG				(DISPSYS_GAMMA0_BASE + 0x020)
#define DISP_REG_GAMMA_CFG_STALL_CG_ON			BIT(8)
#define DISP_REG_GAMMA_RELAY_MODE_ENABLE		BIT(0)

#define DISP_REG_GAMMA_SIZE				(DISPSYS_GAMMA0_BASE + 0x030)
#define DISP_REG_GAMMA_WIDTH_SHIFT			16
#define DISP_REG_GAMMA_WIDTH_MASK			0x1fff
#define DISP_REG_GAMMA_HEIGHT_MASK			0x1fff

#define DISP_REG_GAMMA_INPUT_COUNT			(DISPSYS_GAMMA0_BASE + 0x024)
#define DISP_REG_GAMMA_OUTPUT_COUNT			(DISPSYS_GAMMA0_BASE + 0x028)
#define DISP_REG_GAMMA_SHADOW_CTRL			(DISPSYS_GAMMA0_BASE + 0x034)

/* Dither */
#define DISP_REG_DITHER_EN				(DISPSYS_DITHER0_BASE + 0x000)
#define DISP_REG_DITHER_EN_ENABLE			BIT(0)

#define DISP_REG_DITHER_RESET				(DISPSYS_DITHER0_BASE + 0x004)
#define DISP_REG_DITHER_INTEN				(DISPSYS_DITHER0_BASE + 0x008)
#define DISP_REG_DITHER_INTSTA				(DISPSYS_DITHER0_BASE + 0x00c)
#define DISP_REG_DITHER_STATUS				(DISPSYS_DITHER0_BASE + 0x010)
#define DISP_REG_DITHER_CFG				(DISPSYS_DITHER0_BASE + 0x020)
#define DISP_REG_DITHER_CFG_RELAY_MODE_ENABLE		BIT(0)

#define DISP_REG_DITHER_IN_CNT				(DISPSYS_DITHER0_BASE + 0x024)
#define DISP_REG_DITHER_OUT_CNT				(DISPSYS_DITHER0_BASE + 0x028)
#define DISP_REG_DITHER_CHKSUM				(DISPSYS_DITHER0_BASE + 0x02c)
#define DISP_REG_DITHER_SIZE				(DISPSYS_DITHER0_BASE + 0x030)
#define DISP_REG_DITHER_SIZE_WIDTH_SHIFT		16
#define DISP_REG_DITHER_SIZE_WIDTH_MASK			0x1fff
#define DISP_REG_DITHER_SIZE_HEIGHT_MASK		0x1fff

#define DISP_REG_DITHER_DUMMY_REG			(DISPSYS_DITHER0_BASE + 0x0c0)
#define DISP_REG_DITHER_0				(DISPSYS_DITHER0_BASE + 0x100)
#define DISP_REG_DITHER_5				(DISPSYS_DITHER0_BASE + 0x114)
#define DISP_REG_DITHER_5_SHORT_LINE_LENGTH_VALUE	0x0

#define DISP_REG_DITHER_6				(DISPSYS_DITHER0_BASE + 0x118)
#define DISP_REG_DITHER_6_FPHASE_R			BIT(13)
#define DISP_REG_DITHER_6_FPHASE_EN			BIT(12)
#define DISP_REG_DITHER_6_RDITHER_EN			BIT(2)

#define DISP_REG_DITHER_7				(DISPSYS_DITHER0_BASE + 0x11c)
#define DISP_REG_DITHER_8				(DISPSYS_DITHER0_BASE + 0x120)
#define DISP_REG_DITHER_9				(DISPSYS_DITHER0_BASE + 0x124)
#define DISP_REG_DITHER_10				(DISPSYS_DITHER0_BASE + 0x128)
#define DISP_REG_DITHER_11				(DISPSYS_DITHER0_BASE + 0x12c)
#define DISP_REG_DITHER_12				(DISPSYS_DITHER0_BASE + 0x130)
#define DISP_REG_DITHER_13				(DISPSYS_DITHER0_BASE + 0x134)
#define DISP_REG_DITHER_14				(DISPSYS_DITHER0_BASE + 0x138)
#define DISP_REG_DITHER_14_TESTPIN_INPUT_ENABLE		0x0

#define DISP_REG_DITHER_15				(DISPSYS_DITHER0_BASE + 0x13c)
#define DISP_REG_DITHER_16				(DISPSYS_DITHER0_BASE + 0x140)
#define DISP_REG_DITHER_17				(DISPSYS_DITHER0_BASE + 0x144)

/* RDMA */
#define DISP_REG_RDMA_INT_ENABLE			(DISPSYS_RDMA0_BASE + 0x000)
#define DISP_REG_RDMA_INT_STATUS			(DISPSYS_RDMA0_BASE + 0x004)
#define DISP_REG_RDMA_GLOBAL_CON			(DISPSYS_RDMA0_BASE + 0x010)
#define DISP_REG_RDMA_GLOBAL_CON_ENABLE			BIT(0)

#define DISP_REG_RDMA_SIZE_CON_0			(DISPSYS_RDMA0_BASE + 0x014)
#define DISP_REG_RDMA_SIZE_WIDTH_MASK			0x1fff

#define DISP_REG_RDMA_SIZE_CON_1			(DISPSYS_RDMA0_BASE + 0x018)
#define DISP_REG_RDMA_SIZE_HEIGHT_MASK			0x1fff

#define DISP_REG_RDMA_TARGET_LINE			(DISPSYS_RDMA0_BASE + 0x01c)
#define DISP_REG_RDMA_MEM_CON				(DISPSYS_RDMA0_BASE + 0x024)
#define DISP_REG_RDMA_MEM_SRC_PITCH			(DISPSYS_RDMA0_BASE + 0x02c)
#define DISP_REG_RDMA_MEM_GMC_SETTING_0			(DISPSYS_RDMA0_BASE + 0x030)
#define DISP_REG_RDMA_MEM_GMC_FORCE_PREULTRA BIT(31)
#define DISP_REG_RDMA_MEM_GMC_PREULTRA_THRESH_HIGH_SHIFT 16
#define DISP_REG_RDMA_MEM_GMC_PREULTRA_THRESH_HIGH	0x5ed
#define DISP_REG_RDMA_MEM_GMC_PREULTRA_THRESH_LOW	0x5b2

#define DISP_REG_RDMA_MEM_GMC_SETTING_1			(DISPSYS_RDMA0_BASE + 0x034)
#define DISP_REG_RDMA_MEM_GMC_BLOCK_ULTRA BIT(31)
#define DISP_REG_RDMA_MEM_GMC_ULTRA_THRESH_HIGH_SHIFT	16
#define DISP_REG_RDMA_MEM_GMC_ULTRA_THRESH_HIGH		0x5b2
#define DISP_REG_RDMA_MEM_GMC_ULTRA_THRESH_LOW		0x53e

#define DISP_REG_RDMA_MEM_SLOW_CON			(DISPSYS_RDMA0_BASE + 0x038)
#define DISP_REG_RDMA_MEM_GMC_SETTING_2			(DISPSYS_RDMA0_BASE + 0x03c)
#define DISP_REG_RDMA_MEM_GMC_ISSUE_REQ_THRESHOLD	0x100

#define DISP_REG_RDMA_FIFO_CON				(DISPSYS_RDMA0_BASE + 0x040)
#define DISP_REG_RDMA_FIFO_PSEUDO_SIZE			0x780
#define DISP_REG_RDMA_FIFO_PSEUDO_SIZE_SHIFT		16

#define DISP_REG_RDMA_FIFO_LOG				(DISPSYS_RDMA0_BASE + 0x044)
#define DISP_REG_RDMA_C00				(DISPSYS_RDMA0_BASE + 0x054)
#define DISP_REG_RDMA_C01				(DISPSYS_RDMA0_BASE + 0x058)
#define DISP_REG_RDMA_C02				(DISPSYS_RDMA0_BASE + 0x05c)
#define DISP_REG_RDMA_C10				(DISPSYS_RDMA0_BASE + 0x060)
#define DISP_REG_RDMA_C11				(DISPSYS_RDMA0_BASE + 0x064)
#define DISP_REG_RDMA_C12				(DISPSYS_RDMA0_BASE + 0x068)
#define DISP_REG_RDMA_C20				(DISPSYS_RDMA0_BASE + 0x06c)
#define DISP_REG_RDMA_C21				(DISPSYS_RDMA0_BASE + 0x070)
#define DISP_REG_RDMA_C22				(DISPSYS_RDMA0_BASE + 0x074)
#define DISP_REG_RDMA_PRE_ADD_0				(DISPSYS_RDMA0_BASE + 0x078)
#define DISP_REG_RDMA_PRE_ADD_1				(DISPSYS_RDMA0_BASE + 0x07c)
#define DISP_REG_RDMA_PRE_ADD_2				(DISPSYS_RDMA0_BASE + 0x080)
#define DISP_REG_RDMA_POST_ADD_0			(DISPSYS_RDMA0_BASE + 0x084)
#define DISP_REG_RDMA_POST_ADD_1			(DISPSYS_RDMA0_BASE + 0x088)
#define DISP_REG_RDMA_POST_ADD_2			(DISPSYS_RDMA0_BASE + 0x08c)
#define DISP_REG_RDMA_DUMMY				(DISPSYS_RDMA0_BASE + 0x090)
#define DISP_REG_RDMA_DEBUG_OUT_SEL			(DISPSYS_RDMA0_BASE + 0x094)
#define DISP_REG_RDMA_MEM_START_ADDR			(DISPSYS_RDMA0_BASE + 0xf00)
#define DISP_REG_RDMA_BG_CON_0				(DISPSYS_RDMA0_BASE + 0x0a0)
#define DISP_REG_RDMA_BG_CON_1				(DISPSYS_RDMA0_BASE + 0x0a4)
#define DISP_REG_RDMA_THRESHOLD_FOR_SODI		(DISPSYS_RDMA0_BASE + 0x0a8)
#define DISP_REG_RDMA_THRESHOLD_FOR_DVFS		(DISPSYS_RDMA0_BASE + 0x0ac)
#define DISP_REG_RDMA_SRAM_SEL				(DISPSYS_RDMA0_BASE + 0x0b0)
#define DISP_REG_RDMA_SRAM_SEL_DISP_RDMA_SRAM		0x0
#define DISP_REG_RDMA_STALL_CG_CON			(DISPSYS_RDMA0_BASE + 0x0b4)
#define DISP_REG_RDMA_STALL_CG_CON_ENG_CG		0x0

#define DISP_REG_RDMA_SHADOW_UPDATE			(DISPSYS_RDMA0_BASE + 0x0bc)
#define DISP_REG_RDMA_DRAM_CON				(DISPSYS_RDMA0_BASE + 0x0c0)
#define DISP_REG_RDMA_DVFS_SETTING_PRE			(DISPSYS_RDMA0_BASE + 0x0d0)
#define DISP_REG_RDMA_DVFS_SETTING_ULTRA		(DISPSYS_RDMA0_BASE + 0x0d4)
#define DISP_REG_RDMA_LEAVE_DRS_SETTING			(DISPSYS_RDMA0_BASE + 0x0d8)
#define DISP_REG_RDMA_ENTER_DRS_SETTING			(DISPSYS_RDMA0_BASE + 0x0dc)
#define DISP_REG_RDMA_MEM_GMC_SETTING_3			(DISPSYS_RDMA0_BASE + 0x0e8)
#define DISP_REG_RDMA_IN_P_CNT				(DISPSYS_RDMA0_BASE + 0x120)
#define DISP_REG_RDMA_IN_LINE_CNT			(DISPSYS_RDMA0_BASE + 0x124)
#define DISP_REG_RDMA_OUT_P_CNT				(DISPSYS_RDMA0_BASE + 0x128)
#define DISP_REG_RDMA_OUT_LINE_CNT			(DISPSYS_RDMA0_BASE + 0x12c)
#define DISP_REG_RDMA_DBG_OUT				(DISPSYS_RDMA0_BASE + 0x100)
#define DISP_REG_RDMA_ULTRA_SRC_SEL			(DISPSYS_RDMA0_BASE + 0x1a0)
#define DISP_REG_RDMA_GREQ_NUM_SEL			(DISPSYS_RDMA0_BASE + 0x1a4)
#define DISP_REG_RDMA_GREQ_URG_NUM_SEL			(DISPSYS_RDMA0_BASE + 0x1a8)

/* MERGE */
#define DISP_MERGE_ENABLE				(DISPSYS_MERGE0_BASE + 0x000)
#define DISP_MERGE_ENABLE_ENABLE			BIT(0)

#define DISP_MERGE_RESET				(DISPSYS_MERGE0_BASE + 0x004)
#define DISP_MERGE_CFG_0				(DISPSYS_MERGE0_BASE + 0x010)
#define DISP_MERGE_CFG_1				(DISPSYS_MERGE0_BASE + 0x014)
#define DISP_MERGE_CFG_4				(DISPSYS_MERGE0_BASE + 0x020)
#define DISP_MERGE_CFG_5				(DISPSYS_MERGE0_BASE + 0x024)
#define DISP_MERGE_CFG_8				(DISPSYS_MERGE0_BASE + 0x030)
#define DISP_MERGE_CFG_9				(DISPSYS_MERGE0_BASE + 0x034)
#define DISP_MERGE_CFG_10				(DISPSYS_MERGE0_BASE + 0x038)
#define DISP_MERGE_CFG_11				(DISPSYS_MERGE0_BASE + 0x03c)
#define DISP_MERGE_CFG_12				(DISPSYS_MERGE0_BASE + 0x040)
#define DISP_MERGE_CFG_12_CFG_10_10_1PI_2PO_BUF_MODE	0x6

#define DISP_MERGE_CFG_13				(DISPSYS_MERGE0_BASE + 0x044)
#define DISP_MERGE_CFG_14				(DISPSYS_MERGE0_BASE + 0x048)
#define DISP_MERGE_CFG_15				(DISPSYS_MERGE0_BASE + 0x04c)
#define DISP_MERGE_CFG_17				(DISPSYS_MERGE0_BASE + 0x054)
#define DISP_MERGE_CFG_18				(DISPSYS_MERGE0_BASE + 0x058)
#define DISP_MERGE_CFG_19				(DISPSYS_MERGE0_BASE + 0x05c)
#define DISP_MERGE_CFG_20				(DISPSYS_MERGE0_BASE + 0x060)
#define DISP_MERGE_CFG_21				(DISPSYS_MERGE0_BASE + 0x064)
#define DISP_MERGE_CFG_22				(DISPSYS_MERGE0_BASE + 0x068)
#define DISP_MERGE_CFG_23				(DISPSYS_MERGE0_BASE + 0x06c)
#define DISP_MERGE_CFG_24				(DISPSYS_MERGE0_BASE + 0x070)
#define DISP_MERGE_CFG_25				(DISPSYS_MERGE0_BASE + 0x074)
#define DISP_MERGE_CFG_26				(DISPSYS_MERGE0_BASE + 0x078)
#define DISP_MERGE_CFG_27				(DISPSYS_MERGE0_BASE + 0x07c)
#define DISP_MERGE_CFG_28				(DISPSYS_MERGE0_BASE + 0x080)
#define DISP_MERGE_CFG_29				(DISPSYS_MERGE0_BASE + 0x084)
#define DISP_MERGE_CFG_HEIGHT_SHIFT			16

/* SMI_LARB0 */
#define SMI_LARB0_OVL0_NON_SEC_CON			(SMI_LARB0_BASE + 0x388)
#define  SMI_LARB0_OVL0_NON_SEC_CON_DISABLE_MMU		0x0

/* Config */
#define MT8195_VDO0_OVL_GLOBAL_CG_CLR0			(VDOSYS0_CONFIG_BASE + 0x108)
#define MT8195_VDO0_OVL_GLOBAL_CG_B26_DISP_MUTEX0	BIT(26)
#define MT8195_VDO0_OVL_GLOBAL_CG_B25_DP_INTF0		BIT(25)
#define MT8195_VDO0_OVL_GLOBAL_CG_B24_VPP_MERGE0	BIT(24)
#define MT8195_VDO0_OVL_GLOBAL_CG_B23_DSC_WRAP0		BIT(23)
#define MT8195_VDO0_OVL_GLOBAL_CG_B21_DSI0		BIT(21)
#define MT8195_VDO0_OVL_GLOBAL_CG_B19_DISP_RDMA0	BIT(19)
#define MT8195_VDO0_OVL_GLOBAL_CG_B10_DISP_DITHER0	BIT(10)
#define MT8195_VDO0_OVL_GLOBAL_CG_B8_DISP_GAMMA0	BIT(8)
#define MT8195_VDO0_OVL_GLOBAL_CG_B6_DISP_AAL0		BIT(6)
#define MT8195_VDO0_OVL_GLOBAL_CG_B4_DISP_CCORR0	BIT(4)
#define MT8195_VDO0_OVL_GLOBAL_CG_B2_DISP_COLOR0	BIT(2)
#define MT8195_VDO0_OVL_GLOBAL_CG_B0_DISP_OVL0		BIT(0)

#define MT8195_VDO0_OVL_GLOBAL_CG_CLR1			(VDOSYS0_CONFIG_BASE + 0x118)
#define MT8195_VDO0_OVL_GLOBAL_CG_B15_SMI_RSI		BIT(15)
#define MT8195_VDO0_OVL_GLOBAL_CG_B14_SMI_LARM		BIT(14)
#define MT8195_VDO0_OVL_GLOBAL_CG_B13_SMI_IOMMU		BIT(13)
#define MT8195_VDO0_OVL_GLOBAL_CG_B12_SMI_EMI		BIT(12)
#define MT8195_VDO0_OVL_GLOBAL_CG_B11_SMI_COMMON	BIT(11)
#define MT8195_VDO0_OVL_GLOBAL_CG_B10_SMI_GALS		BIT(10)
#define MT8195_VDO0_OVL_GLOBAL_CG_B0_DISP_DL_ASYNC0	BIT(0)

#define MT8195_VDO0_OVL_GLOBAL0_SW0_RST_B		(VDOSYS0_CONFIG_BASE + 0x190)
#define MT8195_VDO0_OVL_MOUT_EN				(VDOSYS0_CONFIG_BASE + 0xf14)
#define MT8195_VDO0_OVL_MOUT_EN_OUTPUT_TO_RDMA0		BIT(0)

#define MT8195_VDO0_SEL_IN				(VDOSYS0_CONFIG_BASE + 0xf34)
#define MT8195_VDO0_DSI0_IN_SHIFT			16
#define MT8195_VDO0_DSI0_IN_FROM_DSC_WRAP0		BIT(0)
#define MT8195_VDO0_DP_INTF0_IN_SHIFT			12
#define MT8195_VDO0_DP_INTF0_IN_FROM_VPP_MERGE		BIT(0)

#define MT8195_VDO0_SEL_OUT				(VDOSYS0_CONFIG_BASE + 0xf38)
#define MT8195_DISP_DITHER0_OUT_SHIFT			0
#define MT8195_DISP_DITHER0_OUT_TO_DSI0			BIT(0)
#define MT8195_DSC_WRAP0_OUT_SHIFT			12
#define MT8195_DSC_WRAP0_OUT_TO_VPP_MERGE0		BIT(1)
#define MT8195_DSC_VPP_MERGE0_OUT_SHIFT			8
#define MT8195_DSC_VPP_MERGE0_TO_DP_INTF0		BIT(0)

/* Mutex */
#define DISP_MUTEX0_EN					(MM_MUTEX_BASE + 0x020)
#define DISP_MUTEX0_EN_ENABLE				BIT(0)

#define DISP_MUTEX0_CTL					(MM_MUTEX_BASE + 0x02c)
#define DISP_MUTEX0_MUTEX_EOF_SHIFT			7
#define DISP_MUTEX0_MUTEX_EOF_DSI0			BIT(0)
#define DISP_MUTEX0_MUTEX_EOF_DP_INTF_EDP		0x3
#define DISP_MUTEX0_MUTEX_SOF_DSI0			BIT(0)
#define DISP_MUTEX0_MUTEX_SOF_DP_INTF_EDP		0x3

#define DISP_MUTEX0_MOD0				(MM_MUTEX_BASE + 0x030)
#define DISP_MUTEX0_VDO0_DP_INTF0			BIT(21)
#define DISP_MUTEX0_VDO0_VPP_MERGE0			BIT(20)
#define DISP_MUTEX0_VDO0_DSC_WRAP0			BIT(9)
#define DISP_MUTEX0_VDO0_DSI0				BIT(8)
#define DISP_MUTEX0_VDO0_DISP_DITHER0			BIT(7)
#define DISP_MUTEX0_VDO0_DISP_GAMMA0			BIT(6)
#define DISP_MUTEX0_VDO0_DISP_AAL0			BIT(5)
#define DISP_MUTEX0_VDO0_DISP_CCORR0			BIT(4)
#define DISP_MUTEX0_VDO0_DISP_COLOR0			BIT(3)
#define DISP_MUTEX0_VDO0_DISP_RDMA0			BIT(2)
#define DISP_MUTEX0_VDO0_DISP_OVL0			BIT(0)

#endif /*__MT_DISP_REG*/

// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 MediaTek Inc.
 * Author: Chris-qj Chen <chris-qj.chen@mediatek.com>
 */

#include <common.h>
#include <dm.h>
#include <asm/io.h>
#include <dt-bindings/clock/mt8195-clk.h>
#include <linux/bitops.h>

#include "clk-mtk.h"

static const struct mtk_gate_regs infra_ao0_cg_regs = {
	.set_ofs = 0x80,
	.clr_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const struct mtk_gate_regs infra_ao1_cg_regs = {
	.set_ofs = 0x88,
	.clr_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const struct mtk_gate_regs infra_ao2_cg_regs = {
	.set_ofs = 0xa4,
	.clr_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const struct mtk_gate_regs infra_ao3_cg_regs = {
	.set_ofs = 0xc0,
	.clr_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

static const struct mtk_gate_regs infra_ao4_cg_regs = {
	.set_ofs = 0xe0,
	.clr_ofs = 0xe4,
	.sta_ofs = 0xe8,
};

#define GATE_INFRA_AO0(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &infra_ao0_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_INFRA_AO1(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &infra_ao1_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_INFRA_AO2(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &infra_ao2_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_INFRA_AO3(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &infra_ao3_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_INFRA_AO4(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &infra_ao4_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

static const struct mtk_gate infra_ao_clks[] = {
	/* INFRA_AO0 */
	GATE_INFRA_AO0(CLK_INFRA_AO_PMIC_TMR, CLK_TOP_PWRAP_ULPOSC, 0),
	GATE_INFRA_AO0(CLK_INFRA_AO_PMIC_AP, CLK_TOP_PWRAP_ULPOSC, 1),
	GATE_INFRA_AO0(CLK_INFRA_AO_PMIC_MD, CLK_TOP_PWRAP_ULPOSC, 2),
	GATE_INFRA_AO0(CLK_INFRA_AO_PMIC_CONN, CLK_TOP_PWRAP_ULPOSC, 3),
	GATE_INFRA_AO0(CLK_INFRA_AO_SEJ, CLK_TOP_AXI, 5),
	GATE_INFRA_AO0(CLK_INFRA_AO_APXGPT, CLK_TOP_AXI, 6),
	GATE_INFRA_AO0(CLK_INFRA_AO_GCE, CLK_TOP_AXI, 8),
	GATE_INFRA_AO0(CLK_INFRA_AO_GCE2, CLK_TOP_AXI, 9),
	GATE_INFRA_AO0(CLK_INFRA_AO_THERM, CLK_TOP_AXI, 10),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM_H, CLK_TOP_AXI, 15),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM1, CLK_TOP_PWM, 16),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM2, CLK_TOP_PWM, 17),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM3, CLK_TOP_PWM, 18),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM4, CLK_TOP_PWM, 19),
	GATE_INFRA_AO0(CLK_INFRA_AO_PWM, CLK_TOP_PWM, 21),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART0, CLK_TOP_UART, 22),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART1, CLK_TOP_UART, 23),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART2, CLK_TOP_UART, 24),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART3, CLK_TOP_UART, 25),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART4, CLK_TOP_UART, 26),
	GATE_INFRA_AO0(CLK_INFRA_AO_GCE_26M, CLK_TOP_CLK26M, 27),
	GATE_INFRA_AO0(CLK_INFRA_AO_CQ_DMA_FPC, CLK_TOP_FPC, 28),
	GATE_INFRA_AO0(CLK_INFRA_AO_UART5, CLK_TOP_UART, 29),
	/* INFRA_AO1 */
	GATE_INFRA_AO1(CLK_INFRA_AO_HDMI_26M, CLK_TOP_CLK26M, 0),
	GATE_INFRA_AO1(CLK_INFRA_AO_SPI0, CLK_TOP_SPI, 1),
	GATE_INFRA_AO1(CLK_INFRA_AO_MSDC0, CLK_TOP_MSDC50_0_HCLK, 2),
	GATE_INFRA_AO1(CLK_INFRA_AO_MSDC1, CLK_TOP_AXI, 4),
	GATE_INFRA_AO1(CLK_INFRA_AO_CG1_MSDC2, CLK_TOP_AXI, 5),
	GATE_INFRA_AO1(CLK_INFRA_AO_MSDC0_SRC, CLK_TOP_MSDC50_0, 6),
	GATE_INFRA_AO1(CLK_INFRA_AO_TRNG, CLK_TOP_AXI, 9),
	GATE_INFRA_AO1(CLK_INFRA_AO_AUXADC, CLK_TOP_CLK26M, 10),
	GATE_INFRA_AO1(CLK_INFRA_AO_CPUM, CLK_TOP_AXI, 11),
	GATE_INFRA_AO1(CLK_INFRA_AO_HDMI_32K, CLK_TOP_CLK32K, 12),
	GATE_INFRA_AO1(CLK_INFRA_AO_CEC_66M_H, CLK_TOP_AXI, 13),
	GATE_INFRA_AO1(CLK_INFRA_AO_IRRX, CLK_TOP_AXI, 14),
	GATE_INFRA_AO1(CLK_INFRA_AO_PCIE_TL_26M, CLK_TOP_CLK26M, 15),
	GATE_INFRA_AO1(CLK_INFRA_AO_MSDC1_SRC, CLK_TOP_MSDC30_1, 16),
	GATE_INFRA_AO1(CLK_INFRA_AO_CEC_66M_B, CLK_TOP_AXI, 17),
	GATE_INFRA_AO1(CLK_INFRA_AO_PCIE_TL_96M, CLK_TOP_TL, 18),
	GATE_INFRA_AO1(CLK_INFRA_AO_DEVICE_APC, CLK_TOP_AXI, 20),
	GATE_INFRA_AO1(CLK_INFRA_AO_ECC_66M_H, CLK_TOP_AXI, 23),
	GATE_INFRA_AO1(CLK_INFRA_AO_DEBUGSYS, CLK_TOP_AXI, 24),
	GATE_INFRA_AO1(CLK_INFRA_AO_AUDIO, CLK_TOP_AXI, 25),
	GATE_INFRA_AO1(CLK_INFRA_AO_PCIE_TL_32K, CLK_TOP_CLK32K, 26),
	GATE_INFRA_AO1(CLK_INFRA_AO_DBG_TRACE, CLK_TOP_AXI, 29),
	GATE_INFRA_AO1(CLK_INFRA_AO_DRAMC_F26M, CLK_TOP_CLK26M, 31),
	/* INFRA_AO2 */
	GATE_INFRA_AO2(CLK_INFRA_AO_IRTX, CLK_TOP_AXI, 0),
	GATE_INFRA_AO2(CLK_INFRA_AO_SSUSB, CLK_TOP_USB_TOP, 1),
	GATE_INFRA_AO2(CLK_INFRA_AO_DISP_PWM, CLK_TOP_DISP_PWM0, 2),
	GATE_INFRA_AO2(CLK_INFRA_AO_CLDMA_B, CLK_TOP_AXI, 3),
	GATE_INFRA_AO2(CLK_INFRA_AO_AUDIO_26M_B, CLK_TOP_CLK26M, 4),
	GATE_INFRA_AO2(CLK_INFRA_AO_SPI1, CLK_TOP_SPI, 6),
	GATE_INFRA_AO2(CLK_INFRA_AO_SPI2, CLK_TOP_SPI, 9),
	GATE_INFRA_AO2(CLK_INFRA_AO_SPI3, CLK_TOP_SPI, 10),
	GATE_INFRA_AO2(CLK_INFRA_AO_UNIPRO_SYS, CLK_TOP_UFS, 11),
	GATE_INFRA_AO2(CLK_INFRA_AO_UNIPRO_TICK, CLK_TOP_UFS_TICK1US, 12),
	GATE_INFRA_AO2(CLK_INFRA_AO_UFS_MP_SAP_B, CLK_TOP_UFS_MP_SAP_CFG, 13),
	GATE_INFRA_AO2(CLK_INFRA_AO_PWRMCU, CLK_TOP_PWRMCU, 15),
	GATE_INFRA_AO2(CLK_INFRA_AO_PWRMCU_BUS_H, CLK_TOP_AXI, 17),
	GATE_INFRA_AO2(CLK_INFRA_AO_APDMA_B, CLK_TOP_AXI, 18),
	GATE_INFRA_AO2(CLK_INFRA_AO_SPI4, CLK_TOP_SPI, 25),
	GATE_INFRA_AO2(CLK_INFRA_AO_SPI5, CLK_TOP_SPI, 26),
	GATE_INFRA_AO2(CLK_INFRA_AO_CQ_DMA, CLK_TOP_AXI, 27),
	GATE_INFRA_AO2(CLK_INFRA_AO_AES_UFSFDE, CLK_TOP_UFS, 28),
	GATE_INFRA_AO2(CLK_INFRA_AO_AES, CLK_TOP_AES_UFSFDE, 29),
	GATE_INFRA_AO2(CLK_INFRA_AO_UFS_TICK, CLK_TOP_UFS_TICK1US, 30),
	GATE_INFRA_AO2(CLK_INFRA_AO_SSUSB_XHCI, CLK_TOP_SSUSB_XHCI, 31),
	/* INFRA_AO3 */
	GATE_INFRA_AO3(CLK_INFRA_AO_MSDC0_SELF, CLK_TOP_MSDC50_0, 0),
	GATE_INFRA_AO3(CLK_INFRA_AO_MSDC1_SELF, CLK_TOP_MSDC50_0, 1),
	GATE_INFRA_AO3(CLK_INFRA_AO_MSDC2_SELF, CLK_TOP_MSDC50_0, 2),
	GATE_INFRA_AO3(CLK_INFRA_AO_I2S_DMA, CLK_TOP_AXI, 5),
	GATE_INFRA_AO3(CLK_INFRA_AO_AP_MSDC0, CLK_TOP_MSDC50_0, 7),
	GATE_INFRA_AO3(CLK_INFRA_AO_MD_MSDC0, CLK_TOP_MSDC50_0, 8),
	GATE_INFRA_AO3(CLK_INFRA_AO_CG3_MSDC2, CLK_TOP_MSDC30_2, 9),
	GATE_INFRA_AO3(CLK_INFRA_AO_GCPU, CLK_TOP_GCPU, 10),
	GATE_INFRA_AO3(CLK_INFRA_AO_PCIE_PERI_26M, CLK_TOP_CLK26M, 15),
	GATE_INFRA_AO3(CLK_INFRA_AO_GCPU_66M_B, CLK_TOP_AXI, 16),
	GATE_INFRA_AO3(CLK_INFRA_AO_GCPU_133M_B, CLK_TOP_AXI, 17),
	GATE_INFRA_AO3(CLK_INFRA_AO_DISP_PWM1, CLK_TOP_DISP_PWM1, 20),
	GATE_INFRA_AO3(CLK_INFRA_AO_FBIST2FPC, CLK_TOP_MSDC50_0, 24),
	GATE_INFRA_AO3(CLK_INFRA_AO_DEVICE_APC_SYNC, CLK_TOP_AXI, 25),
	GATE_INFRA_AO3(CLK_INFRA_AO_PCIE_P1_PERI_26M, CLK_TOP_CLK26M, 26),
	GATE_INFRA_AO3(CLK_INFRA_AO_SPIS0, CLK_TOP_SPIS, 28),
	GATE_INFRA_AO3(CLK_INFRA_AO_SPIS1, CLK_TOP_SPIS, 29),
	/* INFRA_AO4 */
	GATE_INFRA_AO4(CLK_INFRA_AO_133M_M_PERI, CLK_TOP_AXI, 0),
	GATE_INFRA_AO4(CLK_INFRA_AO_66M_M_PERI, CLK_TOP_AXI, 1),
	GATE_INFRA_AO4(CLK_INFRA_AO_PCIE_PL_P_250M_P0, CLK_TOP_PEXTP_PIPE, 7),
	GATE_INFRA_AO4(CLK_INFRA_AO_PCIE_PL_P_250M_P1,
		       CLK_TOP_SSUSB_U3PHY_P1_P_P0, 8),
	GATE_INFRA_AO4(CLK_INFRA_AO_PCIE_P1_TL_96M, CLK_TOP_TL_P1, 17),
	GATE_INFRA_AO4(CLK_INFRA_AO_AES_MSDCFDE_0P, CLK_TOP_AES_MSDCFDE, 18),
	GATE_INFRA_AO4(CLK_INFRA_AO_UFS_TX_SYMBOL, CLK_TOP_UFS_TX_SYMBOL, 22),
	GATE_INFRA_AO4(CLK_INFRA_AO_UFS_RX_SYMBOL, CLK_TOP_UFS_RX_SYMBOL, 23),
	GATE_INFRA_AO4(CLK_INFRA_AO_UFS_RX_SYMBOL1, CLK_TOP_UFS_RX_SYMBOL1, 24),
	GATE_INFRA_AO4(CLK_INFRA_AO_PERI_UFS_MEM_SUB, CLK_TOP_MEM_466M, 31),
};

extern const struct mtk_clk_tree mt8195_clk_tree;
static int mt8195_infra_ao_probe(struct udevice *dev)
{
	return mtk_common_clk_gate_init(dev, &mt8195_clk_tree, infra_ao_clks);
}

static const struct udevice_id of_match_clk_mt8195_infra_ao[] = {
	{ .compatible = "mediatek,mt8195-infracfg_ao", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_infra_ao) = {
	.name = "mt8195-infra_ao",
	.id = UCLASS_CLK,
	.of_match = of_match_clk_mt8195_infra_ao,
	.probe = mt8195_infra_ao_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};

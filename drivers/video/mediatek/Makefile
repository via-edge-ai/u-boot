# SPDX-License-Identifier: GPL-2.0
#
# Copyright (c) 2023 MediaTek Inc.
#
# Author: Tommy Chen <tommyyl.chen@mediatek.com>

ifeq ($(CONFIG_VIDEO_MEDIATEK),y)
	ifeq ($(CONFIG_TARGET_MT8365),y)
		obj-y += \
			mtk_ddp.o \
			mtk_dpi.o \
			mtk_disp_mutex.o \
			mtk_disp_rdma.o \
			mtk_smi.o
	else
		obj-y += mtk_dsi_common.o \
			mtk_dp_common.o \
			mtk_dp_intf.o \
			mtk_dp_hal.o
		obj-$(CONFIG_TARGET_MT8188) += \
			dsi_mt8188.o \
			dp_mt8188.o \
			vdosys_mt8188.o \
			disp_pwm_mt8188.o
		obj-$(CONFIG_TARGET_MT8195) += \
			dsi_mt8195.o \
			dp_mt8195.o \
			vdosys_mt8195.o \
			disp_pwm_mt8195.o
		obj-$(CONFIG_TARGET_MT8370) += \
			dsi_mt8188.o \
			dp_mt8188.o \
			vdosys_mt8188.o \
			disp_pwm_mt8188.o
	endif
endif

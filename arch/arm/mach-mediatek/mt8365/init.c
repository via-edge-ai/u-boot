// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 MediaTek Inc.
 * Copyright (C) 2021 BayLibre, SAS
 * Author: Fabien Parent <fparent@baylibre.com>
 */

#include <common.h>
#include <fdtdec.h>
#include <asm/armv8/mmu.h>
#include <asm/global_data.h>
#include <asm/system.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	int ret;

	ret = fdtdec_setup_memory_banksize();
	if (ret)
		return ret;

	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = gd->ram_base;
	gd->bd->bi_dram[0].size = gd->ram_size;

	return 0;
}

int mtk_pll_early_init(void)
{
	return 0;
}

int mtk_soc_early_init(void)
{
	return 0;
}

#ifndef CONFIG_SYSRESET
void reset_cpu(ulong addr)
{
	psci_system_reset();
}
#endif

int print_cpuinfo(void)
{
	u32 part = mediatek_sip_part_name();

	if (part)
		printf("CPU:   MediaTek MT%.4x\n", part);
	else
		printf("CPU:   MediaTek MT8365\n");
	return 0;
}

static struct mm_region mt8365_mem_map[] = {
	{
		/* DDR */
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0xC0000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) | PTE_BLOCK_OUTER_SHARE,
	}, {
		.virt = 0x00000000UL,
		.phys = 0x00000000UL,
		.size = 0x20000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		0,
	}
};

struct mm_region *mem_map = mt8365_mem_map;

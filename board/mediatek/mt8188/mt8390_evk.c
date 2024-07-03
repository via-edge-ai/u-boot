// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2022 MediaTek Inc.
 * Author: Chris-QJ Chen <chris-qj.chen@mediatek.com>
 */

#include <common.h>
#include <dm.h>
#include <efi_loader.h>
#include <net.h>
#include <asm/io.h>
#include <linux/kernel.h>
#include <linux/arm-smccc.h>
#include <iot_ab.h>

#define MT8390_UPDATABLE_IMAGES	5

#if CONFIG_IS_ENABLED(EFI_HAVE_CAPSULE_SUPPORT)
static struct efi_fw_image fw_images[MT8390_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
#if defined(CONFIG_MEDIATEK_IOT_AB_BOOT_SUPPORT)
	.dfu_string = "mmc 0=bl2.img raw 0x0 0x2000 mmcpart 1;"
			"fip.bin part 0 %d;firmware.vfat part 0 %d;u-boot-env.bin raw 0x0 0x2000 mmcpart 2",
#else
	.dfu_string = "mmc 0=bl2.img raw 0x0 0x2000 mmcpart 1;"
			"fip.bin part 0 1;firmware.vfat part 0 3;u-boot-env.bin raw 0x0 0x2000 mmcpart 2",
#endif
	.images = fw_images,
};

u8 num_image_type_guids = MT8390_UPDATABLE_IMAGES;
#endif

#if defined(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) && defined(CONFIG_EFI_PARTITION)
enum mt8390_updatable_images {
	MT8390_BL2_IMAGE = 1,
	MT8390_FIP_IMAGE,
	MT8390_FW_IMAGE,
	MT8390_ENV_IMAGE,
	MT8390_FIT_IMAGE,
};

static bool board_is_genio_700_evk(void)
{
	return CONFIG_IS_ENABLED(TARGET_MT8188) &&
		of_machine_is_compatible("mediatek,genio-700-evk");
}

void mediatek_capsule_update_board_setup(void)
{
	fw_images[0].image_index = MT8390_FIT_IMAGE;
	fw_images[1].image_index = MT8390_FIP_IMAGE;
	fw_images[2].image_index = MT8390_BL2_IMAGE;
	fw_images[3].image_index = MT8390_FW_IMAGE;
	fw_images[4].image_index = MT8390_ENV_IMAGE;

	if (board_is_genio_700_evk()) {
		efi_guid_t image_type_guid = GENIO_700_EVK_FIT_IMAGE_GUID;
		efi_guid_t uboot_image_type_guid = GENIO_700_EVK_FIP_IMAGE_GUID;
		efi_guid_t bl2_image_type_guid = GENIO_700_EVK_BL2_IMAGE_GUID;
		efi_guid_t fw_image_type_guid = GENIO_700_EVK_FW_IMAGE_GUID;
		efi_guid_t env_image_type_guid = GENIO_700_EVK_ENV_IMAGE_GUID;

		guidcpy(&fw_images[0].image_type_id, &image_type_guid);
		guidcpy(&fw_images[1].image_type_id, &uboot_image_type_guid);
		guidcpy(&fw_images[2].image_type_id, &bl2_image_type_guid);
		guidcpy(&fw_images[3].image_type_id, &fw_image_type_guid);
		guidcpy(&fw_images[4].image_type_id, &env_image_type_guid);

		fw_images[0].fw_name = u"GENIO-700-EVK-FIT";
		fw_images[1].fw_name = u"GENIO-700-EVK-FIP";
		fw_images[2].fw_name = u"GENIO-700-EVK-BL2";
		fw_images[3].fw_name = u"GENIO-700-EVK-FW";
		fw_images[4].fw_name = u"GENIO-700-EVK-ENV";
	}
}

#if defined(CONFIG_MEDIATEK_IOT_AB_BOOT_SUPPORT)
void set_dfu_alt_info(char *interface, char *devstr)
{
	char alt[BOOTCTRL_DFU_ALT_LEN] = {0};
	const char *s = env_get(BOOTCTRL_ENV);

	if (s) {
		if (!strcmp(s, "a")) {
			if (sprintf(alt, update_info.dfu_string, BOOTCTRL_FIP_NUM + PART_BOOT_B, BOOTCTRL_FW_NUM + PART_BOOT_B) < 0)
				return;
		} else if(!strcmp(s, "b")) {
			if (sprintf(alt, update_info.dfu_string, BOOTCTRL_FIP_NUM, BOOTCTRL_FW_NUM) < 0)
				return;
		}
		env_set("dfu_alt_info", alt);
	}
}
#endif
#endif /* CONFIG_EFI_HAVE_CAPSULE_SUPPORT && CONFIG_EFI_PARTITION */

int board_init(void)
{
	struct udevice *dev;
	int ret;

	if (CONFIG_IS_ENABLED(USB_GADGET)) {
		ret = uclass_get_device(UCLASS_USB_GADGET_GENERIC, 0, &dev);
		if (ret) {
			pr_err("%s: Cannot find USB device\n", __func__);
			return ret;
		}
	}

	if (CONFIG_IS_ENABLED(USB_ETHER))
		usb_ether_init();

	printf("Enabling SCP SRAM\n");
	for (unsigned int val = 0xFFFFFFFF; val != 0U;) {
		val = val >> 1;
		writel(val, 0x1072102C);
	}

	if (IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) &&
	    IS_ENABLED(CONFIG_EFI_PARTITION))
		mediatek_capsule_update_board_setup();

	return 0;
}

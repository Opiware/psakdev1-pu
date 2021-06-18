/* Copyright Statement:
 *
 */

#ifndef __FLASH_MAP_H__
#define __FLASH_MAP_H__

/** 
 * MTK_FOTA_DUAL_IMAGE_ENABLE: Dual image FOTA feature option.
 * If enabled, there are two executable partitions on flash layout in FOTA design, called partition A and partition B.
 * Run the firmware on the one of them, upgrade new firmware on the other by FOTA, and swap the role of the partitions. 
 * Follow this behavior alternately.
 *
 * FOTA_PARTITION_B_BUILD: Dual image FOTA related feature option, depends on MTK_FOTA_DUAL_IMAGE_ENABLE, non-switchable.
 * Indicates which flash layout settings the build flow should apply to partition B. */
#ifdef MTK_FOTA_DUAL_IMAGE_ENABLE

#ifndef FOTA_PARTITION_B_BUILD
/* flash layout on partition A */
#define LOADER_LENGTH           0x8000        /*  32KB */
#define FOTA_CONTROL_LENGTH     0x8000        /*  32KB */
#define N9_RAMCODE_LENGTH       0x50000       /* 320KB */
#define CM4_CODE_LENGTH         0xA0000       /* 640KB */
#define FOTA_LENGTH             0xF0000       /* 960KB */
#define NVDM_LENGTH             0x10000       /*  64KB */

#define LOADER_BASE             0x0
#define FOTA_CONTROL_BASE       (LOADER_BASE       + LOADER_LENGTH)
#define N9_RAMCODE_BASE         (FOTA_CONTROL_BASE + FOTA_CONTROL_LENGTH)
#define CM4_CODE_BASE           (N9_RAMCODE_BASE   + N9_RAMCODE_LENGTH)
#define FOTA_BASE               (CM4_CODE_BASE     + CM4_CODE_LENGTH)
#define NVDM_BASE               (FOTA_BASE         + FOTA_LENGTH)

#define FLASH_BASE		        0x10000000

#else /* FOTA_PARTITION_B_BUILD */
/* flash layout on partition B */
#define LOADER_LENGTH           0x8000        /*  32KB */
#define FOTA_CONTROL_LENGTH     0x8000        /*  32KB */
#define FOTA_LENGTH             0xF0000       /* 960KB */
#define N9_RAMCODE_LENGTH       0x50000       /* 320KB */
#define CM4_CODE_LENGTH         0xA0000       /* 640KB */
#define NVDM_LENGTH             0x10000       /*  64KB */

#define LOADER_BASE             0x0
#define FOTA_CONTROL_BASE       (LOADER_BASE       + LOADER_LENGTH)
#define FOTA_BASE               (FOTA_CONTROL_BASE + FOTA_CONTROL_LENGTH)
#define N9_RAMCODE_BASE         (FOTA_BASE         + FOTA_LENGTH)
#define CM4_CODE_BASE           (N9_RAMCODE_BASE   + N9_RAMCODE_LENGTH)
#define NVDM_BASE               (CM4_CODE_BASE     + CM4_CODE_LENGTH)

#define FLASH_BASE		        0x10000000
#endif /* FOTA_PARTITION_B_BUILD */

#else /* origin layout setting */

#define LOADER_LENGTH           0x8000        /*  32KB */
#define RESERVED_LENGTH         0x8000        /*  32KB */
#define N9_RAMCODE_LENGTH       0x69000       /* 420KB */
#define CM4_CODE_LENGTH         0xBF000       /* 764KB */
#define FOTA_LENGTH             0xBF000       /* 764KB */
#define NVDM_LENGTH             0x9000        /*  36KB */

#define LOADER_BASE             0x0
#define RESERVED_BASE           (LOADER_BASE     + LOADER_LENGTH)
#define N9_RAMCODE_BASE         (RESERVED_BASE   + RESERVED_LENGTH)
#define CM4_CODE_BASE           (N9_RAMCODE_BASE + N9_RAMCODE_LENGTH)
#define FOTA_BASE               (CM4_CODE_BASE   + CM4_CODE_LENGTH)
#define NVDM_BASE               (FOTA_BASE       + FOTA_LENGTH)

#define FLASH_BASE		        0x10000000

#endif

#endif // __FLASH_MAP_H__


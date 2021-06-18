/* Copyright Statement:
 *
 */

#ifndef __FLASH_MAP_H__
#define __FLASH_MAP_H__

#define LOADER_LENGTH           0x8000        /*  32KB */
#define RESERVED_LENGTH         0x8000        /*  32KB */
#define N9_RAMCODE_LENGTH       0x69000       /* 420KB */
#define CM4_CODE_LENGTH         0x1ED000       /* 1972KB */
#define FOTA_LENGTH             0x18A000       /* 1576KB */
#define NVDM_LENGTH             0x10000        /*  64KB */

#define LOADER_BASE             0x0
#define RESERVED_BASE           (LOADER_BASE     + LOADER_LENGTH)
#define N9_RAMCODE_BASE         (RESERVED_BASE   + RESERVED_LENGTH)
#define CM4_CODE_BASE           (N9_RAMCODE_BASE + N9_RAMCODE_LENGTH)
#define FOTA_BASE               (CM4_CODE_BASE   + CM4_CODE_LENGTH)
#define NVDM_BASE               (FOTA_BASE       + FOTA_LENGTH)

#define FLASH_BASE		        0x10000000

#define TCM_BASE                0x00100000
#define TCM_LENGTH              0x00010000  /* 64kB */

#endif // __FLASH_MAP_H__



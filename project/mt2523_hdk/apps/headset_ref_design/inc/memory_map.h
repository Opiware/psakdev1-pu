/* Copyright Statement:
 *
 */

#ifndef __MEMORY_MAP_H__
#define __MEMORY_MAP_H__

#if defined(MTK_MP3_ON_FLASH_ENABLE)
    #define BL_BASE    0x08000000
    #define BL_LENGTH  0x00010000    /* 64kB */
    
    #define CM4_BASE    0x08010000
    #define CM4_LENGTH  0x003E0000   /* 3968kB */
    
    #define FOTA_RESERVED_BASE    0x083F0000
    #define FOTA_RESERVED_LENGTH  0x00002000   /* 8kB */
    
    #define ROM_NVDM_BASE    0x083F2000
    #define ROM_NVDM_LENGTH  0x0000E000   /* 56kB */
    
    #define RAM_BASE    0x00000000
    #define RAM_LENGTH  0x00100000   /* 1024kB */
    
    #define VRAM_BASE    0x10000000
    #define VRAM_LENGTH  0x00100000   /* 1024kB */
    
    #define TCM_BASE      0x04008000
    #define TCM_LENGTH    0x00020000  /* 128kB */
#elif defined(MTK_INEAR_NOODLES_HEADSET_ENABLE)
    #define BL_BASE    0x08000000
    #define BL_LENGTH  0x00010000    /* 64kB */
    
    #define CM4_BASE    0x08010000
    #define CM4_LENGTH  0x00145000   /* 1300kB */
    
    #define FOTA_RESERVED_BASE    0x08155000
    #define FOTA_RESERVED_LENGTH  0x0009D000   /* 628kB */
    
    #define ROM_NVDM_BASE    0x083F2000
    #define ROM_NVDM_LENGTH  0x0000E000   /* 56kB */
    
    #define RAM_BASE    0x00000000
    #define RAM_LENGTH  0x00100000   /* 1024kB */
    
    #define VRAM_BASE    0x10000000
    #define VRAM_LENGTH  0x00100000   /* 1024kB */
    
    #define TCM_BASE      0x04008000
    #define TCM_LENGTH    0x00020000  /* 128kB */
#else
    #define BL_BASE    0x08000000
    #define BL_LENGTH  0x00010000    /* 64kB */
    
    #define CM4_BASE    0x08010000
    #define CM4_LENGTH  0x0012C000   /* 1200kB */
    
    #define FOTA_RESERVED_BASE    0x0813C000
    #define FOTA_RESERVED_LENGTH  0x000B6000   /* 728kB */
    
    #define ROM_NVDM_BASE    0x081F2000
    #define ROM_NVDM_LENGTH  0x0000E000   /* 56kB */
    
    #define RAM_BASE    0x00000000
    #define RAM_LENGTH  0x00100000   /* 1024kB */
    
    #define VRAM_BASE    0x10000000
    #define VRAM_LENGTH  0x00100000   /* 1024kB */
    
    #define TCM_BASE      0x04008000
    #define TCM_LENGTH    0x00020000  /* 128kB */

#endif

#endif


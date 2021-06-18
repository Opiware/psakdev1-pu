/* Copyright Statement:
 *
 */

#include "exception_handler.h"

/******************************************************************************/
/*            Memory Regions Definition                                       */
/******************************************************************************/
#if defined(__GNUC__)

extern unsigned int __FLASH_segment_start__[];
extern unsigned int __FLASH_segment_end__[];
extern unsigned int __SRAM_segment_start__[];
extern unsigned int __SRAM_segment_end__[];
extern unsigned int __ramtext_start__[];
extern unsigned int __ramtext_end__[];
extern unsigned int __tcmbss_start__[];
extern unsigned int __tcmbss_end__[];

const memory_region_type memory_regions[] =
{
    {"flash", __FLASH_segment_start__, __FLASH_segment_end__, 0},
    {"sram",  __SRAM_segment_start__, __SRAM_segment_end__, 1},
    {"ramtext", __ramtext_start__, __ramtext_end__, 1},
    {"tcmbss", __tcmbss_start__, __tcmbss_end__, 1},
    {"scs",  (unsigned int*)SCS_BASE, (unsigned int*)(SCS_BASE + 0x1000), 1},
    {0}
};

#endif /* __GNUC__ */

#if defined (__CC_ARM)

extern unsigned int Image$$TEXT$$Base[];
extern unsigned int Image$$TEXT$$Limit[];
extern unsigned int Image$$DATA$$Base[];
extern unsigned int Image$$DATA$$ZI$$Limit[];
extern unsigned int Image$$TCM$$Base[];
extern unsigned int Image$$TCM$$ZI$$Limit[];
extern unsigned int Image$$STACK$$Base[];
extern unsigned int Image$$STACK$$ZI$$Limit[];

const memory_region_type memory_regions[] =
{
    {"text", Image$$TEXT$$Base, Image$$TEXT$$Limit, 0},
    {"data", Image$$DATA$$Base, Image$$DATA$$ZI$$Limit, 1},
    {"tcm", Image$$TCM$$Base, Image$$TCM$$ZI$$Limit, 1},
    {"stack", Image$$STACK$$Base, Image$$STACK$$ZI$$Limit, 1},
    {"scs",  (unsigned int *)SCS_BASE, (unsigned int *)(SCS_BASE + 0x1000), 1},
    {0}
};

#endif /* __CC_ARM */


#if defined(__ICCARM__)

extern unsigned int RAM_BLOCK$$Base[];
extern unsigned int RAM_BLOCK$$Limit[];
extern unsigned int TCM_BLOCK$$Base[];
extern unsigned int TCM_BLOCK$$Limit[];
extern unsigned int CSTACK$$Base[];
extern unsigned int CSTACK$$Limit[];

const memory_region_type memory_regions[] =
{
    {"ram", RAM_BLOCK$$Base, RAM_BLOCK$$Limit, 1},
    {"tcm", TCM_BLOCK$$Base, TCM_BLOCK$$Limit, 1},
    {"stack", CSTACK$$Base, CSTACK$$Limit, 1},
    {"scs", (unsigned int*)SCS_BASE, (unsigned int*)(SCS_BASE + 0x1000), 1},
    {0}
};


#endif /* __ICCARM__ */



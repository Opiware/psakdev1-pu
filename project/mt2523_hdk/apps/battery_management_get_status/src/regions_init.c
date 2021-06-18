/* Copyright Statement:
 *
 */

#include "exception_handler.h"

/******************************************************************************/
/*            Memory Regions Definition                                       */
/******************************************************************************/
#if 0
typedef struct
{
  char *region_name;
  unsigned int *start_address;
  unsigned int *end_address;
  unsigned int is_dumped;
} memory_region_type;
#endif

#if defined(__GNUC__)

extern unsigned int Image$$RAM_TEXT$$Base[];
extern unsigned int Image$$RAM_TEXT$$Limit[];
extern unsigned int Image$$NONCACHED_DATA$$Base[];
extern unsigned int Image$$NONCACHED_ZI$$Limit[];
extern unsigned int Image$$CACHED_DATA$$RW$$Base[];
extern unsigned int Image$$CACHED_DATA$$ZI$$Limit[];
extern unsigned int Image$$TCM$$RO$$Base[];
extern unsigned int Image$$TCM$$ZI$$Limit[];
extern unsigned int Image$$STACK$$ZI$$Base[];
extern unsigned int Image$$STACK$$ZI$$Limit[];

const memory_region_type memory_regions[] =
{
    {"ram_text", Image$$RAM_TEXT$$Base, Image$$RAM_TEXT$$Limit, 1},
    {"noncached_data", Image$$NONCACHED_DATA$$Base, Image$$NONCACHED_ZI$$Limit, 1},
    {"cached_data", Image$$CACHED_DATA$$RW$$Base, Image$$CACHED_DATA$$ZI$$Limit, 1},
    {"tcm", Image$$TCM$$RO$$Base, Image$$STACK$$ZI$$Limit, 1},
    {"stack", Image$$STACK$$ZI$$Base, Image$$STACK$$ZI$$Limit, 0},
    {"scs", (unsigned int*)SCS_BASE, (unsigned int*)(SCS_BASE + 0x1000), 1},
    {0}
};

#endif /* __GNUC__ */

#if defined (__CC_ARM)

extern unsigned int Image$$RAM_TEXT$$Base[];
extern unsigned int Image$$RAM_TEXT$$Limit[];
extern unsigned int Image$$NONCACHED_DATA$$Base[];
extern unsigned int Image$$NONCACHED_ZI$$Limit[];
extern unsigned int Image$$CACHED_DATA$$RW$$Base[];
extern unsigned int Image$$CACHED_DATA$$ZI$$Limit[];
extern unsigned int Image$$TCM$$RO$$Base[];
extern unsigned int Image$$TCM$$ZI$$Limit[];
extern unsigned int Image$$STACK$$ZI$$Base[];
extern unsigned int Image$$STACK$$ZI$$Limit[];

const memory_region_type memory_regions[] =
{
    {"ram_text", Image$$RAM_TEXT$$Base, Image$$RAM_TEXT$$Limit, 1},
    {"noncached_data", Image$$NONCACHED_DATA$$Base, Image$$NONCACHED_ZI$$Limit, 1},
    {"cached_data", Image$$CACHED_DATA$$RW$$Base, Image$$CACHED_DATA$$ZI$$Limit, 1},
    {"tcm", Image$$TCM$$RO$$Base, Image$$STACK$$ZI$$Limit, 1},
    {"stack", Image$$STACK$$ZI$$Base, Image$$STACK$$ZI$$Limit, 0},
    {"scs", (unsigned int*)SCS_BASE, (unsigned int*)(SCS_BASE + 0x1000), 1},
    {0}
};

#endif /* __CC_ARM */

#if defined(__ICCARM__)

extern unsigned int RAM_BLOCK$$Base[];
extern unsigned int RAM_BLOCK$$Limit[];
extern unsigned int VRAM_BLOCK$$Base[];
extern unsigned int VRAM_BLOCK$$Limit[];
extern unsigned int TCM_BLOCK$$Base[];
extern unsigned int TCM_BLOCK$$Limit[];
extern unsigned int CSTACK$$Base[];
extern unsigned int CSTACK$$Limit[];

const memory_region_type memory_regions[] =
{
    {"ram", RAM_BLOCK$$Base, RAM_BLOCK$$Limit, 1},
    {"vram", VRAM_BLOCK$$Base, VRAM_BLOCK$$Limit, 1},
    {"tcm", TCM_BLOCK$$Base, CSTACK$$Limit, 1},
    {"stack", CSTACK$$Base, CSTACK$$Limit, 0},
    {"scs", (unsigned int*)SCS_BASE, (unsigned int*)(SCS_BASE + 0x1000), 1},
    {0}
};
#endif /* __ICCARM__ */



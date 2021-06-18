/* Copyright Statement:
 *
 */

#include <stdbool.h>

#if (PRODUCT_VERSION == 2523 || PRODUCT_VERSION == 2533)
#include "mt2523.h"
#include "hal_flash_mtd.h"
#define configUSE_FLASH_SUSPEND 1
#endif

#if (PRODUCT_VERSION == 7687) || (PRODUCT_VERSION == 7697)
#include "mt7687.h"
#include "flash_sfc.h"
#define configUSE_FLASH_SUSPEND 1
#endif

#if (PRODUCT_VERSION == 7686) || (PRODUCT_VERSION == 7682)
#include "mt7686.h"
#include "flash_sfc.h"
#define configUSE_FLASH_SUSPEND 1
#endif

#if (PRODUCT_VERSION == 5932)
#include "mt7686.h"
#define configUSE_FLASH_SUSPEND 0
#endif

#if defined(MTK_SAVE_LOG_AND_CONTEXT_DUMP_ENABLE)

#if (PRODUCT_VERSION == 7687) || (PRODUCT_VERSION == 7697)
#include "flash_map.h"
#include "xflash_map.h"
#define CRASH_CONTEXT_FLASH_BASE     CRASH_CONTEXT_BASE
#define CRASH_CONTEXT_RESERVED_SIZE  CRASH_CONTEXT_LENGTH

#define CRASH_CONTEXT_EXT_FLASH_BASE     CRASH_CONTEXT_EXT_BASE
#define CRASH_CONTEXT_EXT_RESERVED_SIZE  CRASH_CONTEXT_EXT_LENGTH

#endif

#if (PRODUCT_VERSION == 2523)
#include "memory_map.h"
#define CRASH_CONTEXT_FLASH_BASE     (CRASH_CONTEXT_BASE - BL_BASE)
#define CRASH_CONTEXT_RESERVED_SIZE  CRASH_CONTEXT_LENGTH
#endif

void exception_get_assert_expr(const char **expr, const char **file, int *line);

#endif /* MTK_SAVE_LOG_AND_CONTEXT_DUMP_ENABLE */

#define DISABLE_MEMDUMP_MAGIC 0xdeadbeef

typedef struct
{
  char *region_name;
  unsigned int *start_address;
  unsigned int *end_address;
  unsigned int is_dumped;
} memory_region_type;

typedef void (*f_exception_callback_t)(void);

typedef struct
{
  f_exception_callback_t init_cb;
  f_exception_callback_t dump_cb;
} exception_config_type;

bool exception_register_callbacks(exception_config_type *cb);
void exception_dump_config(int flag);
void exception_reboot(void);

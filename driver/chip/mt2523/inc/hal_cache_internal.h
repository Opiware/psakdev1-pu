/* Copyright Statement:
 *
 */

#ifndef __HAL_CACHE_INTERNAL_H__
#define __HAL_CACHE_INTERNAL_H__
#include "hal_cache.h"

#ifdef HAL_CACHE_MODULE_ENABLED

#include "hal_nvic.h"
#include "hal_nvic_internal.h"



#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint32_t MCEN: 1;                       /**< CACHE enable */
        uint32_t MPEN: 1;                       /**< MPU enable */
        uint32_t CNTEN0: 1;                     /**< Hit counter0 enable */
        uint32_t CNTEN1: 1;                     /**< Hit counter1 enable */
        uint32_t MPDEFEN: 1;                    /**< MPU default protection */
        uint32_t _reserved0: 2;                 /**< Reserved */
        uint32_t MDRF: 1;                       /**< Early restart */
        uint32_t CACHESIZE: 2;                  /**< CACHE size */
        uint32_t _reserved1: 22;                /**< Reserved */
    } b;
    uint32_t w;
} CACHE_CON_Type;

typedef uint32_t CACHE_REGION_EN_Type;          /**< Region Enable Type */

typedef union {
    struct {
        uint32_t _reserved0: 5;                 /**< bit 0 */
        uint32_t ATTR: 3;                       /**< Attribute */
        uint32_t C: 1;                          /**< Cacheable bit */
        uint32_t _reserved1: 3;                 /**< Reserved */
        uint32_t BASEADDR: 20;                  /**< Base address of CACHE region */
    } b;
    uint32_t w;
} CACHE_ENTRY_N_Type;

typedef union {
    struct {
        uint32_t _reserved0: 12;                /**< Reserved */
        uint32_t BASEADDR: 20;                  /**< End address of CACHE region */
    } b;
    uint32_t w;
} CACHE_END_ENTRY_N_Type;

typedef struct {
    CACHE_ENTRY_N_Type cache_entry_n;
    CACHE_END_ENTRY_N_Type cache_end_entry_n;
} CACHE_ENTRY_Type;


extern CACHE_CON_Type g_cache_con;
extern CACHE_REGION_EN_Type g_cache_region_en;
extern CACHE_ENTRY_Type g_cache_entry[HAL_CACHE_REGION_MAX];

#define MTK_CACHE_REGION_SIZE_UNIT  (0x1000)    /**< CACHE region size must be 4KB aligned */

typedef enum {
    CACHE_INVALIDATE_ALL_LINES = 1,             /**< Invalidate all CACHE line */
    CACHE_INVALIDATE_ONE_LINE_BY_ADDRESS = 2,   /**< Invalidate one line by address */
    CACHE_INVALIDATE_ONE_LINE_BY_SET_WAY = 4,   /**< Invalidate one line by set and way */
    CACHE_FLUSH_ALL_LINES = 9,                  /**< Flush all CACHE lines */
    CACHE_FLUSH_ONE_LINE_BY_ADDRESS = 10,       /**< Flush one line by address */
    CACHE_FLUSH_ONE_LINE_BY_SET_WAY = 12        /**< Flush one line by set and way */
} cache_line_command_t;

#ifdef HAL_SLEEP_MANAGER_ENABLED

/* Save CACHE status before entering deepsleep */
void cache_status_save(void);

/* Restore CACHE status after leaving deepsleep */
void cache_status_restore(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_CACHE_MODULE_ENABLED */
#endif /* __HAL_CACHE_INTERNAL_H__ */


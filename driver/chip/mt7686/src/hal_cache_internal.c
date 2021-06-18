/* Copyright Statement:
 *
 */

#include "hal_cache.h"

#ifdef HAL_CACHE_MODULE_ENABLED

#include "hal_cache_internal.h"
#include "memory_attribute.h"
#include "memory_map.h"

#ifdef __cplusplus
extern "C" {
#endif


ATTR_RWDATA_IN_TCM CACHE_CON_Type g_cache_con;
ATTR_RWDATA_IN_TCM CACHE_REGION_EN_Type g_cache_region_en;
ATTR_RWDATA_IN_TCM CACHE_ENTRY_Type g_cache_entry[HAL_CACHE_REGION_MAX];

#ifdef HAL_SLEEP_MANAGER_ENABLED

/* flush and invalidate before enter deepsleep!!! */
ATTR_TEXT_IN_TCM void  cache_status_save(void)
{
    /* flush all */
    CACHE->CACHE_OP &= ~CACHE_OP_OP_MASK;
    CACHE->CACHE_OP |= ((CACHE_FLUSH_ALL_LINES << CACHE_OP_OP_OFFSET) | CACHE_OP_EN_MASK);
    /* invalidate all */
    CACHE->CACHE_OP &= ~CACHE_OP_OP_MASK;
    CACHE->CACHE_OP |= ((CACHE_INVALIDATE_ALL_LINES << CACHE_OP_OP_OFFSET) | CACHE_OP_EN_MASK);
    /* cache disable */
    CACHE->CACHE_CON &= ~CACHE_CON_MCEN_MASK;
}

/* restores only regions that are enabled before entering into deepsleep */
ATTR_TEXT_IN_TCM void  cache_status_restore(void)
{
    CACHE_REGION_EN_Type cache_region_en;
    hal_cache_region_t region;

    cache_region_en = g_cache_region_en;
	
    /* invalidate all */
    CACHE->CACHE_OP &= ~CACHE_OP_OP_MASK;
    CACHE->CACHE_OP |= ((CACHE_INVALIDATE_ALL_LINES << CACHE_OP_OP_OFFSET) | CACHE_OP_EN_MASK);

    for (region = HAL_CACHE_REGION_0; region < HAL_CACHE_REGION_MAX; region ++) {
        /* If the region is enabled, restore the previous setting of the corresponding region*/
        if (cache_region_en & 1) {
            CACHE->CACHE_ENTRY_N[region] = g_cache_entry[region].cache_entry_n.w;
            CACHE->CACHE_END_ENTRY_N[region] = g_cache_entry[region].cache_end_entry_n.w;
        }
        cache_region_en = cache_region_en >> 1;
    }
    CACHE->CACHE_REGION_EN = g_cache_region_en;
    CACHE->CACHE_CON = g_cache_con.w;
}

#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_CACHE_MODULE_ENABLED */


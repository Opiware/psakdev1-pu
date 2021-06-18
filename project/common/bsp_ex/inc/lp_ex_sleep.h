/* Copyright Statement:
 *
 */

/**
 * @file        lp_ex_sleep.h
 * @brief       Low Power CLI
 *
 * @history     2015/08/18   Initial for 1st draft */

#ifndef __LP_EX_SLEEP_H__
#define __LP_EX_SLEEP_H__

#include "cli.h"

#ifdef __cplusplus
extern "C" {
#endif

#if ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))
#if defined(MTK_HAL_LOWPOWER_ENABLE)
extern cmd_t   lp_cli[];
#define LP_CLI_ENTRY { "lp",  "low power",  NULL, lp_cli },
#endif
#endif

#ifndef LP_CLI_ENTRY
#define LP_CLI_ENTRY
#endif

#ifdef __cplusplus
}
#endif

#endif /*  __LP_EX_SLEEP_H__ */

/* Copyright Statement:
 *
 */
/**
 * @file wifi_inband_cli.h
 *
 * Inband Command CLI commands tree.
 *
 * @author  Anthony Liu
 * @version 2015/12/11 Initial */

#ifndef __WIFI_INBAND_CLI_H__
#define __WIFI_INBAND_CLI_H__


#ifdef MTK_MINICLI_ENABLE


#include "cli.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CC_ARM
extern const cmd_t inband_cmds_cli[];
#else
extern cmd_t inband_cmds_cli[];
#endif


#ifdef MTK_MINISUPP_ENABLE
#define INBAND_CLI_ENTRY    { "inband", "inband channel", NULL, (cmd_t *)inband_cmds_cli },
#else
#define INBAND_CLI_ENTRY
#endif

#ifdef __cplusplus
}
#endif

#endif /* MTK_MINICLI_ENABLE */

#endif /* __WIFI_INBAND_CLI_H__ */


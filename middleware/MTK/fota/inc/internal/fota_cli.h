/* Copyright Statement:
 *
 */

#ifndef __FTOA_CLI_H__
#define __FTOA_CLI_H__

#ifndef MOD_CFG_FOTA_DISABLE_CLI

#include "cli.h"


#ifdef __cplusplus
extern "C" {
#endif

extern cmd_t   fota_cli[];


#if defined(MTK_FOTA_ENABLE)
#define FOTA_CLI_ENTRY      { "fota", "storage mgmt", NULL, fota_cli },
#else
#define FOTA_CLI_ENTRY
#endif


#ifdef __cplusplus
}
#endif


#endif /* MOD_CFG_FOTA_DISABLE_CLI */

#endif /* __FTOA_CLI_H__ */


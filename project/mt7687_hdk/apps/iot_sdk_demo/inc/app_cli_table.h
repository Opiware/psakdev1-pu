/* Copyright Statement:
 *
 */

#ifndef __APP_CLI_TABLE_H__
#define __APP_CLI_TABLE_H__

#ifdef MTK_MINICLI_ENABLE


#ifdef __cplusplus
 extern "C" {
#endif



 /**
  * WIFI_CLI_ENTRY
  */
#include "wifi_cli.h"




#define APP_CLI_CMDS     WIFI_PUB_CLI_ENTRY \
                         WIFI_PUB_CLI_SMNT_ENTRY \
                         PING_CLI_ENTRY \
                         IPERF_CLI_ENTRY


#ifdef __cplusplus
 }
#endif

#endif /* #if defined(MTK_MINICLI_ENABLE) */

#endif /* __APP_CLI_TABLE_H__ */



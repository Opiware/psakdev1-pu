/* Copyright Statement:
 *
 */

#ifndef __SIE_CLI_H__
#define __SIE_CLI_H__

#include "cli.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const cmd_t sie_cmds[];

#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE
#define SIE_CLI_ENTRY   { "sie",    "sie",            NULL, (cmd_t *)sie_cmds },
#else
#define SIE_CLI_ENTRY
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SIE_CLI_H__ */


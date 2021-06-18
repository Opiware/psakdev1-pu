/* Copyright Statement:
 *
 */

#ifndef __MINISUPP_CLI_H__
#define __MINISUPP_CLI_H__

#if defined(MTK_MINICLI_ENABLE)


#include "cli.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifdef MTK_MINISUPP_ENABLE
extern const cmd_t    minisupp_cli[];
#define MINISUPP_CLI_ENTRY  { "wpa"   ,"wpa_supplicant" , NULL, (cmd_t *)minisupp_cli},
#else
#define MINISUPP_CLI_ENTRY
#endif


#ifdef __cplusplus
}
#endif


#endif /* #if defined(MTK_MINICLI_ENABLE) */


#endif /* __MINISUPP_CLI_H__ */


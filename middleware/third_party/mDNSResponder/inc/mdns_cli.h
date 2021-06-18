/* Copyright Statement:
 *
 */

#ifndef __MDNS_CLI_H__
#define __MDNS_CLI_H__

#if defined(MTK_MINICLI_ENABLE)

#include <cli.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The following content is used in the HomeKit Project. */
#ifdef MTK_HOMEKIT_ENABLE

/**
 *  @brief      mDNS CLI declaration for HomeKit BCT
 */
extern cmd_t mdns_cli[];
#define MOD_MDNS_CLI_ENTRY {"mdnsd", "mdnsd cmd", NULL, mdns_cli},
#else
#define MOD_MDNS_CLI_ENTRY
#endif

#ifdef __cplusplus
}
#endif

#endif /* #if defined(MTK_MINICLI_ENABLE) */

#endif /* __MDNS_CLI_H__ */

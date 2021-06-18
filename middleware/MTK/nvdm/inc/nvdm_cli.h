/* Copyright Statement:
 *
 */

#ifndef __NVDM_CLI_H__
#define __NVDM_CLI_H__

#ifdef MTK_NVDM_ENABLE

#include "cli.h"

#ifdef __cplusplus
extern "C" {
#endif


extern cmd_t nvdm_cli[];


#define NVDM_CLI_ENTRY      { "config", "user config read/write/reset/show", NULL, nvdm_cli},


#ifdef __cplusplus
}
#endif

#endif

#endif /* __NVDM_CLI_H__ */


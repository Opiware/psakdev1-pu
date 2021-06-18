/* Copyright Statement:
 *
 */

#ifndef __CONTEXT_INFO_SAVE_H__
#define __CONTEXT_INFO_SAVE_H__

#ifdef MTK_NVDM_ENABLE

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

bool context_info_save(uint8_t *context_info, uint32_t length);

#ifdef __cplusplus
    }
#endif

#endif

#endif


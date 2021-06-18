/* Copyright Statement:
 *
 */

#ifndef __EXTERNAL_NTC_H__
#define __EXTERNAL_NTC_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

bool external_ntc_init(void);
int32_t external_ntc_get_temperature(void);

#ifdef __cplusplus
}
#endif

#endif

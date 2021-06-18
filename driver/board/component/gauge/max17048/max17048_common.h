/* Copyright Statement:
 *
 */

#ifndef __MAX17048_COMMON_H__
#define __MAX17048_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX17048_DEBUG_ENABLEx
#ifdef  MAX17048_DEBUG_ENABLE
#define MAX17048_DBG(_message,...)      LOG_I(max17048,_message, ##__VA_ARGS__)
#else
#define MAX17048_DBG(_message,...)
#endif
#define MAX17048_INFO(_message,...)     LOG_I(max17048,_message, ##__VA_ARGS__)
#define MAX17048_WARN(_message,...)     LOG_W(max17048,_message, ##__VA_ARGS__)
#define MAX17048_ERR(_message,...)      LOG_E(max17048,_message, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif

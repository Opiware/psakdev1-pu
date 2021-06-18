/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_CUSTOM_H__
#define __HAL_AUDIO_CUSTOM_H__

#include "hal_audio.h"

#if defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED)

#include<stdint.h>
#include<stdbool.h>
#include "hal_gpio.h"
#include "hal_audio_internal_afe.h"
#include "hal_log.h"

#ifdef __cplusplus
extern "C" {
#endif

void afe_switch_external_amp(bool on);

#ifdef __cplusplus
}
#endif

#endif  /* defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED) */

#endif /*__AUDIO_INTERNAL_PCM2WAY_H__*/

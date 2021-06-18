/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_EXT_H__
#define __HAL_AUDIO_EXT_H__

#include "hal_platform.h"

#ifdef HAL_I2S_MODULE_ENABLED
#include "hal_audio.h"

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Audio device. */
typedef enum {
    HAL_AUDIO_EXT_DEVICE_NONE               = 0x00,
    HAL_AUDIO_EXT_DEVICE_I2S_IN             = 0x01,
    HAL_AUDIO_EXT_DEVICE_I2S_OUT            = 0x02
} hal_audio_ext_device_t;

hal_audio_status_t hal_audio_set_extended_out_device(hal_audio_ext_device_t device);

/**
 *  @brief     Speical case to enable i2s rx when dsp decode. (AAC/SBC)
 *  @param[in] enable is a flag to set the i2s rx on/off. */
void hal_i2s_dsp_decode_enable(bool enable);

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2S_MODULE_ENABLED */
#endif /* __HAL_AUDIO_EXT_H__ */

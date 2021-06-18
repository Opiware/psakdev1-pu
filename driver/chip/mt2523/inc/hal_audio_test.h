/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_TEST_H__
#define __HAL_AUDIO_TEST_H__

#include "hal_audio.h"

#if defined(__GNUC__)
#if defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED)

#include<stdint.h>
#include<stdbool.h>
#include "hal_audio_internal_pcm.h"
#include "hal_audio_internal_afe.h"
#include "hal_audio_internal_service.h"
#include "hal_audio_internal_pcm2way.h"
#include "hal_audio_fw_interface.h"
#include "hal_accdet.h"
#include "hal_gpt.h"
#include "hal_log.h"
#include "hal_i2s.h"
#include "hal_gpio.h"
#include "hal_rtc.h"

#ifdef HAL_AUDIO_LOW_POWER_ENABLED
#include "hal_audio_low_power.h"
#endif

#ifdef MTK_EXTERNAL_DSP_ENABLE
#define HAL_AUDIO_TEST_ENABLE
#endif

/* This feature option HAL_AUDIO_SDFATFS_ENABLE is for testing internally. Please do not turn on it. */
//#define HAL_AUDIO_SDFATFS_ENABLE
//#define HAL_AUDIO_SLT_ENABLE

/* This feature option AUDIO_TEST_ACOUSTIC_LOOPBACK_ENABLE is for loopback from uplink to downlink. Please turn on it if needed. */
#define AUDIO_TEST_ACOUSTIC_LOOPBACK_ENABLE

#if defined(HAL_AUDIO_SDFATFS_ENABLE)
#include "ff.h"
#endif

#define WB_BUFFER_SIZE              320
#define NB_BUFFER_SIZE              160
#define I2S_TEST_RX_DUMP_SIZE       256     /* in word */
typedef long long  int64_t;

#define PI  3.1415926535
#define nb_buffer_size 160

/* 2523G EVB: make sure J1040.1 & J1040.2 is connected before insert earphone! */
#define HOOK_KEY_DEBOUNCE_TIME 300
#define PLUG_IN_DEBOUNCE_TIME  500               /**< unit = 1ms */
#define PLUG_OUT_DEBOUNCE_TIME 50

#define RB_INC(in, size)    (((in)++) == (size)? (0) : (in))

typedef struct complex_ {
    int64_t  real;
    int64_t  image;
} Complex;

uint8_t audio_test_detect_1k_tone_result(void);
void audio_test_set_output_device(hal_audio_device_t device);
void audio_test_set_input_device(hal_audio_device_t device);
void audio_test_set_audio_tone(bool enable);
uint8_t audio_test_play_voice_1k_tone(void);
uint8_t audio_test_play_audio_1k_tone(void);
uint8_t audio_test_external_loopback_test(void);
uint8_t audio_test_internal_loopback_test(void);
uint8_t audio_test_stop_1k_tone(void);
uint8_t audio_test_detect_earphone(void);
void register_accdet_callback(void);
uint8_t audio_test_play_audio_sd(void);
uint8_t audio_test_stop_audio_sd(void);
void audio_set_audio_sd_play_repeat(bool repeat);
bool audio_is_slt_or_external_loopback_test(void);
uint8_t audio_slt_test(void);
uint8_t audio_external_dsp_slt_test(void);
uint8_t audio_test_dual_dmic_bypass(void);
uint8_t audio_test_download_external_dsp(void);
uint8_t audio_test_i2s_external_loopback(void);
uint8_t audio_test_loopback_ul2dl(void);
uint8_t audio_test_loopback_ul2dl_mixer(bool mix, uint32_t delay_ms);

#endif /* defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED) */

#endif /*__HAL_AUDIO_TEST_H__*/
#endif /*defined(__GNUC__)*/

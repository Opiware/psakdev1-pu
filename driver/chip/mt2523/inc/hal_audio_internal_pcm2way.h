/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_INTERNAL_PCM2WAY_H__
#define __HAL_AUDIO_INTERNAL_PCM2WAY_H__

#include "hal_audio.h"

#if defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED)

#include<stdint.h>
#include<stdbool.h>
#include "hal_audio_fw_sherif.h"
#include "hal_audio_fw_interface.h"
#include "hal_audio_internal_afe.h"
#include "hal_audio_internal_service.h"
#include "hal_audio_internal_pcm.h"
#include "hal_log.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*audio_pcm2way_stream_in_callback_t)(void);

typedef enum {
    PCM2WAY_WIDEBAND = 0,
    PCM2WAY_NARROWBAND
} audio_pcm2way_band_t;

typedef enum {
    PCMEX_OFF = 0,
    PCMEX_ON,
    PCMEX_READY
} pcm_ex_state_t;

typedef enum {
    UL_FIFO = 0,
    I2S_FIFO
} audio_pcm2way_afe_uplink_fifo;

typedef enum {
    PCM2WAY_FORMAT_NORMAL = 0,  //NB
    PCM2WAY_FORMAT_WB_NORMAL,   //normal usage for WB p2w
    PCM2WAY_FORMAT_CAL,         //calibration
    PCM2WAY_FORMAT_WB_CAL       //WB calibration
} audio_pcm2way_format_t;

typedef struct {
    bool stream_in_d2m_on;
    bool stream_in_is_after_enhancement;
    bool stream_out_m2d_on;
    bool stream_out_is_after_enhancement;
    audio_pcm2way_band_t band;
    audio_pcm2way_format_t format;
} audio_pcm2way_config_t;

typedef struct {
    audio_pcm2way_config_t audio_pcm2way_config;
    uint16_t audio_id;
    uint32_t dsp_pcm_ex_rx_len;
    uint32_t dsp_pcm_ex_tx_len;
    speech_path_type_t path;
    audio_pcm2way_afe_uplink_fifo pcm2way_uplink_fifo;
    audio_pcm2way_stream_in_callback_t stream_in_callback;
} audio_pcm2way_t;

#define PCM2WAY_PRESILENCE_NUM 7

void audio_pcm2way_set_dsp_uplink_fifo(audio_pcm2way_afe_uplink_fifo uplink_fifo);
void audio_pcm2way_register_stream_in_callback(hal_audio_stream_in_callback_t callback, void *user_data);
void audio_pcm2way_register_stream_out_callback(hal_audio_stream_out_callback_t callback, void *user_data);
hal_audio_status_t audio_pcm2way_stream_in_read(const void *buffer, uint32_t size);
hal_audio_status_t audio_pcm2way_stream_out_write(const void *buffer, uint32_t size);
void audio_pcm2way_get_from_stream_in(uint16_t *stream_in_buffer);
void audio_pcm2way_get_from_stream_in_second_mic(uint16_t *stream_in_buffer);
void audio_pcm2way_put_to_stream_out(uint16_t *stream_out_buffer);
void audio_pcm2way_start(void (*pcm2way_dl_hdlr)(void), void (*pcm2way_ul_hdlr)(void), audio_pcm2way_config_t *config);
void audio_pcm2way_stop(void);
void audio_pcm2way_play_voice(void);
void audio_pcm2way_stop_voice(void);
speech_path_type_t audio_pcm2way_get_path_type(void);
#ifdef __cplusplus
}
#endif

#endif  /* defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED) */

#endif /*__AUDIO_INTERNAL_PCM2WAY_H__*/

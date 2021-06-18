/* Copyright Statement:
 *
 */

#ifndef __HAL_I2S_INTERNAL_PCM_ROUTE_H__
#define __HAL_I2S_INTERNAL_PCM_ROUTE_H__

#include "hal_i2s.h"

#if defined(HAL_I2S_MODULE_ENABLED)

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_i2s_internal.h"
#include "hal_audio_fw_sherif.h"
#include "hal_audio_fw_interface.h"

#define PCM_ROUTE_MASK      0x80
#define PCM_ROUTE_ON        0x81

extern hal_i2s_t      hal_i2s;

typedef struct pcm_route_handle_s pcm_route_handle_t;
struct pcm_route_handle_s {
    void (*write_data_to_dsp)(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
    void (*write_silence_to_dsp)(uint32_t dsp_offset, uint32_t count);
    void (*read_data_from_dsp)(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
};

typedef struct {
    void (*isr_handler)(void);
    /* pcm route control flag */
    bool        isr_enable;
    int32_t     pcm_route_id;

    /* pcm route information from DSP */
    uint16_t    buffer_address;
    uint16_t    channel_number;
    uint16_t    page_number;
    uint16_t    data_length_get;
    uint16_t    data_length_put;
    bool        stereo2mono;
    bool        mono2stereo;

    /* user input buffer */
    ring_buffer_t    *rx_buffer;            /**< Rx buffer- internal use */
    ring_buffer_t    *tx_buffer;            /**< Tx buffer- internal use */
    pcm_route_handle_t  handle;
} pcm_route_t;

void pcm_route_get_length_info(uint32_t *sample_count_get, uint32_t *sample_count_put);
void pcm_route_get_data_from_dsp(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
void pcm_route_get_data_from_dsp_dropR(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
void pcm_route_put_data_to_dsp(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
void pcm_route_put_data_to_dsp_duplicate(uint16_t *buffer, uint32_t dsp_offset, uint32_t length);
void pcm_route_put_silence_to_dsp(uint32_t dsp_offset, uint32_t count);
void pcm_route_put_silence_to_dsp_duplicate(uint32_t dsp_offset, uint32_t count);

void pcm_route_start(void);
void pcm_route_stop(void);
void pcm_route_turn_on_interrupt(void);
void pcm_route_turn_off_interrupt(void);

void pcm_route_isr(void *data);
void pcm_route_callback(void);
void pcm_route_isr_handler(void);

void audio_manager_set_post_process_control(uint16_t mask, uint16_t control);
void audio_manager_clear_post_process_control(uint16_t mask);

#ifdef __cplusplus
}
#endif

#endif  /* defined(HAL_I2S_MODULE_ENABLED)*/

#endif /* __HAL_I2S_INTERNAL_PCM_ROUTE_H__ */

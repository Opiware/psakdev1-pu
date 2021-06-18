/* Copyright Statement:
 *
 */


#ifndef __WAV_CODEC_INTERNAL_H__
#define __WAV_CODEC_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "syslog.h"
#include <string.h>
#include "semphr.h"
#include "audio_codec.h"
#include "wav_codec_exp.h"

#ifndef HAL_AUDIO_MODULE_ENABLED
#error "please turn on audio feature option on hal_feature_config.h"
#endif
#include "hal_audio_internal_service.h"
#include "hal_audio.h"
#include "hal_log.h"

#define TASK_ERROR_LOGGING
#define TASK_WARNING_LOGGING
#define TASK_PROCESS_LOGGING
// #define TASK_DEBUG_LOGGING
// log_create_module(WAV_CODEC, PRINT_LEVEL_INFO);

#if defined(TASK_ERROR_LOGGING)
#define TASK_LOG_E(fmt,arg...)      log_hal_info("[WAV_CODEC][Error] " fmt,##arg)
#else
#define TASK_LOG_E(fmt,arg...)
#endif

#if defined(TASK_WARNING_LOGGING)
#define TASK_LOG_W(fmt,arg...)      log_hal_info("[WAV_CODEC][Warning] " fmt,##arg)
#else
#define TASK_LOG_W(fmt,arg...)
#endif

#if defined(TASK_PROCESS_LOGGING)
#define TASK_LOG_I(fmt,arg...)      log_hal_info("[WAV_CODEC][Info] " fmt,##arg)
#else
#define TASK_LOG_I(fmt,arg...)
#endif

#if defined(TASK_DEBUG_LOGGING)
#define TASK_LOG_D(fmt,arg...)      log_hal_info("[WAV_CODEC][Debug] " fmt,##arg)
#else
#define TASK_LOG_D(fmt,arg...)
#endif

#if 0
#define FUNCTION_IN  TASK_LOG_D("+\n")
#define FUNCTION_OUT TASK_LOG_D("-\n")
#else
#define FUNCTION_IN
#define FUNCTION_OUT
#endif

#define WAV_CODEC_UT_FLOW

#if 0
#define WAV_CODEC_DECODE_PCM_OUTPUT_SIZE      (2048) // IP output
#define WAV_CODEC_DECODE_PCM_RING_BUFFER_SIZE (WAV_CODEC_DECODE_PCM_OUTPUT_SIZE*2) // buffering
#define WAV_CODEC_WAV_BITSTREAM_SIZE          (WAV_CODEC_DECODE_PCM_OUTPUT_SIZE*2) /*It should be a multiple number of 4. minimum size is 256*/ // IP input
#define WAV_CODEC_BS_RING_BUFFER_SIZE         (WAV_CODEC_WAV_BITSTREAM_SIZE)
#endif /* HAL_AUDIO_LOW_POWER_ENABLED */

#define WAV_CODEC_WAV_BITSTREAM_SIZE (16 * 1024) /*It should be a multiple number of 4. minimum size is 256*/ // IP input
#define WAV_CODEC_DECODE_PCM_OUTPUT_SIZE (WAV_CODEC_WAV_BITSTREAM_SIZE*4) // IP output
#define WAV_CODEC_DECODE_PCM_RING_BUFFER_SIZE (WAV_CODEC_WAV_BITSTREAM_SIZE * 4) // buffering
#define WAV_CODEC_BS_RING_BUFFER_SIZE (WAV_CODEC_WAV_BITSTREAM_SIZE * 2) // user fill bs data to dirver

/** @brief audio codec state. */
typedef enum {
    WAV_CODEC_STATUS_NONE          = 0,
    WAV_CODEC_STATUS_ERROR         = 1 << 0,
    WAV_CODEC_STATUS_DSP_UNDERFLOW = 1 << 1,
    WAV_CODEC_STATUS_IN_TASK_LIST  = 1 << 2,
} wav_codec_state_t;

typedef struct {
    audio_codec_media_handle_t  handle;                     /** Wav codec handle. */
    WAV_DEC_HDL                 *wav_handle;                /** Wav codec IP handle. */

    wav_codec_state_t           status;
    ring_buffer_information_t   decoded_pcm_ring;
    bool                        linear_data;
    bool                        eof_flag;
    bool                        decode_end_flag;
    uint8_t                     *decoder_working_buf;       /** Wav codec IP working buffer. */
    uint8_t                     *decoder_input_buf;         /** bitstream buffer*/
    uint8_t                     *decoder_output_buf;        /** pcm buffer*/
    unsigned int                decoder_input_buf_offset;   /** record consumed data(decoder use) offset*/
    unsigned int                decoder_output_buf_offset;  /** record consumed data(fill to decodec_pcm_ring) offset*/
    unsigned int                decoder_working_buf_size;   /** Wav codec IP working buffer size. */
    unsigned int                decoder_input_buf_size;     /** bitstream buffer size*/
    unsigned int                decoder_output_buf_size;    /** pcm buffer size*/
    unsigned int                decode_size;
    unsigned int                remain_bs;                  /* the total audio data number (bytes) in the file */
    SemaphoreHandle_t           semaphore_handle;
#ifdef WAV_CODEC_UT_FLOW
    uint8_t                     *pcm_ring;                  /** pcm ring buffer. */
    unsigned int                pcm_ring_size;              /** pcm ring buffer size. */
#endif
} wav_codec_internal_handle_t;


#ifdef __cplusplus
}
#endif

#endif  /*__WAV_CODEC_INTERNAL_H__*/


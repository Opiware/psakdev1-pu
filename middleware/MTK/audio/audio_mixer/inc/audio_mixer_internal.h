/* Copyright Statement:
 *
 */

#ifndef __AUDIO_MIXER_INTERNAL_H__
#define __AUDIO_MIXER_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_audio.h"
#include "bli_exp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define AUDIO_MIXER_MAX_TRACK_NUMBER   (2)
#define AUDIO_MIXER_BLOCK_MS           (64)
#define AUDIO_MIXER_BLOCK_MAX_SIZE     (48*4*AUDIO_MIXER_BLOCK_MS)
#define AUDIO_MIXER_BUFFER_SIZE        (16*1024)
#define AUDIO_MIXER_PCM_ROUTE_MAX_SIZE (4096)
    
#define AUDIO_MIXER_NOTIFY_THRESHOLD   (8*1024)
    
#define AUDIO_MIXER_TRACK_BUFFER_SIZE  (16*1024)
#define AUDIO_MIXER_TRACK_BUFFER_MS    (100)

#define AUDIO_MIXER_UNIT_GAIN          (0x8000)

#define AUDIO_MIXER_FREQ_L_BOUND       (104000)

typedef enum {
    AUDIO_MIXER_STATE_MACHINE_IDLE,
    AUDIO_MIXER_STATE_MACHINE_CONFIGURED,
    AUDIO_MIXER_STATE_MACHINE_RUNNING
} audio_mixer_state_machine_t;

typedef enum {
    AUDIO_MIXER_QUEUE_EVENT_NONE = 0,
    AUDIO_MIXER_QUEUE_EVENT_PROCESS,
    AUDIO_MIXER_QUEUE_EVENT_FILL_DATA,
    AUDIO_MIXER_QUEUE_EVENT_END,
    AUDIO_MIXER_QUEUE_EVENT_TOTAL
} audio_mixer_queue_event_id_t;

typedef enum {
    AUDIO_MIXER_EOF_STATE_NONE,
    AUDIO_MIXER_EOF_STATE_FLUSH_TRACK,
    AUDIO_MIXER_EOF_STATE_FLUSH_MIXER,
    AUDIO_MIXER_EOF_STATE_FLUSH_HAL
} audio_mixer_eof_state_t;

typedef enum {
    AUDIO_MIXER_CHANNEL_CONVERT_NONE = 0,
    AUDIO_MIXER_CHANNEL_CONVERT_STEREO_TO_MONO,
    AUDIO_MIXER_CHANNEL_CONVERT_MONO_TO_STEREO
} audio_mixer_channel_convert_t;

typedef struct {
    audio_mixer_queue_event_id_t    id;
    void                            *parameter;
} audio_mixer_queue_event_t;

typedef struct {
    uint8_t                         *base_address_alloc;
    uint8_t                         *base_address;
    uint32_t                        size;
    uint32_t                        read;
    uint32_t                        write;
} track_buffer_t;

typedef struct {
    // Basic info
    hal_audio_sampling_rate_t       sampling_rate_enum;
    hal_audio_channel_number_t      channel_number_enum;
    audio_mixer_role_t              role;

    uint32_t                        sampling_rate;
    uint8_t                         channel_number;
    
    audio_mixer_state_machine_t     state;
    audio_mixer_eof_state_t         eof_state;
    int32_t                         eof_remaining_size;

    // Gain related
    int32_t                         current_gain;

    // Callback related
    bool                            waiting;
    hal_audio_stream_out_callback_t callback;
    void                            *callback_user_data;

    // Buffer information
    track_buffer_t                  source_buffer;

    // SRC related
    uint8_t                         *bli_allocate_buffer_alloc;
    void                            *bli_allocate_buffer;
    BLI_HANDLE                      *bli_handle;
    audio_mixer_channel_convert_t   channel_convert;
} track_info_t;

typedef struct {
    // Track resource is occupied or not
    uint32_t                        track_flag;
    uint8_t                         active_main_track_count;
    uint8_t                         active_side_track_count;

    // Track information
    track_info_t                    track[AUDIO_MIXER_MAX_TRACK_NUMBER];
    int32_t                         main_track_gain;
    int32_t                         side_track_gain;

    // HAL information
    uint32_t                        hal_sampling_rate;
    uint16_t                        hal_channel_number;
    hal_audio_sampling_rate_t       hal_sampling_rate_enum;
    hal_audio_channel_number_t      hal_channel_number_enum;
    bool                            hal_is_runnung;
    bool                            hal_is_pcm_route;
    bool                            hal_is_p2w;
    bool                            hal_is_aws;
    bool                            hal_eof_waiting;
    bool                            hal_callback_waiting;
    uint8_t                         hal_eof_waiting_count;
    int32_t                         pcm_route_current_gain;
    int32_t                         hal_pcm_route_id;
    uint8_t                         *hal_memory_alloc;
    void                            *hal_memory;
    uint32_t                        hal_memory_size;

    // Task related
    TaskHandle_t                    task_handle;
    QueueHandle_t                   queue_handle;
    
    // Mixer Buffer
    uint8_t                         *resample_temp_block_alloc;
    uint8_t                         *resample_temp_block;
    uint8_t                         *mixer_temp_block_alloc;
    uint8_t                         *mixer_temp_block;
    uint8_t                         *pcm_route_buffer_alloc;
    uint8_t                         *pcm_route_buffer;
    track_buffer_t                  mixer_buffer;
    uint32_t                        mixer_block_size;
    
    // Simplified Buffer Operation
    bool                            f_direct_track_buffer;
    track_buffer_t                  *p_buffer_to_hal;
    
} audio_mixer_t;

#ifdef __cplusplus
}
#endif

#endif  /*__AUDIO_MIXER_INTERNAL_H__*/

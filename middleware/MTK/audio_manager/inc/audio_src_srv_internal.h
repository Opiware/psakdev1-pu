/* Copyright Statement:
 *
 */

#ifndef __AUDIO_SRC_SRV_INTERNAL_H__
#define __AUDIO_SRC_SRV_INTERNAL_H__

#include <stdint.h>
#include <syslog.h>
#include "audio_src_srv.h"


typedef enum {
    AUDIO_SRC_SRV_MSG_START = 0,
    AUDIO_SRC_SRV_MSG_UNAVAILABLE,
    AUDIO_SRC_SRV_MSG_READY,
    AUDIO_SRC_SRV_MSG_PLAY,
    AUDIO_SRC_SRV_MSG_STOP,
    AUDIO_SRC_SRV_MSG_PLAYING,
} audio_src_srv_message_t;

typedef struct {
    audio_src_srv_state_t state;
    audio_src_srv_transient_state_t substate;
    uint32_t play_count;

    audio_src_srv_handle_t *running;
} audio_src_srv_context_t;



#define AUDIO_SRC_SRV_SET_FLAG(HANDLE, FLAG) ((HANDLE->flag) |= (FLAG))
#define AUDIO_SRC_SRV_RESET_FLAG(HANDLE, FLAG) ((HANDLE->flag) &= ~(FLAG))

#ifndef NULL
#define NULL ((void *)0)       /**<Default value of the pointer.*/
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define audio_src_srv_report(_message,...) LOG_I(AudSrc, (_message), ##__VA_ARGS__)

audio_src_srv_context_t *audio_src_srv_get_ctx(void);

void audio_src_srv_update_psedev_state(audio_src_srv_handle_t *handle, audio_src_srv_state_t state);

void audio_src_srv_state_machine_handle(audio_src_srv_handle_t *handle, audio_src_srv_message_t msg_id, void *param);

audio_src_srv_handle_t *audio_src_srv_check_waiting_list(void);

void audio_src_srv_update_psedev_play_count(audio_src_srv_handle_t *handle);

void audio_src_srv_process_psedev_event(audio_src_srv_handle_t *handle, audio_src_srv_event_t evt_id);

#ifdef __cplusplus
}
#endif

#endif /* __AUDIO_SRC_SRV_INTERNAL_H__ */


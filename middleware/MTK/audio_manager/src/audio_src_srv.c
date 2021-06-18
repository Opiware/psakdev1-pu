/* Copyright Statement:
 *
 */

#include <string.h>
#include "stdint.h"
#include "audio_src_srv.h"
#include "audio_src_srv_internal.h"


/* multi source handle */
audio_src_srv_handle_t g_audio_src_srv_handle[AUDIO_SRC_SRV_PSEUDO_DEVICE_NUM];


static void audio_src_srv_reset_handle(audio_src_srv_handle_t *handle)
{
    if (handle) {
        memset(handle, 0x00, sizeof(audio_src_srv_handle_t));
    }
}


audio_src_srv_handle_t *audio_src_srv_construct_handle(audio_src_srv_pseudo_device_t type)
{
    int32_t i = 0;
    audio_src_srv_handle_t *hd = NULL;
    // mutex lock
    audio_src_srv_mutex_lock();
    for (i = 0; i < AUDIO_SRC_SRV_PSEUDO_DEVICE_NUM; ++i) {
        if (!(g_audio_src_srv_handle[i].flag & AUDIO_SRC_SRV_FLAG_USED)) {
            hd = &g_audio_src_srv_handle[i];
            // audio_src_srv_reset_handle(handle);
            hd->type = type;
            //hd->flag |= AUDIO_SRC_SRV_FLAG_USED;
            AUDIO_SRC_SRV_SET_FLAG(hd, AUDIO_SRC_SRV_FLAG_USED);
            break;
        }
    }

    if (!hd) {
        // exception: no source handle, check
        audio_src_srv_report("[AudSrc]construct_handle--error\n");
    }

    // mutex unlock
    audio_src_srv_mutex_unlock();

    return hd;
}


void audio_src_srv_destruct_handle(audio_src_srv_handle_t *handle)
{
    // mutex lock
    audio_src_srv_mutex_lock();
    audio_src_srv_reset_handle(handle);
    // mutex unlock
    audio_src_srv_mutex_unlock();
}


void audio_src_srv_add_waiting_list(audio_src_srv_handle_t *handle)
{
    // mutex lock
    audio_src_srv_mutex_lock();
    if (handle) {
        audio_src_srv_report("[AudSrc]add_waiting_list--hd: 0x%x, type: %d, state: %d\n", handle, handle->type, handle->state);
        AUDIO_SRC_SRV_SET_FLAG(handle, AUDIO_SRC_SRV_FLAG_WAITING);
    } else {
        audio_src_srv_report("[AudSrc]add_waiting_list(err)\n");
    }
    // mutex unlock
    audio_src_srv_mutex_unlock();
}


void audio_src_srv_del_waiting_list(audio_src_srv_handle_t *handle)
{
    // mutex lock
    audio_src_srv_mutex_lock();
    if (handle) {
        audio_src_srv_report("[AudSrc]del_waiting_list--hd: 0x%x, type: %d, state: %d\n", handle, handle->type, handle->state);
        AUDIO_SRC_SRV_RESET_FLAG(handle, AUDIO_SRC_SRV_FLAG_WAITING);
    } else {
        audio_src_srv_report("[AudSrc]del_waiting_list(err)\n");
    }
    // mutex unlock
    audio_src_srv_mutex_unlock();
}


void audio_src_srv_update_state(audio_src_srv_handle_t *handle, audio_src_srv_event_t evt_id)
{
    // mutex lock
    audio_src_srv_mutex_lock();
    if (handle) {
        audio_src_srv_process_psedev_event(handle, evt_id);
    } else {
        audio_src_srv_report("[AudSrc]update_state(err)\n");
    }
    // mutex unlock
    audio_src_srv_mutex_unlock();
}


const audio_src_srv_handle_t *audio_src_srv_get_pseudo_device(void)
{
    return g_audio_src_srv_handle;
}


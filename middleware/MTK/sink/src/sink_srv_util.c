/* Copyright Statement:
 *
 */


#include <stdint.h>
#include "sink_srv_util.h"

extern void bt_sink_srv_music_drv_play(void *param);

extern void bt_sink_srv_music_drv_stop(void *param);

int32_t sink_srv_util_send_event(sink_srv_event_t evt_id, void *param)
{
    int32_t ret = 0;

    if (evt_id == SINK_SRV_EVT_CODEC_PLAY) {
        bt_sink_srv_music_drv_play(param);
    } else if (evt_id == SINK_SRV_EVT_CODEC_STOP) {
        bt_sink_srv_music_drv_stop(param);
    } else {
        ;
    }

    return ret;
}


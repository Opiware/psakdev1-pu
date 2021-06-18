/* Copyright Statement:
 *
 */

#ifndef __SINK_SRV_UTIL_H__
#define __SINK_SRV_UTIL_H__

#include "stdint.h"

typedef enum {
    SINK_SRV_EVT_CODEC_PLAY,
    SINK_SRV_EVT_CODEC_STOP,
} sink_srv_event_t;

int32_t sink_srv_util_send_event(sink_srv_event_t evt_id, void *param);

#ifdef __cplusplus
}
#endif

#endif

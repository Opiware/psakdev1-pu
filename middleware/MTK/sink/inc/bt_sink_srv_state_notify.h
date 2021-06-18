/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_STATE_NOTIFY_H__
#define __BT_SINK_SRV_STATE_NOTIFY_H__

#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SINK_SRV_STATE_FLAG_NONE               (0x00)
#define BT_SINK_SRV_STATE_FLAG_CONNECTED (0x01)
typedef uint8_t bt_sink_srv_state_flags_t;    

void bt_sink_srv_state_set(bt_sink_srv_state_t state);
void bt_sink_srv_state_reset(bt_sink_srv_state_t state);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_STATE_NOTIFY_H__ */


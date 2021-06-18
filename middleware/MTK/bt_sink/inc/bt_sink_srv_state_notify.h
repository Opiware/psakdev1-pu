/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_STATE_NOTIFY_H__
#define __BT_SINK_SRV_STATE_NOTIFY_H__

#include <stdint.h>
#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

void bt_sink_srv_state_set(bt_sink_srv_state_t state);

void bt_sink_srv_state_reset(bt_sink_srv_state_t state);

bt_sink_srv_state_t bt_sink_srv_state_query(void);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_STATE_NOTIFY_H__ */


/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_ACTION_HANDLE_H__
#define __BT_SINK_SRV_ACTION_HANDLE_H__

#include <stdint.h>
#include "bt_gap.h"
#include "bt_sink_srv_resource.h"
#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef bt_sink_srv_status_t (*bt_sink_action_callback_t)(bt_sink_srv_action_t action, void *parameters);

typedef struct {
    bt_sink_srv_action_t action;
    bt_sink_action_callback_t callback;
} bt_sink_srv_action_callback_table_t;

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_ACTION_HANDLE_H__ */

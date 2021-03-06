/* Copyright Statement:
 *
 */

#include "bt_sink_srv.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_state_notify.h"

static bt_sink_srv_state_t bt_sink_srv_state;

static void bt_sink_srv_state_change_notify(bt_sink_srv_state_t previous, bt_sink_srv_state_t now)
{
    bt_sink_srv_event_param_t *params = bt_sink_srv_memory_alloc(sizeof(*params));

    params->state_change.previous = previous;
    params->state_change.now = now;

    bt_sink_srv_event_callback(BT_SINK_SRV_EVENT_STATE_CHANGE, params);
    bt_sink_srv_memory_free(params);
}

void bt_sink_srv_state_set(bt_sink_srv_state_t state)
{
    if (!(bt_sink_srv_state & state) || ((bt_sink_srv_state & state) == BT_SINK_SRV_STATE_HELD_ACTIVE)) {
        if (state >= BT_SINK_SRV_STATE_INCOMING && state <= BT_SINK_SRV_STATE_MULTIPARTY) {
            bt_sink_srv_state &= 0xF00F;
        }
        bt_sink_srv_state_change_notify(bt_sink_srv_state, (bt_sink_srv_state_t)(bt_sink_srv_state | state));
        bt_sink_srv_state |= state;
    }
    bt_sink_srv_report("[Sink][State] set:0x%x, now:0x%x", state, bt_sink_srv_state);
}

void bt_sink_srv_state_reset(bt_sink_srv_state_t state)
{
    if (bt_sink_srv_state & state) {
        bt_sink_srv_state_t previous_state = bt_sink_srv_state;

        if (BT_SINK_SRV_STATE_CONNECTED == state) {
            bt_sink_srv_state &= 0x000F;
        }
        if (BT_SINK_SRV_STATE_POWER_ON == state) {
            bt_sink_srv_state = BT_SINK_SRV_STATE_NONE;
        }
        bt_sink_srv_state &= (~state);
        bt_sink_srv_state_change_notify(previous_state, bt_sink_srv_state);
    }
    bt_sink_srv_report("[Sink][State] reset:0x%x, now:0x%x", state, bt_sink_srv_state);
}

bt_sink_srv_state_t bt_sink_srv_state_query(void)
{
    return bt_sink_srv_state;
}

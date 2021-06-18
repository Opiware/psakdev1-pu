/* Copyright Statement:
 *
 */

#include "bt_sink_srv.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_state_notify.h"

static bt_sink_srv_state_t bt_sink_srv_state = BT_SINK_SRV_STATE_NONE;
static bt_sink_srv_state_flags_t bt_sink_srv_state_flag = BT_SINK_SRV_STATE_FLAG_NONE;

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
    if (BT_SINK_SRV_STATE_CONNECTED == state) {
        bt_sink_srv_state_flag |=  BT_SINK_SRV_STATE_FLAG_CONNECTED;
    } else if (BT_SINK_SRV_STATE_POWER_ON == state ||BT_SINK_SRV_STATE_NONE == state ) {
        bt_sink_srv_state_flag &= ~BT_SINK_SRV_STATE_FLAG_CONNECTED;
    }
    bt_sink_srv_report("[Sink][State] set prev:0x%x, next:0x%x", bt_sink_srv_state, state);

    /*local player is playing then stop immediately for call interrupt mp3 case .*/
    if ( state == BT_SINK_SRV_STATE_LOCAL_PLAYING ) {
        if (bt_sink_srv_state >= BT_SINK_SRV_STATE_INCOMING && bt_sink_srv_state <= BT_SINK_SRV_STATE_MULTIPARTY) {
            return;
        }
    }

    if (bt_sink_srv_state !=state) {
        bt_sink_srv_state_change_notify(bt_sink_srv_state, state);
        /*Special case for connected when local player is playing*/
        if ((state == BT_SINK_SRV_STATE_CONNECTED || state == BT_SINK_SRV_STATE_POWER_ON ) && 
            bt_sink_srv_state == BT_SINK_SRV_STATE_LOCAL_PLAYING ) {
             bt_sink_srv_state_change_notify(state, bt_sink_srv_state);
             state = BT_SINK_SRV_STATE_LOCAL_PLAYING;
        }
        bt_sink_srv_state = state;
    }
}

void bt_sink_srv_state_reset(bt_sink_srv_state_t state)
{
    bt_sink_srv_report("[Sink][State] reset prev:0x%x, next:0x%x", bt_sink_srv_state, state);

   if (state == BT_SINK_SRV_STATE_STREAMING  || state == BT_SINK_SRV_STATE_LOCAL_PLAYING) {
        if (bt_sink_srv_state >= BT_SINK_SRV_STATE_INCOMING && bt_sink_srv_state <= BT_SINK_SRV_STATE_MULTIPARTY) {
            return;
        }
        if (bt_sink_srv_state_flag & BT_SINK_SRV_STATE_FLAG_CONNECTED) {
            state = BT_SINK_SRV_STATE_CONNECTED;
        } else {
            state = BT_SINK_SRV_STATE_POWER_ON;
        }
   }
    if (bt_sink_srv_state !=state) {
        bt_sink_srv_state_change_notify(bt_sink_srv_state, state);
        bt_sink_srv_state = state;
    }
    bt_sink_srv_report("[Sink][State] final :0x%x", bt_sink_srv_state);
}

bt_sink_srv_state_t bt_sink_srv_state_query(void)
{
    return bt_sink_srv_state;
}


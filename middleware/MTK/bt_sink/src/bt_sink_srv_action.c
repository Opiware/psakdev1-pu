/* Copyright Statement:
 *
 */

#include "bt_gap.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv_conmgr.h"
#include "bt_sink_srv_hf.h"
#include "bt_sink_srv_avrcp.h"
#include "bt_sink_srv_a2dp.h"
#include "bt_sink_srv_pbapc.h"
#include "bt_sink_srv_spp.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv_aws.h"
#include "bt_sink_srv_ami.h"

const static bt_sink_srv_action_callback_table_t bt_sink_srv_action_callback_table[] = {
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_cm_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_hf_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_a2dp_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_avrcp_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_pbapc_action_handler},
    #ifdef __BT_AWS_SUPPORT__
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_aws_action_handler},
    #endif
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_spp_action_handler}
};

bt_sink_srv_status_t bt_sink_srv_action_send(bt_sink_srv_action_t action, void *parameters)
{
    bt_sink_srv_status_t result = BT_SINK_SRV_STATUS_SUCCESS;
    uint32_t index;

    bt_sink_srv_report("[Sink] bt_sink_srv_action_send, 0x%x", action);

    for (index = 0; index < sizeof(bt_sink_srv_action_callback_table) / sizeof(bt_sink_srv_action_callback_table_t); index++) {
        if (bt_sink_srv_action_callback_table[index].action == BT_SINK_SRV_ACTION_ALL) {
            if (NULL != bt_sink_srv_action_callback_table[index].callback) {
                result = bt_sink_srv_action_callback_table[index].callback(action, parameters);
                if (BT_SINK_SRV_STATUS_EVENT_STOP == result) {
                    // TRACE
                    break;
                }
            } else {
                // TRACE
            }
        } else if (bt_sink_srv_action_callback_table[index].action == action) {
            result = bt_sink_srv_action_callback_table[index].callback(action, parameters);
            if (BT_SINK_SRV_STATUS_EVENT_STOP == result) {
                // TRACE
                break;
            }
        } else {
            // TRACE
        }
    }
    return result;
}


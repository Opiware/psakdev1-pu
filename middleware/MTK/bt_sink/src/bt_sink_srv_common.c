/* Copyright Statement:
 *
 */

#include <string.h>
#include "bt_sink_srv_resource.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_conmgr.h"
#include "bt_gap_le.h"
#include "bt_system.h"
#include "bt_sink_srv_hf.h"
#include "bt_sink_srv_a2dp.h"
#include "bt_sink_srv_avrcp.h"
#include "bt_sink_srv_pbapc.h"
#include "bt_sink_srv_spp.h"
#include "bt_sink_srv_ami.h"
#ifdef __BT_AWS_SUPPORT__
#include "bt_sink_srv_aws.h"
#endif

bt_sink_srv_features_config_t bt_sink_srv_features_config;

void bt_sink_srv_config_features(bt_sink_srv_features_config_t *features)
{
    bt_sink_srv_memcpy(&bt_sink_srv_features_config, features, sizeof(bt_sink_srv_features_config_t));
}

const bt_sink_srv_features_config_t *bt_sink_srv_get_features_config(void)
{
    return &bt_sink_srv_features_config;
}


bt_status_t bt_sink_srv_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer)
{
    bt_status_t result = BT_STATUS_SUCCESS;
    uint32_t moduel = msg & 0xFF000000;

    switch (moduel) {
        case BT_MODULE_SYSTEM:
            result = bt_sink_srv_cm_system_callback(msg, status, buffer);
            break;

        case BT_MODULE_GAP:
            result = bt_sink_srv_cm_gap_callback(msg, status, buffer);
            break;

        case BT_MODULE_HFP:
            result = bt_sink_srv_hf_common_callback(msg, status, buffer);
            break;

        case BT_MODULE_A2DP:
            result = bt_sink_srv_a2dp_common_callback(msg, status, buffer);
            break;

        case BT_MODULE_AVRCP:
            result = bt_sink_srv_avrcp_common_callback(msg, status, buffer);
            break;

        case BT_MODULE_PBAPC:
            result = bt_sink_srv_pbapc_common_callback(msg, status, buffer);
            break;

        case BT_MODULE_SPP:
            //result = bt_sink_srv_spp_common_callback(msg, status, buffer);
            break;

        #ifdef __BT_AWS_SUPPORT__
        case BT_MODULE_AWS:
            result = bt_sink_srv_aws_common_callback(msg, status, buffer);
            break;
        #endif

        default:
            bt_sink_srv_report("[Sink] Unknown Bluetooth MSG:0x%x, status:0x%x", msg, status);
            break;
    }
    return result;
}


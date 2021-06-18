/* Copyright Statement:
 *
 */

#include <string.h>
#include "bt_sink_srv_resource.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv.h"
#include "bt_system.h"
#include "bt_sink_srv_spp.h"
#include "bt_sink_srv_action.h"

bt_sink_srv_spp_context_t *bt_sink_srv_spp_device;

void bt_sink_srv_spp_disconnect(bt_bd_addr_t *addr)
{
    if (NULL != bt_sink_srv_spp_device && 0 != bt_sink_srv_spp_device->spp_handle
            && 0 == bt_sink_srv_memcmp((void *)addr, (void *)&bt_sink_srv_spp_device->bt_addr, sizeof(bt_bd_addr_t))) {
        bt_spp_disconnect(bt_sink_srv_spp_device->spp_handle);
    }
}

bt_sink_srv_status_t bt_sink_srv_spp_action_handler(bt_sink_srv_action_t action, void *parameters)
{
    switch (action) {
        case BT_SINK_SRV_ACTION_PROFILE_DISCONNECT: {
            bt_sink_srv_profile_connection_action_t *action_param = (bt_sink_srv_profile_connection_action_t *)parameters;
            if (~action_param->profile_connection_mask & BT_SINK_SRV_PROFILE_CONNECTION_TYPE_AWS) {
                // no aws connection
                if (NULL != bt_sink_srv_spp_device && 0 != bt_sink_srv_spp_device->spp_handle) {
                    bt_spp_disconnect(bt_sink_srv_spp_device->spp_handle);
                }
            }
        }
        break;

        default:
            break;
    }
    return BT_SINK_SRV_STATUS_SUCCESS;
}

bt_status_t bt_sink_srv_spp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer)
{
    bt_sink_srv_report("[Sink][SPP] SDK msg:0x%x", msg);

    switch (msg) {
        case BT_SPP_CONNECT_IND: {
            bt_spp_connect_ind_t *message = (bt_spp_connect_ind_t *)buffer;

            bt_sink_srv_spp_device = (bt_sink_srv_spp_context_t *)bt_sink_srv_memory_alloc(sizeof(bt_sink_srv_spp_context_t));
            bt_sink_srv_memcpy((void *)&bt_sink_srv_spp_device->bt_addr,
                               (void *)message->address,
                               sizeof(bt_bd_addr_t));
            bt_sink_srv_spp_device->spp_handle = message->handle;
        }
        break;

        case BT_SPP_CONNECT_CNF: {
            if (BT_STATUS_SUCCESS == status) {
                bt_sink_srv_action_send(BT_SINK_SRV_ACTION_CONNECT, bt_sink_srv_spp_device);
            } else {
                bt_sink_srv_memory_free(bt_sink_srv_spp_device);
                bt_sink_srv_spp_device = NULL;
            }
        }
        break;

        case BT_SPP_DISCONNECT_IND: {
            bt_sink_srv_memory_free(bt_sink_srv_spp_device);
            bt_sink_srv_spp_device = NULL;
        }
        break;

        default:
            break;
    }
    return BT_STATUS_SUCCESS;
}


/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_PBAPC_H__
#define __BT_SINK_SRV_PBAPC_H__

#include "bt_type.h"
#include "bt_sink_srv.h"
#include "bt_sink_srv_conmgr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*bt_sink_srv_pbapc_get_name_callback_t)(bt_bd_addr_t *address, bt_sink_srv_pbapc_record_t *record, void *user_data);

typedef struct {
    uint32_t pbapc_handle;
    bt_sink_srv_profile_connection_state_t state;
    bt_sink_srv_pbapc_record_t *pending;
    void *user_data;
    bt_sink_srv_pbapc_get_name_callback_t callback;
} bt_sink_srv_pbapc_context_t;

bt_status_t bt_sink_srv_pbapc_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

bt_sink_srv_status_t bt_sink_srv_pbapc_action_handler(bt_sink_srv_action_t action, void *parameters);

bt_status_t bt_sink_srv_pbapc_get_name_from_local(bt_bd_addr_t *address, bt_sink_srv_pbapc_record_t *record);

bt_status_t bt_sink_srv_pbapc_get_name_from_remote(bt_bd_addr_t *address,
        uint8_t *number,
        void *user_data,
        bt_sink_srv_pbapc_get_name_callback_t callback);

bt_status_t bt_sink_srv_pbapc_connect(bt_bd_addr_t *address);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_PBAPC_H__ */


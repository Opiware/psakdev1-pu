/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_SPP_H__
#define __BT_SINK_SRV_SPP_H__

#include <stdint.h>
#include "bt_hfp.h"
#include "bt_type.h"
#include "bt_sink_srv_resource.h"
#include "bt_spp.h"

typedef struct {
    bt_bd_addr_t bt_addr;
    uint32_t     spp_handle;
} bt_sink_srv_spp_context_t;

bt_sink_srv_status_t bt_sink_srv_spp_action_handler(bt_sink_srv_action_t action, void *parameters);

void bt_sink_srv_spp_disconnect(bt_bd_addr_t *addr);

bt_status_t bt_sink_srv_spp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

#endif /* __BT_SINK_SRV_SPP_H__ */

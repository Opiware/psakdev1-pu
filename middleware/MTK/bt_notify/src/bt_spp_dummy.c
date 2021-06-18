/* Copyright Statement:
 *
 */

#include "bt_spp_dummy.h"

 bt_status_t bt_spp_connect(
     uint32_t *handle,
     const bt_bd_addr_t *address,
     const uint8_t *uuid128)
{
    return BT_STATUS_SUCCESS;
}

bt_status_t bt_spp_connect_response(uint32_t handle, bool accept)
{
    return BT_STATUS_SUCCESS;
}


bt_status_t bt_spp_send(
        uint32_t handle,
        uint8_t *packet,
        uint16_t packet_length)
{
    return BT_STATUS_SUCCESS;
}

bt_status_t bt_spp_disconnect(uint32_t handle)
{
    return BT_STATUS_SUCCESS;
}

void bt_spp_hold_data(uint8_t *data)
{
    return;
}

void bt_spp_release_data(uint8_t *data)
{
    return;
}



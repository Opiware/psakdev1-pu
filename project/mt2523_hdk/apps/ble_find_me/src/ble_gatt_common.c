/* Copyright Statement:
 *
 */

#include "bt_gatts.h"
#include "ble_gatt_common.h"
#include "ble_gatt_utils.h"
#include "ble_gatt_connect.h"

//server collects all service
const bt_gatts_service_t *bt_if_gatt_server[] = {
    &bt_if_gap_service,
    &bt_if_gatt_service,
    //&bt_if_lls_service,
    &bt_if_ias_service,
    NULL
};


/*****************************************************************************
* FUNCTION
*  bt_get_gatt_server
* DESCRIPTION
* Get GATT server
* PARAMETERS
*  void
* RETURNS
*  bt_gatts_service_t
*****************************************************************************/
const bt_gatts_service_t **bt_get_gatt_server()
{
    return bt_if_gatt_server;
}


/*****************************************************************************
* FUNCTION
*  bt_app_event_callback
* DESCRIPTION
* Handle le event
* PARAMETERS
*  msg         [IN]        Event message ID
*  status      [IN]        Event status
*  buff        [IN]        Event result
* RETURNS
*  bt_status_t
*****************************************************************************/
bt_status_t bt_app_event_callback(bt_msg_type_t msg, bt_status_t status,
    void *buff)
{
    return ble_app_event_handle(msg, status, buff);
}


/*****************************************************************************
* FUNCTION
*  ble_app_event_handle
* DESCRIPTION
* Handle le event
* PARAMETERS
*  msg         [IN]        Event message ID
*  status      [IN]        Event status
*  buff        [IN]        Event result
* RETURNS
*  bt_status_t
*****************************************************************************/
bt_status_t ble_app_event_handle(bt_msg_type_t msg, bt_status_t status,
    void *buff)
{
    bt_status_t ret = BT_STATUS_SUCCESS;
    int32_t err_1st = BLE_GATT_ERR_FAIL_1ST;
    uint32_t module = msg & 0xFF000000;

    if ((BT_MODULE_GAP == module) ||
        (BT_MODULE_GATT == module) ||
        (BT_MODULE_SYSTEM == module)) {
    ble_gatt_report("[gatt][common]ent_hdr(s)--msg: 0x%x, status: %d, buff: 0x%x",
        msg, status, buff);
    }

    if (BT_MODULE_GAP == module) {
        ret = ble_gap_event_handle(msg, status, buff);
    } else if (BT_MODULE_GATT == module) {
        ret = ble_gatt_event_handle(msg, status, buff);
    } else if (BT_MODULE_SYSTEM == module) {
        ret = ble_gap_event_handle(msg, status, buff);
    }

    if ((BT_MODULE_GAP == module) ||
        (BT_MODULE_GATT == module) ||
        (BT_MODULE_SYSTEM == module)) {
    ble_gatt_report("[gatt][common]ent_hdr(e)--ret: %d, err_1st: %d\n", ret,
        err_1st);
    }

    return ret;
}


/*****************************************************************************
* FUNCTION
*  bt_gap_le_get_local_config
* DESCRIPTION
* Get LE configuration
* PARAMETERS
* RETURNS
*  bt_gap_le_local_config_req_ind_t
*****************************************************************************/
bt_gap_le_local_config_req_ind_t *bt_gap_le_get_local_config(void)
{
    return ble_gatt_connect_gap_le_get_local_config();
}


/*****************************************************************************
* FUNCTION
*  bt_gap_le_get_bonding_info
* DESCRIPTION
* Get LE bonding information
* PARAMETERS
*  remote_addr      [IN]        Bluetooth address
* RETURNS
*  bt_gap_le_bonding_info_t
*****************************************************************************/
bt_gap_le_bonding_info_t *bt_gap_le_get_bonding_info(const bt_addr_t remote_addr)
{
    return ble_gatt_connect_gap_le_get_bonding_info(remote_addr);
}


/*****************************************************************************
* FUNCTION
*  bt_gap_le_get_pairing_config
* DESCRIPTION
* Get LE pairing information
* PARAMETERS
*  ind      [IN]        Bonding ind
* RETURNS
*  bt_status_t
*****************************************************************************/
bt_status_t bt_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind)
{
    return bt_gatt_connect_gap_le_get_pairing_config(ind);
}


/*****************************************************************************
* FUNCTION
*  ble_gatt_event_handle
* DESCRIPTION
* Handle le event
* PARAMETERS
*  msg         [IN]        Event message ID
*  status      [IN]        Event status
*  buff        [IN]        Event result
* RETURNS
*  bt_status_t
*****************************************************************************/
bt_status_t ble_gatt_event_handle(bt_msg_type_t msg, bt_status_t status,
    void *buff)
{
    bt_status_t ret = BT_STATUS_SUCCESS;

    switch (msg) {
        case BT_GATTC_DISCOVER_PRIMARY_SERVICE_BY_UUID: {
            break;
        }
        case BT_GATTC_FIND_INCLUDED_SERVICES: {
            break;
        }
        case BT_GATTC_DISCOVER_CHARC: {
            break;
        }
        case BT_GATTC_DISCOVER_CHARC_DESCRIPTOR: {
            break;
        }
        case BT_GATTC_WRITE_CHARC: {
            break;
        }
        case BT_GATTC_CHARC_VALUE_NOTIFICATION: {
            break;
        }

        default:
            break;
    }

    ble_gatt_report("[gatt][common]ent_hdr(e)--ret: %d\n", ret);
    return ret;
}


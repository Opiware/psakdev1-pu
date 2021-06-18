/* Copyright Statement:
 *
 */

#ifndef __BLE_GATT_CONNECT_H__
#define __BLE_GATT_CONNECT_H__

#include "bt_type.h"
#include "stdint.h"
#include "ble_gatt_common.h"


#define BLE_GATT_CONNECT_FLAG_INIT                 (0x0001)

/* device info flag */
#define BLE_GATT_CONNECT_INFO_FLAG_USED            (0x01)

#define BT_ADDR_TYPE_UNKNOW 0xFF

#define BLE_GATT_DEV_NAME                          "MediaTek_PXP"

typedef enum {
    BLE_GATT_CONNECT_INFO_HANDLE,   /* 0 */
    BLE_GATT_CONNECT_INFO_ADDR,   /* 1 */
    BLE_GATT_CONNECT_INFO_UNUSED, /* 2 */

    BLE_GATT_CONNECT_INFO_TOTAL
} ble_gatt_connect_info_type_t;

typedef struct {
    uint8_t flag;
    bt_handle_t       handle;
    bt_role_t         role;
    bt_addr_t         peer_addr;
    uint8_t           gatts_wait_att_rx_opcode; //use to wait handle value confirmation.
} ble_gatt_connect_info_t;

typedef struct {
    bt_addr_t bt_addr;
    bt_gap_le_bonding_info_t info;
} ble_gatt_bonded_info_t;


typedef struct {
    uint32_t flag;
    ble_gatt_connect_info_t *conn_info;
} ble_gatt_connect_context_t;


bt_gap_le_local_config_req_ind_t *ble_gatt_connect_gap_le_get_local_config(void);

bt_gap_le_bonding_info_t *ble_gatt_connect_gap_le_get_bonding_info(const bt_addr_t remote_addr);

bt_status_t bt_gatt_connect_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind);

bt_status_t ble_gap_event_handle(bt_msg_type_t msg, bt_status_t status,
    void *buff);

/* Extern API */
void ble_gatt_connect_init(void);

ble_gatt_connect_context_t *ble_gatt_connect_get_context(void);

#endif /* __BLE_GATT_CONNECT_H__ */


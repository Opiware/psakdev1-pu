/* Copyright Statement:
 *
 */

#ifndef __BT_GATT_HANDLE_OP_H__
#define __BT_GATT_HANDLE_OP_H__

#include "bt_gattc.h"

#include "stdint.h"
#include "bt_uuid.h"

#define __BT_MAX_LE_LINK_NUM__ 4
#define SRV_MAX_DEV  __BT_MAX_LE_LINK_NUM__

/*gattc current state*/
#define GATTC_IN_IDLE 0
#define GATTC_CONNECTED 1
#define GATTC_SEARCH_DONE   2
#define GATTC_IN_SEARCHING 3

typedef struct {
    uint8_t addr[16];
} ble_address_t;

typedef struct {
    uint8_t uuid[16];
} gattc_uuid_t;

typedef struct {
    uint16_t handle;
    uint16_t uuid;
} bt_gatt_descriptor_t;

typedef struct {
    uint16_t handle;
    uint16_t value_handle;
    uint8_t property;
    uint16_t uuid;
    bt_gatt_descriptor_t descr[3];
} bt_gatt_char_t;

typedef struct {
    uint16_t handle;
    uint16_t start_handle;
    uint16_t end_handle;
    uint16_t uuid;
} bt_gatt_included_service_t;

typedef struct {
    uint16_t start_handle;
    uint16_t end_handle;
    uint16_t uuid;
    uint8_t num_of_char;
    uint8_t explore_index;
    bt_gatt_included_service_t incl_srv[3];
    bt_gatt_char_t chara[3];
} bt_gatt_service_t;


typedef struct {
    uint16_t service_number; /*current primary service number*/
    uint32_t conn_id;
    bt_gatt_service_t att_data;     /* Stores all the supported services found on the Server */
} gatt_data_t;


typedef struct {
    uint8_t flag;
    uint16_t state;
    uint16_t conn_id;
    gatt_data_t data;
} gattc_conn_t;

typedef struct {
    uint8_t *value;
    uint16_t handle;
    uint16_t size;
} bt_gattc_write_descr_req_t;


/*start discovery service from remote device*/
int32_t bt_gattc_start_discover_service(uint16_t conn_id);
bt_gatt_char_t *bt_gattc_get_char_by_handle(uint16_t conn_id, uint16_t handle);
/*write descriptor's value*/
bt_status_t bt_gattc_write_descr(uint16_t conn_id, bt_gattc_write_descr_req_t *req);
bt_status_t bt_gattc_event_callback(bt_msg_type_t msg, bt_status_t status, void *param);
#endif

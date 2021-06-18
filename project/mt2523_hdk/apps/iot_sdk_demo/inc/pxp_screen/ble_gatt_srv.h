/* Copyright Statement:
 *
 */

#ifndef __BLE_GATT_SRV_H__
#define __BLE_GATT_SRV_H__

#include "stdint.h"
#include "bt_gap_le.h"

typedef int32_t ble_gatt_srv_status_t;

/* BLE APP event base */
#define BLE_GATT_SRV_BASE                           (0x00)

#define BLE_GATT_SRV_IAS_BASE                       (0x1000)
#define BLE_GATT_SRV_LLS_BASE                       (0x1100)


typedef enum {
    /* GAP event */
    BLE_GATT_SRV_LE_CONNECT = BLE_GATT_SRV_BASE,
    BLE_GATT_SRV_LE_DISCONNECT,
    /* IAS event */
    BLE_GATT_SRV_IAS_START = BLE_GATT_SRV_IAS_BASE,
    BLE_GATT_SRV_IAS_AL_READ,
    BLE_GATT_SRV_IAS_AL_WRITE,
    /* LLS event */
    BLE_GATT_SRV_LLS_START = BLE_GATT_SRV_LLS_BASE,
    BLE_GATT_SRV_LLS_AL_READ,
    BLE_GATT_SRV_LLS_AL_WRITE,

    BLE_GATT_SRV_END
} ble_gatt_srv_event_t;


#define BLE_GATT_SRV_STATUS_OK                      (0)
#define BLE_GATT_SRV_STATUS_FAIL                    (-1)
#define BLE_GATT_SRV_STATUS_REGISTERED              (-2)
#define BLE_GATT_SRV_STATUS_EXHAUST                 (-3)
#define BLE_GATT_SRV_STATUS_PARAM                   (-4)


typedef ble_gatt_srv_status_t (*ble_gatt_srv_callback_t)(ble_gatt_srv_event_t event, void *para, void *user_data);

typedef struct {
    bt_handle_t handle;
} ble_gatt_srv_connect_t;

typedef struct {
    bt_handle_t handle;
} ble_gatt_srv_disconnect_t;

typedef struct {
    bt_handle_t handle;
    uint8_t al;
} ble_gatt_char_alter_level_t;

ble_gatt_srv_status_t ble_gatt_srv_init(void);

ble_gatt_srv_status_t ble_gatt_srv_register(ble_gatt_srv_callback_t cb_func,
    void *user_data);

ble_gatt_srv_status_t ble_gatt_srv_deregister(ble_gatt_srv_callback_t cb_func,
    void *user_data);

#endif /* __BLE_GATT_SRV_H__ */


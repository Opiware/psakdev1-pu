/* Copyright Statement:
 *
 */

#ifndef __BLE_IAS_H__
#define __BLE_IAS_H__

#include "ble_gatt_common.h"
#include "stdint.h"

#define BLE_IAS_DEV_FLAG_USED              (0x01)

typedef enum {
    BLE_IAS_DEV_INFO_HANDLE,   /* 0 */
    BLE_IAS_DEV_INFO_USED, /* 1 */
    BLE_IAS_DEV_INFO_UNUSED, /* 2 */

    BLE_IAS_DEV_INFO_TOTAL
} ble_ias_dev_info_type_t;

typedef struct {
    uint8_t flag;
    bt_handle_t handle;
    uint8_t alert_level;
} ble_ias_dev_info_t;

typedef struct {
    uint8_t flag;
    ble_ias_dev_info_t *dev_info;
} ble_ias_context_t;


void ble_ias_init(void);

ble_ias_context_t *ble_ias_get_context(void);

void ble_ias_dev_connect(bt_handle_t handle);

void ble_ias_dev_disconnect(bt_handle_t handle); 

#endif /* __BLE_IAS_H__ */


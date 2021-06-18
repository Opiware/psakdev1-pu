/* Copyright Statement:
 *
 */
#ifndef __BLE_BAS_APP_H__
#define __BLE_BAS_APP_H__

#include "bt_type.h"
#include "bt_platform.h"

BT_EXTERN_C_BEGIN

#define BLE_BAS_CONNECTION_MAX 4
#define BLE_BAS_CCCD_NOTIFICATION  0x0001

typedef struct {
    uint16_t                        notify_enabled;/**< Client Characteristic Configuration of Service Changed Characteristic. */
    uint16_t                        conn_handle;   /**< Connection handle. */
} ble_bas_buffer_t;

bt_status_t ble_bas_app_init(void);
void ble_bas_app_update_battery_capacity(int32_t capacity);


BT_EXTERN_C_END

#endif


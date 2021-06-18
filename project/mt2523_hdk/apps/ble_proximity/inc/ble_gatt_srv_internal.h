/* Copyright Statement:
 *
 */

#ifndef __BLE_GATT_INTERNAL_H__
#define __BLE_GATT_INTERNAL_H__

#include "ble_gatt_srv.h"
#include "stdint.h"

#define BLE_GATT_SRV_MAX_USER                       (2)


#define BLE_GATT_SRV_USER_FLAG_USED                 (0x0001)


typedef struct {
    uint32_t uflag;
    void *user_data;
    ble_gatt_srv_callback_t cb_func;
} ble_gatt_srv_user_t;

typedef struct {
    uint32_t flag;
    ble_gatt_srv_user_t *user;
} ble_gatt_srv_context_t;


ble_gatt_srv_context_t *ble_gatt_srv_get_context(void);

void ble_gatt_srv_notify(ble_gatt_srv_event_t event, void *para);

#endif /* __BLE_GATT_INTERNAL_H__ */


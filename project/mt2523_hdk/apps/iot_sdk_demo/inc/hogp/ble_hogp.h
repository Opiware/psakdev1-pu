/* Copyright Statement:
 *
 */

#ifndef __BLE_HOGP_H__
#define __BLE_HOGP_H__
#include <stdint.h>


typedef struct {
    uint16_t        report_ccc;
    uint16_t        bat_level_ccc;
    uint16_t        bk_input_ccc; /////
    bt_handle_t     conn_handle;
}ble_hogp_cntx_t;

extern const bt_gatts_service_t bt_if_hogp_device_info_service;

extern const bt_gatts_service_t bt_if_hogp_hid_service;
extern const bt_gatts_service_t bt_if_hogp_battery_service;

void ble_hogp_init(void);

bt_status_t ble_hogp_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);



#endif /* __BLE_HOGP_H__ */


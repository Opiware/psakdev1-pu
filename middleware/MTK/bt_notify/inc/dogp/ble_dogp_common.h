/* Copyright Statement:
 *
 */
#ifndef __BLE_DOGP_COMMON_H__
#define __BLE_DOGP_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "timers.h"
#include "bt_type.h"

typedef enum {
    BLE_GAP_ADV_INTERVAL_DEFAULT,
    BLE_GAP_ADV_INTERVAL_FAST_CONNECT,
    BLE_GAP_ADV_INTERVAL_LOW_POWER
} ble_gap_adv_interval_enum_t;
 
typedef enum {
    BLE_GAP_CONN_PARAM_PRIORITY_DEFAULT,
    BLE_GAP_CONN_PARAM_HIGH_SPEED_ANDROID, /**< please use this High speed enum, when remote device is android. */
    BLE_GAP_CONN_PARAM_HIGH_SPEED_IOS,     /**< please use this High speed enum, when remote device is IOS. */
    BLE_GAP_CONN_PARAM_LOW_POWER
} ble_gap_conn_param_priority_t;

typedef struct {
    uint16_t                        conn_handle;
    uint16_t                        conn_interval;
    ble_gap_conn_param_priority_t   conn_priority;
    ble_gap_adv_interval_enum_t     adv_interval;
    uint8_t                         remote_device_type;
} ble_dogp_adp_low_powe_cntx_t;

#if 0
void ble_dogp_adp_advertise_data_init(void);
#endif
bt_status_t bt_dogp_app_event_callback(bt_msg_type_t msg, void *buff);
bt_status_t ble_dogp_update_connection_interval(uint16_t conn_handle, ble_gap_conn_param_priority_t conn_priority);
bt_status_t bt_dogp_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);
bt_status_t ble_dogp_event_callback_init(void);






#ifdef __cplusplus
}
#endif

#endif /*__BLE_DOGP_COMMON_H__*/




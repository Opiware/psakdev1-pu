/* Copyright Statement:
 *
 */

#include "bt_type.h"
#include "bt_gattc_discovery.h"


/**
 *  @brief Define ancs event type. */
#define BLE_ANCS_EVENT_CONNECTED                0
#define BLE_ANCS_EVENT_IOS_NOTIFICATION         1
#define BLE_ANCS_EVENT_NOTIFICATION_ATTRIBUTE   2
#define BLE_ANCS_EVENT_APP_ATTRIBUTE            3
#define BLE_ANCS_EVENT_REQUEST_COMPLETED        4
#define BLE_ANCS_EVENT_DISCONNECTED             5
typedef uint8_t ble_ancs_event_type_t;


/**
 *  @brief Define ancs connection speed. */
#define BLE_ANCS_CONN_DEFAULT       0
#define BLE_ANCS_CONN_HIGH_SPEED    1
#define BLE_ANCS_CONN_LOW_POWER     2
typedef uint8_t ble_ancs_conn_speed_t;


/**
 *  @brief Define bt_ancs_common status. */
#define ANCS_COMM_STATUS_READY              0
#define ANCS_COMM_STATUS_READ_NOTIF_SOURCE  1
#define ANCS_COMM_STATUS_READ_DATA_SOURCE   2
typedef uint8_t ble_ancs_comm_status_t;

typedef struct {
    ble_ancs_event_type_t evt_type;
    bt_handle_t connection_handle;
    bt_status_t result;
    union {
        ble_ancs_event_notification_t notification;
        ble_ancs_event_attribute_t attribute;
    } data;
} ble_ancs_event_t;
 
typedef void(* ble_ancs_event_handler_t)(ble_ancs_event_t *p_evt);

typedef struct {
    ble_ancs_comm_status_t status;
    ble_ancs_event_handler_t evt_handler;
    bt_gattc_discovery_service_t service;
    bt_gattc_discovery_characteristic_t charc[BLE_ANCS_MAX_CHARC_NUMBER];
    bt_gattc_discovery_descriptor_t descrp[BLE_ANCS_MAX_CHARC_NUMBER];
} ble_ancs_srv_content_t;


void ble_ancs_start(ble_ancs_event_handler_t evt_handler);

uint16_t ble_ancs_get_conn_interval(void);

bt_status_t ble_ancs_update_connection_interval(bt_handle_t connection_handle, ble_ancs_conn_speed_t conn_speed);




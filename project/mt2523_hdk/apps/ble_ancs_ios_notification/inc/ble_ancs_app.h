/* Copyright Statement:
 *
 */

#include "stdint.h"
#include "stdbool.h"
#include "ble_ancs.h"
#include "FreeRTOS.h"
#include "timers.h"

#define BLE_ANCS_APP_ID_LEN         50
#define BLE_ANCS_TITLE_LEN          40
#define BLE_ANCS_SUBTITLE_LEN       30
#define BLE_ANCS_MESSAGE_LEN        300
#define BLE_ANCS_MESSAGE_SIZE_LEN   4
#define BLE_ANCS_DATE_LEN           30
#define BLE_ANCS_APP_NAME_LEN       30

/*The max number of notificaiton can be queued, if more than 10, previous notifications will be droped*/
#define BLE_ANCS_MAX_NOTIF_NUM      10
#define BLE_ANCS_LAB_LEN            20
#define BLE_ANCS_TIMER_PERIOD       15000



/**
 *  @brief Define for ble ancs status type. */
#define ANCS_APP_STATUS_NONE                    0
#define ANCS_APP_STATUS_ENABLE_DATA_SOURCE      1
#define ANCS_APP_STATUS_ENABLE_NOTIF_SOURCE     2
#define ANCS_APP_STATUS_DISABLE_DATA_SOURCE     3
#define ANCS_APP_STATUS_DISABLE_NOTIF_SOURCE    4
#define ANCS_APP_STATUS_GET_NOTIF_ATTRIBUTE     5
#define ANCS_APP_STATUS_GET_APP_ATTRIBUTE       6
#define ANCS_APP_STATUS_PERFORM_ACTION          7
typedef uint8_t ble_ancs_app_status_t; 


typedef struct {
    uint8_t notif_uid[4];
    bt_handle_t connection_handle;
} ble_ancs_notification_info_t;

typedef struct _ble_ancs_notification_node_t {
    ble_ancs_notification_info_t notif;
    struct _ble_ancs_notification_node_t *next;
} ble_ancs_notification_node_t;

typedef struct {
    bt_handle_t connection_handle;
    TimerHandle_t ancs_timer;
    ble_ancs_app_status_t status;

    uint8_t appid[BLE_ANCS_APP_ID_LEN + 1];     /*String must be NULL_terminated, add 1 byte for '\0'*/
    uint8_t title[BLE_ANCS_TITLE_LEN + 1];
    uint8_t subtitle[BLE_ANCS_SUBTITLE_LEN + 1];
    uint8_t message[BLE_ANCS_MESSAGE_LEN + 1];
    uint8_t messagesize[BLE_ANCS_MESSAGE_SIZE_LEN + 1];
    uint8_t date[BLE_ANCS_DATE_LEN + 1];
    /*posi_lab and nega_lab only supported by IOS8.0 or later*/
    uint8_t posi_lab[BLE_ANCS_LAB_LEN + 1];     /*positive label*/
    uint8_t nega_lab[BLE_ANCS_LAB_LEN + 1];
    uint8_t app_name[BLE_ANCS_APP_NAME_LEN + 1];

    uint8_t notif_num;
    ble_ancs_notification_node_t notif_list;
    ble_ancs_notification_node_t *curr_notif;   /*the notification in getting attributes*/
    ble_ancs_notification_node_t *new_notif;    /*The latest received notification*/
} ble_ancs_app_cntx_t;


void ble_ancs_task_init(void);

void ble_ancs_perform_action(uint8_t *cmd);



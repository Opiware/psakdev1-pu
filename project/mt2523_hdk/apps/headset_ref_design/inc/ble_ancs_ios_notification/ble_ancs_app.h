/* Copyright Statement:
 *
 */

#include "stdint.h"
#include "stdbool.h"
#include "ble_ancs.h"


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
    bt_handle_t connection_handle;
    ble_ancs_app_status_t status;
    uint32_t notif_counter;
} ble_ancs_app_cntx_t;


void ble_ancs_app_init(void);




/* Copyright Statement:
 *
 */
#ifndef __BLE_FIND_ME_SERVER_H__
#define __BLE_FIND_ME_SERVER_H__

#include "bt_type.h"
#include "bt_platform.h"

BT_EXTERN_C_BEGIN

#define BLE_FMPS_CONNECTION_MAX 1

typedef struct {
    uint8_t                         alert_level;   /**< Alert Level value of Alert Level Characteristic. */
    uint16_t                        conn_handle;   /**< Connection handle. */
} ble_fmps_cntx_t;


bt_status_t ble_fmp_server_init(void);

BT_EXTERN_C_END

#endif


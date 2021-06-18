/* Copyright Statement:
 *
 */

#ifndef __BLE_CONNECT_H__
#define __BLE_CONNECT_H__

#include "bt_gap_le.h"
#include "bt_gattc_handle_op.h"
#include "connection_info.h"
#include "bt_gap.h"

#include "bt_debug.h"

#define UT_APP_CMP(_cmd) (strncmp((_cmd), cmd, strlen(_cmd)) == 0)

bt_status_t bt_gattc_set_scan(bt_hci_cmd_le_set_scan_enable_t *enable);

void gattc_service_init(void);
gattc_conn_t *bt_gattc_link_info_by_id(uint16_t conn_id);

void gattc_free_conn(gattc_conn_t *conn);

bt_status_t bt_gattc_disconnect(uint16_t conn_id);

bt_status_t bt_gattc_connect(uint8_t *addr, uint8_t type);

bt_status_t bt_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);

bt_status_t bt_hr_io_callback(uint8_t *cmd);
//bt_status_t bt_app_io_callback(void *input, void *output);
#endif


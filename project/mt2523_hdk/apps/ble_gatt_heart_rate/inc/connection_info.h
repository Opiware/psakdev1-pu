/* Copyright Statement:
 *
 */

#ifndef __CONNECTION_INFO_H__
#define __CONNECTION_INFO_H__

#include "bt_debug.h"
#include "bt_system.h"
#include "bt_gap_le.h"
#include "project_config.h"

BT_EXTERN_C_BEGIN
#define BT_ADDR_TYPE_UNKNOW 0xFF
BT_PACKED (
typedef struct {
    bt_handle_t       connection_handle;
    bt_role_t         role;
    bt_addr_t         peer_addr;
    uint8_t           gatts_wait_att_rx_opcode;//use to wait handle value confirmation.
}) app_bt_connection_cb_t;

BT_PACKED (
typedef struct {
   bt_addr_t bt_addr;
   bt_gap_le_bonding_info_t info;
}) app_bt_bonded_info_t;

extern app_bt_connection_cb_t connection_cb[BT_CONNECTION_MAX];

void add_connection_info(void *buff);
void delete_connection_info(void *buff);
app_bt_connection_cb_t* find_conneciton_info_by_handle(bt_handle_t target_handle);
app_bt_bonded_info_t* get_bonded_info(const bt_addr_t *target_bt, uint8_t create);
app_bt_bonded_info_t* find_bonded_info_by_index(uint8_t idx);
app_bt_bonded_info_t* find_bonded_info_by_handle(bt_handle_t target_handle);
void cancel_bonded_info(const bt_addr_t *target_bt);
void clear_bonded_info(void);
void dump_bonded_info_list(void);
void dump_connection_info_list(void);
BT_EXTERN_C_END

#endif /* __CONNECTION_INFO_H__ */

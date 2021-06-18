/* Copyright Statement:
 *
 */

#include "connection_info.h"

app_bt_connection_cb_t connection_cb[BT_CONNECTION_MAX] = {{0}};
app_bt_bonded_info_t bonded_info_req[BT_CONNECTION_MAX] = {{{0}}};
static const bt_addr_t default_bt_addr = {
                       .type = BT_ADDR_TYPE_UNKNOW,
                       .addr = {0}
                       };

void add_connection_info(void *buff)
{
    uint8_t i;

    bt_gap_le_connection_ind_t *connection_ind = (bt_gap_le_connection_ind_t *)buff;
    for (i =0; i< BT_CONNECTION_MAX; i++) {
        if (connection_cb[i].connection_handle==0) {
            connection_cb[i].connection_handle = connection_ind->connection_handle;
            connection_cb[i].role = connection_ind->role;
            connection_cb[i].peer_addr = connection_ind->peer_addr;
            break;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        BT_LOGW("APP", "Reach maximum connection\n");
    }
}

void dump_connection_info_list()
{
    uint8_t i;
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        if (connection_cb[i].connection_handle) {
            BT_LOGD("APP", "Connection Info[%d]: [%s] [0x%04x] [%s]",i,bt_debug_addr2str(&(connection_cb[i].peer_addr)), connection_cb[i].connection_handle, connection_cb[i].role?"Slave":"Master");
        }
    }
}

void delete_connection_info(void *buff)
{
    bt_hci_evt_disconnect_complete_t *disconnect_complete;
    uint8_t i;

    disconnect_complete = (bt_hci_evt_disconnect_complete_t*) buff;
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        if (disconnect_complete->connection_handle == connection_cb[i].connection_handle) {
            connection_cb[i].connection_handle = 0;//clear conneciton info.
            connection_cb[i].gatts_wait_att_rx_opcode = 0;
            break;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        BT_LOGW("APP", "Don't know connection info for deleting.\n");
    }
}
app_bt_connection_cb_t* find_conneciton_info_by_handle(bt_handle_t target_handle)
{
    uint8_t i;
    for (i = 0; i< BT_CONNECTION_MAX; i++) {
        if (target_handle == connection_cb[i].connection_handle) {
            return &(connection_cb[i]);
        }
    }
    return NULL;
}
app_bt_bonded_info_t* get_bonded_info(const bt_addr_t *target_bt, uint8_t create)
{
    uint8_t i;
    //Check have we been bonded?
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        if (0 == memcmp(target_bt,&(bonded_info_req[i].bt_addr), sizeof(default_bt_addr))) {
            return &(bonded_info_req[i]);
        }
    }
    //Give a new
    if (create) {
        for (i = 0; i< BT_CONNECTION_MAX ; i++) {
            if (0 == memcmp(&default_bt_addr,&(bonded_info_req[i].bt_addr), sizeof(default_bt_addr))) {
                bonded_info_req[i].info.identity_addr.address.type = BT_ADDR_TYPE_UNKNOW;
                memcpy(&(bonded_info_req[i].bt_addr), target_bt, sizeof(default_bt_addr));
                return &(bonded_info_req[i]);
            }
        }
    }
    //Out of memory
    return NULL;
}
app_bt_bonded_info_t* find_bonded_info_by_index(uint8_t idx)
{
    if (idx <BT_CONNECTION_MAX) {
        if (0 != memcmp(&default_bt_addr,&(bonded_info_req[idx].bt_addr), sizeof(default_bt_addr))) {
            return &(bonded_info_req[idx]);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}
app_bt_bonded_info_t* find_bonded_info_by_handle(bt_handle_t target_handle)
{
    app_bt_connection_cb_t *con = find_conneciton_info_by_handle(target_handle);
    return get_bonded_info(&(con->peer_addr), 0);
}
void cancel_bonded_info(const bt_addr_t *target_bt)
{
    uint8_t i;
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        if (0 == memcmp(target_bt,&(bonded_info_req[i].bt_addr), sizeof(default_bt_addr))) {
            memset(&(bonded_info_req[i]),0x00, sizeof(app_bt_bonded_info_t));
            bonded_info_req[i].info.identity_addr.address.type = BT_ADDR_TYPE_UNKNOW;
            BT_LOGD("APP", "Cancel bonded info for BT addr %s",bt_debug_addr2str(target_bt));
        }
    }
}
void clear_bonded_info()
{
    uint8_t i;
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        memset(&(bonded_info_req[i]),0x00, sizeof(app_bt_bonded_info_t));
        bonded_info_req[i].bt_addr.type = BT_ADDR_TYPE_UNKNOW;
        bonded_info_req[i].info.identity_addr.address.type = BT_ADDR_TYPE_UNKNOW;
    }
}
void dump_bonded_info_list()
{
    uint8_t i;
    for (i = 0; i< BT_CONNECTION_MAX ; i++) {
        if (0 != memcmp(&default_bt_addr,&(bonded_info_req[i].bt_addr), sizeof(default_bt_addr))) {
            BT_LOGD("APP", "Bonded Info[%d]: [%s]",i,bt_debug_addr2str(&(bonded_info_req[i].bt_addr)));
        }
    }
}

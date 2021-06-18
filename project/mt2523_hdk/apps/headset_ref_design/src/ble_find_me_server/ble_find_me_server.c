/* Copyright Statement:
 *
 */

#include "bt_gap_le.h"
#include "bt_callback_manager.h"
#include "ble_ias.h"
#include "ble_find_me_server.h"
#include "syslog.h"

/* Create the log control block as user wishes. Here we use 'BT_IAS' as module name.
 * User needs to define their own log control blocks as project needs.
 * Please refer to the log dev guide under /doc folder for more details. */
log_create_module(BLE_FMPS, PRINT_LEVEL_INFO);

static ble_fmps_cntx_t g_fmps_buffer[BLE_FMPS_CONNECTION_MAX];


static void ble_fmp_disable_alert(void);
static void ble_fmp_enable_alert(uint8_t alert_level);
static void ble_fmp_alert_level_trigger(uint8_t alert_level);

static bt_status_t ble_fmp_server_save_connection_info(void *buff);
static bt_status_t ble_fmp_server_delete_connection_info(void *buff);
static void ble_fmp_server_clear_all_connection_info(void);
static bt_status_t ble_fmp_server_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);
static bt_status_t ble_fmp_server_event_callback_register(void);
static void ble_fmp_alert_level_write_callback(uint16_t conn_handle, uint8_t alert_level);


static void ble_fmp_disable_alert(void)
{
    LOG_I(BLE_FMPS, "%s: disable alert success!\r\n", __FUNCTION__);
}
static void ble_fmp_enable_alert(uint8_t alert_level)
{
    LOG_I(BLE_FMPS, "%s: enable alert with level is %d success!\r\n", __FUNCTION__, alert_level);
}

static void ble_fmp_alert_level_trigger(uint8_t alert_level)
{
    LOG_I(BLE_FMPS, "%s: enter, alert level is %d\r\n", __FUNCTION__, alert_level);

    switch (alert_level) {
        case 0:
            ble_fmp_disable_alert();
            break;
        case 1:
        case 2:
            ble_fmp_enable_alert(alert_level);
            break;
        default:
            break;
    }
}

static bt_status_t ble_fmp_server_save_connection_info(void *buff)
{
    uint8_t i;
    bt_status_t status;
    
    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);
    bt_gap_le_connection_ind_t *conn_ind = (bt_gap_le_connection_ind_t *)buff;
    for (i = 0; i< BLE_FMPS_CONNECTION_MAX; i++) {
        /**< first connect, to save connection info. */
        if (0 == g_fmps_buffer[i].conn_handle) {
            g_fmps_buffer[i].conn_handle = conn_ind->connection_handle;
            break;
        }
    }

    if (i == BLE_FMPS_CONNECTION_MAX) {  
        LOG_I(BLE_FMPS, "Reach maximum connection, no empty buffer!\r\n"); 
        status = BT_STATUS_OUT_OF_MEMORY;
    }
    return status;
}

static bt_status_t ble_fmp_server_delete_connection_info(void *buff)
{
    uint8_t i; 
    bt_status_t status = BT_STATUS_SUCCESS;
    bt_hci_evt_disconnect_complete_t *disconnect_complete;

    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);
    disconnect_complete = (bt_hci_evt_disconnect_complete_t*) buff;
    for (i = 0; i< BLE_FMPS_CONNECTION_MAX ; i++) {
        if (disconnect_complete->connection_handle == g_fmps_buffer[i].conn_handle) {
            ble_fmp_alert_level_trigger(0);
            memset(&(g_fmps_buffer[i]),0x00, sizeof(ble_fmps_cntx_t));
            break;
        }
    }
    if (i == BLE_FMPS_CONNECTION_MAX) {
        LOG_I(BLE_FMPS, "Don't know connection info for deleting!\r\n");
        status = BT_STATUS_FAIL;
    }
    return status;
}

static void ble_fmp_server_clear_all_connection_info(void)
{
    uint8_t i;
    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);

    for (i = 0; i< BLE_FMPS_CONNECTION_MAX ; i++) {   
        memset(&(g_fmps_buffer[i]),0x00, sizeof(ble_fmps_cntx_t));
    }
}

static bt_status_t ble_fmp_server_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    LOG_I(BLE_FMPS, "%s: status(0x%04x), msg(0x%04x)", __FUNCTION__, status, msg);

    if(status != BT_STATUS_SUCCESS) {
       return BT_STATUS_SUCCESS;
    }

     switch (msg)
     {
         case BT_GAP_LE_CONNECT_IND: 
             ble_fmp_server_save_connection_info(buff);
             break;  
                         
         case BT_GAP_LE_DISCONNECT_IND: 
            ble_fmp_server_delete_connection_info(buff);
            break;
            
         default:
             break;
     }
     return BT_STATUS_SUCCESS;
}

static bt_status_t ble_fmp_server_event_callback_register(void)
{
    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);
    return bt_callback_manager_register_callback(bt_callback_type_app_event, MODULE_MASK_GAP, (void *)ble_fmp_server_event_callback);    
}

static void ble_fmp_alert_level_write_callback(uint16_t conn_handle, uint8_t alert_level)
{
    uint8_t i; 

    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);
    for (i = 0; i< BLE_FMPS_CONNECTION_MAX ; i++) {
        if (conn_handle == g_fmps_buffer[i].conn_handle) {
            g_fmps_buffer[i].alert_level = alert_level;
            ble_fmp_alert_level_trigger(alert_level);
            break;
        }
    }
    if (i == BLE_FMPS_CONNECTION_MAX) {
        LOG_I(BLE_FMPS, "Unknown connetion handle!\r\n");
    }
}

void ble_ias_alert_level_write_callback(uint16_t conn_handle, uint8_t alert_level)
{
    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);
    ble_fmp_alert_level_write_callback(conn_handle, alert_level);
}

bt_status_t ble_fmp_server_init(void)
{
    bt_status_t status;

    LOG_I(BLE_FMPS, "%s: enter\r\n", __FUNCTION__);

    ble_fmp_server_clear_all_connection_info();
    status = ble_fmp_server_event_callback_register();
    return status;
}



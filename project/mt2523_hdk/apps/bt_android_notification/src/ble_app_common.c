/* Copyright Statement:
 *
 */

#include "bt_gap_le.h"
#include "bt_gattc.h"
#include "bt_debug.h"
#include "bt_gatts.h"
#include "bt_callback_manager.h"
#include "bt_hci.h"
#include "syslog.h"
#include "ble_app_common.h"

log_create_module(BLE_APP, PRINT_LEVEL_INFO);

static bt_gap_le_smp_pairing_config_t g_app_pairing_config_req = {
    .auth_req = BT_GAP_LE_SMP_AUTH_REQ_BONDING,
    .io_capability = BT_GAP_LE_SMP_NO_INPUT_NO_OUTPUT,
    .maximum_encryption_key_size = 16,
};

static bt_gap_le_local_key_t g_app_local_key_req = {
    .encryption_info = {{0}},
    .master_id = {0},
    .identity_info = {{0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0x19, 0x28, 0x55, 0x33, 0x68, 0x33, 0x56, 0xde}},
    .signing_info = {{0}}
};

static bool g_app_sc_only = false;
static bt_gap_le_bonding_info_t g_app_bonding_info = {{{{0}}}};
static bt_gap_le_local_config_req_ind_t g_app_local_config;

char *device_name = "ANDROID_NOTIFY";

static void ble_app_advertise_data_init(void);
static bt_gap_le_local_config_req_ind_t *ble_app_gap_le_get_local_config(void);
static bt_gap_le_bonding_info_t *ble_app_gap_le_get_bonding_info(const bt_addr_t remote_addr);
static bt_status_t ble_app_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind);
static bt_status_t ble_app_event_callback_internal(bt_msg_type_t msg, void *buff);
static bt_status_t ble_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);


static bt_gap_le_local_config_req_ind_t *ble_app_gap_le_get_local_config(void)
{
    LOG_I(BLE_APP, "ble_app_gap_le_get_local_config \r\n");

    g_app_local_config.local_key_req = &g_app_local_key_req;
    g_app_local_config.sc_only_mode_req = g_app_sc_only;

    return &g_app_local_config;
}

static bt_gap_le_bonding_info_t *ble_app_gap_le_get_bonding_info(const bt_addr_t remote_addr)
{
    LOG_I(BLE_APP, "ble_app_gap_le_get_bonding_info \r\n");

    return &g_app_bonding_info;
}

static bt_status_t ble_app_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind)
{
    LOG_I(BLE_APP, "ble_app_gap_le_get_pairing_config \r\n");

    ind->pairing_config_req = g_app_pairing_config_req;
    return BT_STATUS_SUCCESS;
}

static void ble_app_advertise_data_init(void)
{
    LOG_I(BLE_APP, "ble_app_advertise_data_init \r\n");

    bt_hci_cmd_le_set_advertising_parameters_t adv_param = {
        .advertising_interval_min = 0xC0,
        .advertising_interval_max = 0xC0,
        .advertising_type = BT_HCI_ADV_TYPE_CONNECTABLE_UNDIRECTED,
        .own_address_type = BT_ADDR_RANDOM,
        .advertising_channel_map = 7,
        .advertising_filter_policy = 0
    };

    bt_hci_cmd_le_set_advertising_enable_t enable;
    bt_hci_cmd_le_set_advertising_data_t adv_data = {
        .advertising_data_length = 31,
    };

    memcpy(&adv_data.advertising_data[5], device_name, strlen(device_name));
    adv_data.advertising_data[0] = 2; 
    adv_data.advertising_data[1] = BT_GAP_LE_AD_TYPE_FLAG;
    adv_data.advertising_data[2] = BT_GAP_LE_AD_FLAG_BR_EDR_NOT_SUPPORTED | BT_GAP_LE_AD_FLAG_GENERAL_DISCOVERABLE;
    adv_data.advertising_data[3] = strlen(device_name)+1;
    adv_data.advertising_data[4] = BT_GAP_LE_AD_TYPE_NAME_COMPLETE;
    adv_data.advertising_data[5 + strlen(device_name)] = 0x0;
    
    enable.advertising_enable = BT_HCI_ENABLE;

    bt_gap_le_set_advertising(&enable, &adv_param, &adv_data, NULL);
    
    bt_gatts_set_max_mtu(512);
}

static bt_status_t ble_app_event_callback_internal(bt_msg_type_t msg, void *buff)
{
    bt_status_t status = BT_STATUS_SUCCESS;
    LOG_I(BLE_APP, "ble_app_event_callback_internal msg = 0x%04x \r\n", msg);

     switch (msg)
     {
         case BT_POWER_ON_CNF:
             ble_app_advertise_data_init();
             break;
            
         case BT_GAP_LE_DISCONNECT_IND:  
         {
             ble_app_advertise_data_init();
         }
            break;
            
         default:
             break;
     }
    return status;
}

static bt_status_t ble_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    LOG_I(BLE_APP, "%s: status(0x%04x)", __FUNCTION__, status);
    
    if(status != BT_STATUS_SUCCESS) {
        return status;
    }
    
    return ble_app_event_callback_internal(msg, buff);
}

bt_status_t ble_app_common_init(void)
{
    bt_status_t result;
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_local_cofig, 0, (void *)ble_app_gap_le_get_local_config);
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_pairing_config, 0, (void *)ble_app_gap_le_get_pairing_config);
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_bonding_info, 0, (void *)ble_app_gap_le_get_bonding_info);
    result = bt_callback_manager_register_callback(bt_callback_type_app_event, MODULE_MASK_GAP | MODULE_MASK_SYSTEM, (void*)ble_app_event_callback);
    if (result != BT_STATUS_SUCCESS) {
        LOG_I(BLE_APP, "ble_app_common_init fail! \r\n");
    }
    return result;
}








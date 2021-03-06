/* Copyright Statement:
 *
 */


#include "bt_hci.h"
#include "bt_gap_le.h"
#include "bt_debug.h"




static bt_gap_le_smp_pairing_config_t pairing_config = {//mitm, bond, oob
    .maximum_encryption_key_size = 16,
    .io_capability = BT_GAP_LE_SMP_NO_INPUT_NO_OUTPUT,
    .auth_req = BT_GAP_LE_SMP_AUTH_REQ_BONDING,
    .oob_data_flag = BT_GAP_LE_SMP_OOB_DATA_NOT_PRESENTED,
    .initiator_key_distribution = BT_GAP_LE_SMP_KEY_DISTRIBUTE_ENCKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_IDKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_SIGN,
    .responder_key_distribution = BT_GAP_LE_SMP_KEY_DISTRIBUTE_ENCKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_IDKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_SIGN,
};

static bt_gap_le_local_key_t local_key = {
    .encryption_info.ltk = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc8, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf },
    .master_id.ediv = 0x1005,
    .master_id.rand = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7 },
    .identity_info.irk = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf },
    .signing_info.csrk = { 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf }
};

static bt_gap_le_bonding_info_t  bonding_info;
static bool sc_only = false;
static bt_gap_le_local_config_req_ind_t local_config;

/**
 * @brief   This function is a static callback for the application to listen to the event. Provide a user-defined callback.
 * @param[in] msg     is the callback message type.
 * @param[in] status  is the status of the callback message.
 * @param[in] buf     is the payload of the callback message.
 * @return            The status of this operation returned from the callback. */
bt_status_t bt_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{

    /*Listen all BT event*/
    return BT_STATUS_SUCCESS;
}

/**
 * @brief     This API invoked by the SDK process should be implemented by the application. The application should return the Local Configuration field.
 * @return    The loacl configuration pointer, please set the local key and secure connection mode flag. The pointer should not be NULL and it must be a global variable. */
bt_gap_le_local_config_req_ind_t *bt_gap_le_get_local_config(void)
{
    local_config.local_key_req = &local_key;
    local_config.sc_only_mode_req = sc_only;

    return &local_config;
}

/**
 * @brief   This API invoked by the SDK process should be implemented by the application. The application should return the Bonding Information field.
 * @param[in] remote_addr The address of the remote device to be bonded.
 * @return                The Bonding Information pointer, please set a pointer to the connection bonding information. The pointer should not be NULL and it must be a global variable. */
bt_gap_le_bonding_info_t *bt_gap_le_get_bonding_info(const bt_addr_t remote_addr)
{
    return &bonding_info;
}

/**
 * @brief   This API invoked by the SDK process should be implemented by the application. The application should return the Pairing Configuration field.
 * @param[in] ind         Bonding start indication structure. Application should set the pairing_config_req variable to a global variable.
 * @return    #BT_STATUS_SUCCESS, the application set the pairing configuration successfully.
 *            #BT_STATUS_OUT_OF_MEMORY, out of memory. */
bt_status_t bt_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind)
{
    ind->pairing_config_req = pairing_config;

    return BT_STATUS_SUCCESS;
}



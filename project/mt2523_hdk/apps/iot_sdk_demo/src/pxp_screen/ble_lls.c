/* Copyright Statement:
 *
 */

#include "ble_gatt_common.h"
#include "ble_lls.h"
#include "ble_gatt_srv.h"
#include "ble_gatt_utils.h"
#include "ble_gatt_srv_internal.h"

static ble_lls_context_t g_lls_context;

static ble_lls_dev_info_t g_lls_dev_info[BLE_GATT_MAX_LINK];

static uint32_t bt_if_lls_alert_level_callback (const uint8_t rw, uint16_t handle,
    void *data, uint16_t size, uint16_t offset);

static ble_lls_dev_info_t *ble_lls_get_dev_info(ble_lls_dev_info_type_t type,
    void *para);

static void ble_lls_reset_dev_info(ble_lls_dev_info_t *dev_info);

static const bt_uuid_t BT_SIG_UUID_ALERT_LEVEL =
    BT_UUID_INIT_WITH_UUID16(BT_SIG_UUID16_ALERT_LEVEL);

BT_GATTS_NEW_PRIMARY_SERVICE_16(bt_if_lls_primary_service,
    BT_GATT_UUID16_LINK_LOSS_SERVICE);

BT_GATTS_NEW_CHARC_16_WRITABLE(bt_if_lls_char4_alert_level,
    BT_GATT_CHARC_PROP_READ | BT_GATT_CHARC_PROP_WRITE, BLE_LLS_VAL_HD_AL,
    BT_SIG_UUID16_ALERT_LEVEL);

BT_GATTS_NEW_CHARC_VALUE_CALLBACK(bt_if_lls_alert_level, BT_SIG_UUID_ALERT_LEVEL,
    BT_GATTS_REC_PERM_READABLE | BT_GATTS_REC_PERM_WRITABLE, bt_if_lls_alert_level_callback);

static const bt_gatts_service_rec_t *bt_if_lls_service_rec[] = {
    (const bt_gatts_service_rec_t *) &bt_if_lls_primary_service,
    (const bt_gatts_service_rec_t *) &bt_if_lls_char4_alert_level,
    (const bt_gatts_service_rec_t *) &bt_if_lls_alert_level
};

const bt_gatts_service_t bt_if_lls_service = {
    .starting_handle = BLE_LLS_START_HANDLE,
    .ending_handle = BLE_LLS_END_HANDLE,
    .required_encryption_key_size = BLE_LLS_REKS,
    .records = bt_if_lls_service_rec
};


static uint32_t bt_if_lls_alert_level_callback (const uint8_t rw, uint16_t handle,
    void *data, uint16_t size, uint16_t offset)
{
    uint32_t ret = 0;
    ble_gatt_char_alter_level_t char_al;
    ble_lls_dev_info_t *dev_info = NULL;

    ble_gatt_report("[gatt][lls]al_cb(s)--rw: %d, hd: %d, size: %d, offset: %d\n",
        rw, handle, size, offset);

    dev_info = ble_lls_get_dev_info(BLE_LLS_DEV_INFO_HANDLE, (void *)&handle);

    if (rw == BT_GATTS_CALLBACK_WRITE) {
        if (size == sizeof(dev_info->alert_level)) { //Size check
            dev_info->alert_level = *(uint8_t *)data;
            ret = size;
            char_al.al = dev_info->alert_level;
            char_al.handle = dev_info->handle;
            ble_gatt_srv_notify(BLE_GATT_SRV_LLS_AL_WRITE, &char_al);
        }
    } else if (rw == BT_GATTS_CALLBACK_READ) {
        if (size == sizeof(dev_info->alert_level)) { //Size check
            *(uint8_t *)data = dev_info->alert_level;
            ret = size;
            char_al.al = dev_info->alert_level;
            char_al.handle = dev_info->handle;
            ble_gatt_srv_notify(BLE_GATT_SRV_LLS_AL_READ, &char_al);
        } else if (0 == size) {
            ret = sizeof(dev_info->alert_level); 
        }
    }

    ble_gatt_report("[gatt][lls]al_cb(e)--ret: %d\n", ret);
    return ret;
}


static ble_lls_dev_info_t *ble_lls_get_dev_info(
    ble_lls_dev_info_type_t type, void *para)
{
    int32_t i = 0, ret = 0;
    ble_lls_dev_info_t *info = NULL;
    ble_lls_context_t *lls_ctx = NULL;
    bt_handle_t *hd = NULL;

    lls_ctx = ble_lls_get_context();

    ble_gatt_report("[gatt][lls]get_dev_info(s)--type: %d, para: 0x%x\n",
        type, para);

    switch (type) {

        case BLE_LLS_DEV_INFO_HANDLE: {
            hd = (bt_handle_t *) para;
            for (i = 0; i < BLE_GATT_MAX_LINK; ++i) {
                if ((lls_ctx->dev_info[i].flag & BLE_LLS_DEV_FLAG_USED) &&
                    lls_ctx->dev_info[i].handle == *(hd)) {
                    info = &(lls_ctx->dev_info[i]);
                    break;
                }
            }
            break;
        }

        case BLE_LLS_DEV_INFO_UNUSED: {
            for (i = 0; i < BLE_GATT_MAX_LINK; ++i) {
                if (!(lls_ctx->dev_info[i].flag & BLE_LLS_DEV_FLAG_USED)) {
                    info = &(lls_ctx->dev_info[i]);
                    lls_ctx->dev_info[i].flag |= BLE_LLS_DEV_FLAG_USED;
                    break;
                }
            }
            break;
        }
        default:
            break;
    }

    ble_gatt_report("[gatt][lls]get_dev_info(e)--info: 0x%x, ret: %d\n",
        info, ret);

    return info;
}


static void ble_lls_reset_dev_info(ble_lls_dev_info_t *dev_info)
{
    ble_gatt_memset(dev_info, 0x00, sizeof(ble_lls_dev_info_t));
}


void ble_lls_init(void)
{
    ble_gatt_memset(&g_lls_context, 0x00, sizeof(ble_lls_context_t));
    ble_gatt_memset(&g_lls_dev_info[0], 0x00,
        sizeof(ble_lls_dev_info_t) * BLE_GATT_MAX_LINK);

    g_lls_context.dev_info = g_lls_dev_info;

    ble_gatt_report("[gatt][lls]init\n");
}


void ble_lls_dev_connect(bt_handle_t handle)
{
    ble_lls_dev_info_t *dev_info = NULL;

    dev_info = ble_lls_get_dev_info(BLE_LLS_DEV_INFO_UNUSED, NULL);
    dev_info->handle = handle;
}


void ble_lls_dev_disconnect(bt_handle_t handle)
{
    ble_lls_dev_info_t *dev_info = NULL;

    dev_info = ble_lls_get_dev_info(BLE_LLS_DEV_INFO_HANDLE, (void *)&handle);
    ble_lls_reset_dev_info(dev_info);
}


ble_lls_context_t *ble_lls_get_context(void)
{
    return &g_lls_context;
}


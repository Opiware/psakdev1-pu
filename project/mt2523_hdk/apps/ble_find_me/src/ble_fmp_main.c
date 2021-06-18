/* Copyright Statement:
 *
 */

#include "ble_fmp_main.h"


ble_fmp_context_t g_ble_fmp_ctx;


/*****************************************************************************
* FUNCTION
*  ble_fmp_get_context
* DESCRIPTION
* Get FMP context
* PARAMETERS
*  void
* RETURNS
*  ble_fmp_context_t
*****************************************************************************/
ble_fmp_context_t *ble_fmp_get_context(void)
{
    return &g_ble_fmp_ctx;
}


/*****************************************************************************
* FUNCTION
*  ble_fmp_gatt_srv_handle
* DESCRIPTION
* Handle le event
* PARAMETERS
*  event         [IN]        Event message ID
*  para          [IN]        Event para
*  user_data     [IN]        Event user data
* RETURNS
*  ble_gatt_srv_status_t
*****************************************************************************/
static ble_gatt_srv_status_t ble_fmp_gatt_srv_handle(ble_gatt_srv_event_t event,
    void *para, void *user_data)
{
    ble_gatt_srv_status_t ret = BLE_GATT_SRV_STATUS_OK;
    ble_gatt_char_alter_level_t *char_al = NULL;

    ble_gatt_report("[fmp]srv_handle(s)--ent: 0x%x\n", event);

    switch (event) {
        case BLE_GATT_SRV_IAS_AL_WRITE: {
            char_al = (ble_gatt_char_alter_level_t *)para;
            ble_gatt_report("[fmp]srv_handle(al_w)--hd: 0x%x, al: %d", char_al->handle, char_al->al);
            break;
        }

        default:
            break;
    }

    ble_gatt_report("[fmp]srv_handle(e)--ret: %d\n", ret);
    return ret;
}


/*****************************************************************************
* FUNCTION
*  ble_fmp_init
* DESCRIPTION
* FMP init
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
void ble_fmp_init(void)
{
    int32_t ret = 0;

    memset(&g_ble_fmp_ctx, 0x00, sizeof(ble_fmp_context_t));

    ble_gatt_srv_init();

    ret = ble_gatt_srv_register(ble_fmp_gatt_srv_handle, &g_ble_fmp_ctx);

    ble_gatt_report("[fmp]init--ret: %d\n", ret);

#if defined(__GNUC__)
    printf("Version: %s\n", "__GNUC__");
#endif

#if defined(__ARMCC_VERSION)
    printf("Version: %s\n", "__ARMCC_VERSION");
#endif

#if defined(__ICCARM__)
    printf("Version: %s\n", "__ICCARM__");
#endif
}


/*****************************************************************************
* FUNCTION
*  ble_fmp_deinit
* DESCRIPTION
* FMP deinit
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
void ble_fmp_deinit(void)
{
    int32_t ret = 0;

    ret = ble_gatt_srv_deregister(ble_fmp_gatt_srv_handle, &g_ble_fmp_ctx);

    ble_gatt_report("[fmp]deinit--ret: %d\n", ret);
}


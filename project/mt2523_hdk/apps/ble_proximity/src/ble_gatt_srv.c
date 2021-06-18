/* Copyright Statement:
 *
 */

#include "ble_gatt_srv_internal.h"
#include "ble_gatt_srv.h"
#include "ble_gatt_utils.h"
#include "ble_gatt_connect.h"
#include "ble_lls.h"

static ble_gatt_srv_user_t g_ble_gatt_srv_user[BLE_GATT_SRV_MAX_USER];

static ble_gatt_srv_context_t g_ble_gatt_srv_ctx;


/*****************************************************************************
* FUNCTION
*  ble_gatt_srv_context_t
* DESCRIPTION
* Get GATT srv context
* PARAMETERS
*  void
* RETURNS
*  ble_gatt_srv_context_t
*****************************************************************************/
ble_gatt_srv_context_t *ble_gatt_srv_get_context(void)
{
    return &g_ble_gatt_srv_ctx;
}


/*****************************************************************************
* FUNCTION
*  ble_gatt_srv_notify
* DESCRIPTION
* Notify GATT srv event
* PARAMETERS
*  event             [IN]            GATT event
*  para              [IN]            Event result
* RETURNS
*  void
*****************************************************************************/
void ble_gatt_srv_notify(ble_gatt_srv_event_t event, void *para)
{
    int32_t i = 0;
    ble_gatt_srv_context_t *gatt_srv = NULL;
    ble_gatt_srv_user_t *user = NULL;

   gatt_srv = ble_gatt_srv_get_context();
   user = gatt_srv->user;

   for (i = 0; i < BLE_GATT_SRV_MAX_USER; ++i) {
       ble_gatt_report("[gatt][srv]notify--i: %d, flag: 0x%x, cb_func: 0x%x\n",
            i, user->uflag, user->cb_func);
       if ((user->uflag & BLE_GATT_SRV_USER_FLAG_USED)) {
            user->cb_func(event, para, user->user_data);
       }
       ++user;
   }
}


/*****************************************************************************
* FUNCTION
*  ble_gatt_srv_init
* DESCRIPTION
* GATT srv init
* PARAMETERS
*  void
* RETURNS
*  ble_gatt_srv_status_t
*****************************************************************************/
/* extern API */
ble_gatt_srv_status_t ble_gatt_srv_init(void)
{
    ble_gatt_srv_status_t ret = BLE_GATT_SRV_STATUS_OK;

    ble_gatt_memset(&g_ble_gatt_srv_user[0], 0x00, sizeof(ble_gatt_srv_user_t) * BLE_GATT_SRV_MAX_USER);
    ble_gatt_memset(&g_ble_gatt_srv_ctx, 0x00, sizeof(ble_gatt_srv_context_t));

    g_ble_gatt_srv_ctx.user = g_ble_gatt_srv_user;

    /* connect manager */
    ble_gatt_connect_init();
    /* lls init */
    ble_lls_init();

    ble_gatt_report("[gatt][srv]init");
    return ret;
}


/*****************************************************************************
* FUNCTION
*  ble_gatt_srv_register
* DESCRIPTION
* Register user
* PARAMETERS
*  cb_func           [IN]          Callback function pointer
*  user_data         [IN]          User data
* RETURNS
*  ble_gatt_srv_status_t
*****************************************************************************/
ble_gatt_srv_status_t ble_gatt_srv_register(ble_gatt_srv_callback_t cb_func,
    void *user_data)
{
    int32_t i = 0;
    ble_gatt_srv_status_t ret = BLE_GATT_SRV_STATUS_OK;
    ble_gatt_srv_context_t *gatt_srv = NULL;
    ble_gatt_srv_user_t *freed = NULL;

    gatt_srv = ble_gatt_srv_get_context();
    
    for (i = 0; i < BLE_GATT_SRV_MAX_USER; ++i) {
        if ((gatt_srv->user[i].uflag & BLE_GATT_SRV_USER_FLAG_USED)
            && (gatt_srv->user[i].cb_func == cb_func)
            && (gatt_srv->user[i].user_data == user_data)) {
            ret = BLE_GATT_SRV_STATUS_REGISTERED;
            break;
        }
    }

    if (!cb_func) {
        ret = BLE_GATT_SRV_STATUS_PARAM;
    }

    if (BLE_GATT_SRV_STATUS_OK == ret) {
        /* alloc free user */
        for (i = 0; i < BLE_GATT_SRV_MAX_USER; ++i) {
            if (gatt_srv->user[i].uflag & BLE_GATT_SRV_USER_FLAG_USED) {
                ;
            } else {
                freed = &(gatt_srv->user[i]);
                break;
            }
        }
    }

    if (freed) {
        freed->cb_func = cb_func;
        freed->user_data = user_data;
        freed->uflag |= BLE_GATT_SRV_USER_FLAG_USED;

        ret = BLE_GATT_SRV_STATUS_OK;
    } else {
        ret = BLE_GATT_SRV_STATUS_EXHAUST;
    }

    ble_gatt_report("[gatt][srv]register--cb: 0x%x, user: 0x%x, ret: %d\n", 
        cb_func, user_data, ret);

    return ret;
}


/*****************************************************************************
* FUNCTION
*  ble_gatt_srv_deregister
* DESCRIPTION
* Deregister user
* PARAMETERS
*  cb_func           [IN]          Callback function pointer
*  user_data         [IN]          User data
* RETURNS
*  ble_gatt_srv_status_t
*****************************************************************************/
ble_gatt_srv_status_t ble_gatt_srv_deregister(ble_gatt_srv_callback_t cb_func,
    void *user_data)
{
    int32_t i = 0;
    ble_gatt_srv_status_t ret = BLE_GATT_SRV_STATUS_OK;
    ble_gatt_srv_context_t *gatt_srv = NULL;
    ble_gatt_srv_user_t *user = NULL, *used = NULL;

    gatt_srv = ble_gatt_srv_get_context();
    user = gatt_srv->user;

    for (i = 0; i < BLE_GATT_SRV_MAX_USER; ++i) {
        if ((user->uflag & BLE_GATT_SRV_USER_FLAG_USED)
            && (user->cb_func == cb_func)
            && (user->user_data == user_data)) {
            used = user;
            break;
        }
        ++user;
    }

    if (used) {
        ble_gatt_memset(used, 0x00, sizeof(ble_gatt_srv_user_t));
        ret = BLE_GATT_SRV_STATUS_OK;
    } else {
        ret = BLE_GATT_SRV_STATUS_FAIL;
    }

    ble_gatt_report("[gatt_srv]deregister--cb: 0x%x, user: 0x%x, ret: %d\n",
        cb_func, user_data, ret);

    return ret;
}


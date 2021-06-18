/* Copyright Statement:
 *
 */

#include "ble_ancs_app.h"
#include <string.h>
#include "bt_debug.h"
#include "bt_ancs_common.h"
#include "syslog.h"
#include "atci.h"

ble_ancs_app_cntx_t ancs_app_cntx;
ble_ancs_app_cntx_t *p_ancs_app = &ancs_app_cntx;


/*****************************************************************************
* FUNCTION
*  ble_ancs_deal_with_new_notification
* DESCRIPTION
* Deal with the newly received notificaitons
* PARAMETERS
*  notif            [IN]        Pointer to notificaiton source
* RETURNS
*  void
*****************************************************************************/
void ble_ancs_deal_with_new_notification(ble_ancs_event_notification_t *notif)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    atci_response_t rsp = {{0}};

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if (notif->event_id == BLE_ANCS_EVENT_ID_NOTIFICATION_REMOVED) {
        p_ancs_app->notif_counter--;
    } else if (notif->event_id == BLE_ANCS_EVENT_ID_NOTIFICATION_ADDED) {
        p_ancs_app->notif_counter++;
    }
    
    //LOG_I(ANCS, "[ANCSapp]New notification, type = %d, counter = %d\r\n", notif->event_id, p_ancs_app->notif_counter);
    sprintf((char *)rsp.response_buf, "[ANCSapp]New notification, type = %d, counter = %d\n", notif->event_id, (int)p_ancs_app->notif_counter);
    rsp.response_len = strlen((char *)rsp.response_buf);
    atci_send_response(&rsp);
}


/*****************************************************************************
* FUNCTION
*  ble_ancs_app_event_callback
* DESCRIPTION
* Send events from ancs service to ancs task
* PARAMETERS
*  ancs_evt            [IN]        Pointer to event
* RETURNS
*  void
*****************************************************************************/
void ble_ancs_app_event_callback(ble_ancs_event_t *ancs_evt)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
        
    //LOG_I(ANCS, "[ANCSapp]event_id = %d\r\n", ancs_evt->evt_type);
    
    switch (ancs_evt->evt_type) {
        case BLE_ANCS_EVENT_CONNECTED: 
            if (ancs_evt->result == BT_STATUS_SUCCESS) {            
                p_ancs_app->connection_handle = ancs_evt->connection_handle;
                ble_ancs_enable_data_source(ancs_evt->connection_handle);
                p_ancs_app->status = ANCS_APP_STATUS_ENABLE_DATA_SOURCE;
                
            } else {
                LOG_I(ANCS, "[ANCSapp]Discover service failed!\r\n");
            }
            break;
            
        case BLE_ANCS_EVENT_REQUEST_COMPLETED: 
        {
            if (ancs_evt->result == BT_STATUS_SUCCESS) {
                if (p_ancs_app->status == ANCS_APP_STATUS_ENABLE_DATA_SOURCE) {
                    /* if notification source is not enabled, enable it */

                    ble_ancs_enable_notification_source(ancs_evt->connection_handle);
                    p_ancs_app->status = ANCS_APP_STATUS_ENABLE_NOTIF_SOURCE;
                } else {
                    p_ancs_app->status = ANCS_APP_STATUS_NONE;
                }
            } else {
                LOG_I(ANCS, "[ANCSapp]Enable data source/notification source failed! result = %x\r\n", ancs_evt->result);
                p_ancs_app->status = ANCS_APP_STATUS_NONE;
            }
        }
            break;
            
        case BLE_ANCS_EVENT_IOS_NOTIFICATION: 
            /*If you need ,get notification attribute*/
            ble_ancs_deal_with_new_notification(&ancs_evt->data.notification);
            break;

        case BLE_ANCS_EVENT_DISCONNECTED: 
            p_ancs_app->notif_counter = 0;
            LOG_I(ANCS, "[ANCSapp]ANCS disconnected!\r\n");
            break;
        default:
            break;
    }
}


/*****************************************************************************
* FUNCTION
*  ble_ancs_app_init
* DESCRIPTION
* Initialize the context p_ancs_app and ancs service
* PARAMETERS
*
* RETURNS
*  ObStatus
*****************************************************************************/
void ble_ancs_app_init(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    LOG_I(ANCS, "[ANCSapp]ble_ancs_app_init\r\n");
    
    memset(p_ancs_app, 0, sizeof(ble_ancs_app_cntx_t));

    ble_ancs_start(ble_ancs_app_event_callback);
}


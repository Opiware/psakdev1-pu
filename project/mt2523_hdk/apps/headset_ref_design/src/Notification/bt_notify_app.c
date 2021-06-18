/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The file is used for testing BT notification..
 *
 ****************************************************************************/

//#include "bt_notify.h"
#include "stdint.h"
#include <string.h>
#include "stdio.h"

#include <FreeRTOS.h>

#include "queue.h"
#include "task.h"
#include "bt_gap.h"
#include "bt_gap_le.h"
#include "bt_system.h"
#include "bt_spp.h"
#include "bt_callback_manager.h"
#include "bt_notify.h"
#include "task_def.h"
#include "bt_notify_app.h"

#include "syslog.h"

#include "fota_bt_common.h"
log_create_module(NOTIFY_APP, PRINT_LEVEL_INFO);


/*****************************************************************************
 * define
 *****************************************************************************/

/*****************************************************************************
 * typedef
 *****************************************************************************/

void bt_notify_app_callback(void *data)
{
    LOG_I(NOTIFY_APP, "\r\n[App test]callback task\r\n");
    
    bt_notify_callback_data_t *p_data = (bt_notify_callback_data_t *)data;
   // queue_item.event_id = p_data->evt_id;

    switch (p_data->evt_id) {
        case BT_NOTIFY_EVENT_CONNECTION: {
           
            break;
        }
        case BT_NOTIFY_EVENT_DISCONNECTION: {
            
            break;
        }
        case BT_NOTIFY_EVENT_SEND_IND: {
           
            break;
        }
        case BT_NOTIFY_EVENT_DATA_RECEIVED: {
            
            break;
        }
        case BT_NOTIFY_EVENT_NOTIFICATION: {
            if (p_data->notification.action == BT_NOTIFY_ACTION_TYPE_NEW) {

                LOG_I(NOTIFY_APP, "\r\n[Notification]Incoming notification!!\r\n");
            }
            break;
        }
        case BT_NOTIFY_EVENT_MISSED_CALL: {
            LOG_I(NOTIFY_APP, "\r\n[Notification]Incoming notification!!\r\n");
            break;
        }
        case BT_NOTIFY_EVENT_SMS: {
            LOG_I(NOTIFY_APP, "\r\n[Notification]Incoming notification!!\r\n");
            break;
        }
        default: {
            break;
        }
    }  
  
}
void bt_notify_app_init(void)
{
    bt_notify_init((BT_SPP_SERVER_ID_START + 2));
    bt_notify_register_callback(NULL, "app_test", bt_notify_app_callback);
}





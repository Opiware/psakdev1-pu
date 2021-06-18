/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The header file for users.
 *
 ****************************************************************************/



#ifndef __BT_NOTIFY_TASK_H__
#define __BT_NOTIFY_TASK_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "queue.h"
#include "task_def.h"
#include "ble_dogp_adp_service.h"

typedef struct {
    bt_msg_type_t msg;
    bt_status_t status;  
    void *buff;
} bt_notify_service_message_t;
void bt_notify_service_task_init(void);
void bt_notify_service_send_queue(bt_msg_type_t msg, bt_status_t status, void* data_ind);
bt_status_t bt_notify_service_event_callback(bt_msg_type_t msg, 
     bt_status_t status, 
     void *buff);

void bt_notify_dogp_callback_func(ble_dogp_adp_event_t event, void *callback_param);


#endif/*__BT_NOTIFY_TASK_H__*/


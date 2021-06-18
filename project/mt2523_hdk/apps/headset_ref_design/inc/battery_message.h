/* Copyright Statement:
 *
 */

#ifndef __BATTERY_MESSAGE_H__
#define __BATTERY_MESSAGE_H__

#include <stdbool.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "syslog.h"
#include "task_def.h"
#include "battery_management.h"

#ifdef __cplusplus
extern "C" {
#endif
/********************************************************
 * Macro & Define
 *
 ********************************************************/
#define APP_TASK_QUEUE_SIZE     BMT_APP_QUEUE_LENGTH
#define APP_TASK_MSG_QUEUE_NUM    5

#define BATTERY_MSG_SW_MAGIC            0xdeac0000      /* SW battery magic handle number*/
#define BATTERY_MSG_SW_HANDLE_MASK      0xffff          /* SW battery handle mask section*/

/********************************************************
 * Enum & Structures
 *
 ********************************************************/
typedef struct {
    battery_management_event_t event;
    const void *data;
} battery_message_context_t;

typedef struct {
    QueueHandle_t   queue;
    bool    is_used;
} battery_message_queue_t;

typedef struct {
    battery_message_queue_t msg_queue[APP_TASK_MSG_QUEUE_NUM];
    uint32_t used_msg_queue_count;
    bool register_callback_flag;

} battery_message_handle_context_t;

/********************************************************
 * External Function
 *
 ********************************************************/
bool battery_message_allocate(uint32_t *handle);
bool battery_message_receive(uint32_t handle, battery_message_context_t *message);


#ifdef __cplusplus
}
#endif

#endif /*__BATTERY_MESSAGE_H__*/


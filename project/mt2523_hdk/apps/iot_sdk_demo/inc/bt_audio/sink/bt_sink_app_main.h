/* Copyright Statement:
 *
 */

#ifndef BT_SINK_APP_MAIN_H
#define BT_SINK_APP_MAIN_H

#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "bt_sink_srv.h"
#include "bt_sink_app_event.h"

#define BT_SINK_APP_TASK_PRIORITY   (1)
#define BT_SINK_APP_TASK_STACK_SIZE (1024)
#define BT_SINK_APP_QUEUE_SIZE      (30)

typedef struct {
    QueueHandle_t            queue_handle;
    bt_sink_srv_state_t      state;
    bt_sink_app_event_node_t dynamic_callback_header;
    bt_sink_srv_event_t      invoking;
} bt_sink_app_context_t;

extern bt_sink_app_context_t bt_sink_app_context;

#define bt_sink_app_report(_message,...) LOG_I(sink_app, (_message), ##__VA_ARGS__)
#define bt_sink_app_assert configASSERT

void bt_sink_app_task_create(void);
void bt_sink_app_task_main(void *arg);
#endif /* BT_SINK_APP_MAIN_H */


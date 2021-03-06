/* Copyright Statement:
 *
 */

#include "FreeRTOS.h"
#include "task.h"
#include "bt_sink_app_main.h"
#include "bt_sink_app_event.h"
#include "bt_sink_app_cmd.h"
#include "bt_sink_srv.h"
#include "task_def.h"
#include "syslog.h"

bt_sink_app_context_t bt_sink_app_context;

log_create_module(sink_app, PRINT_LEVEL_INFO);

void bt_sink_srv_event_callback(bt_sink_srv_event_t event_id, bt_sink_srv_event_param_t *param)
{
    void *event_params = NULL;

    if (NULL != param) {
        event_params = (bt_sink_srv_event_param_t *)pvPortMalloc(sizeof((*param)));
        memcpy(event_params, param, sizeof(*param));
    }
    bt_sink_app_event_post(event_id, event_params, bt_sink_app_event_post_callback);
}

void bt_sink_app_task_main(void *arg)
{
    bt_sink_app_event_t event;
    bt_sink_srv_features_config_t config;

    bt_sink_app_report("enter main");

    memset(&bt_sink_app_context, 0, sizeof(bt_sink_app_context_t));

    // initialize event
    bt_sink_app_event_init();

    // initialize queue
    bt_sink_app_context.queue_handle = xQueueCreate(BT_SINK_APP_QUEUE_SIZE, sizeof(bt_sink_app_event_t));

    bt_sink_app_event_register_callback(BT_SINK_SRV_EVENT_ALL, bt_sink_app_event_handler);

    bt_sink_app_atci_init();

    // initialize sink service
    config.features = BT_SINK_SRV_FEATURE_DISCOVERABLE_ONCE;
    bt_sink_srv_init(&config);

    while (1) {
        if (pdPASS == xQueueReceive(bt_sink_app_context.queue_handle, &event, portMAX_DELAY)) {
            bt_sink_app_event_process(&event);
        }
    }
}

void bt_sink_app_task_create(void)
{
    xTaskCreate(bt_sink_app_task_main,
                BT_SINK_APP_TASK_NAME,
                BT_SINK_APP_TASK_STACKSIZE / ((uint32_t)sizeof(StackType_t)),
                NULL,
                BT_SINK_APP_TASK_PRIO,
                NULL);
}


/* Copyright Statement:
 *
 */

#include "stdint.h"
#include "stdbool.h"
#include "main_screen.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "task_def.h"
#include "syslog.h"

#define UI_TASK_QUEUE_SIZE 20
#define UI_TASK_NAME "UI_DEMO"
#define UI_TASK_STACK_SIZE 4800
#define UI_TASK_PRIORITY 3

typedef struct ui_task_message_struct {
    int message_id;
    int param1;
    void* param2;
} ui_task_message_struct_t;

static struct {
    QueueHandle_t event_queue;
    void* user_data;
} ui_task_cntx;


log_create_module(GRAPHIC_TAG, PRINT_LEVEL_INFO);

/*****************************************************************************
 * FUNCTION
 *  ui_task_msg_handler
 * DESCRIPTION
 *  Process message in queue
 * PARAMETERS
 *  message         [in]
 * RETURNS
 *  void
 *****************************************************************************/
static void ui_task_msg_handler(ui_task_message_struct_t *message)
{
    if (!message) {
        return;
    }
    GRAPHICLOG("ui_task_msg_handler, message_id:%d", message->message_id);
    switch (message->message_id) {
        default:
            common_event_handler((message_id_enum) message->message_id, (int32_t) message->param1, (void*) message->param2);
            break;
                
    }
}
 
/*****************************************************************************
 * FUNCTION
 *  ui_task_main
 * DESCRIPTION
 *  Initialize the UI task.
 * PARAMETERS
 *  arg        [in]
 * RETURNS
 *  void
 *****************************************************************************/
void ui_task_main(void*arg)
{
    ui_task_message_struct_t queue_item;

    ui_task_cntx.event_queue = xQueueCreate(UI_TASK_QUEUE_SIZE , sizeof( ui_task_message_struct_t ) );
    GRAPHICLOG("ui_task_main");  
    main_screen_init(); // Initialize the main screen.
    main_screen_show(); // Display the main screen.
    while (1) {
        if (xQueueReceive(ui_task_cntx.event_queue, &queue_item, portMAX_DELAY)) {
            ui_task_msg_handler(&queue_item);
        }
    }
}

/*****************************************************************************
 * FUNCTION
 *  demo_app_start
 * DESCRIPTION
 *  Create a UI task.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
TaskHandle_t demo_app_start()
{
    TaskHandle_t task_handler;
    xTaskCreate((TaskFunction_t) ui_task_main, UI_TASK_NAME, UI_TASK_STACK_SIZE/(( uint32_t )sizeof( StackType_t )), NULL, UI_TASK_PRIORITY, &task_handler );
    GRAPHICLOG("demo_app_start, task_handler:%d", task_handler);
    return task_handler;
}


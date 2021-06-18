/* Copyright Statement:
 *
 */

#ifndef BT_SINK_APP_MAIN_H
#define BT_SINK_APP_MAIN_H

#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "bt_sink_srv.h"
#include "bt_sink_app_event.h"

#ifdef MTK_LED_ENABLE
#include "bt_sink_app_led.h"
#endif
#ifdef MTK_PROMPT_SOUND_ENABLE
#include "bt_sink_app_voice_prompt.h"
#endif /*MTK_PROMPT_SOUND_ENABLE*/

#define BT_SINK_APP_TASK_PRIORITY   (1)
#define BT_SINK_APP_TASK_STACK_SIZE (1024)
#define BT_SINK_APP_QUEUE_SIZE      (30)

#define  BT_SINK_APP_LOW_BATTERY_ALARM 5
#define  BT_SINK_APP_LOW_BATTERY_POWER_OFF 2

#define BT_SINK_APP_MAX_CONNECTED_DEVICE_NUM      2

/**
    *  @brief Define for the device role.
*/
#define BT_SINK_APP_DEVICE_MASTER  (0x00)
#define BT_SINK_APP_DEVICE_SLAVE       (0x01)
typedef uint8_t bt_sink_app_device_role_t;

typedef struct {
    bt_bd_addr_t addr;
} bt_sink_app_connected_device_t;

typedef struct {
    QueueHandle_t            queue_handle;
    bt_sink_srv_state_t      state;
    bt_sink_app_event_node_t dynamic_callback_header;
    bt_sink_srv_event_t      invoking;
    bt_sink_app_device_role_t device_role;
    uint8_t battery_level;
    bt_sink_srv_features_config_t feature_config;
    bt_sink_app_connected_device_t remote[BT_SINK_APP_MAX_CONNECTED_DEVICE_NUM];
    bool notify_connection_state;
    //bool connected;
} bt_sink_app_context_t;

extern bt_sink_app_context_t bt_sink_app_context;

#define bt_sink_app_report(_message,...) LOG_I(sink_app, (_message), ##__VA_ARGS__)
#define bt_sink_app_assert configASSERT

void bt_sink_app_task_create(void);
void bt_sink_app_task_main(void *arg);
bt_sink_app_device_role_t bt_sink_app_get_device_role(void);
void bt_sink_app_set_device_role(bt_sink_app_device_role_t role);
void bt_sink_app_key_action_handler(bt_sink_srv_key_value_t key_value, bt_sink_srv_key_action_t key_action);
void bt_sink_app_reset_hf_battery(void);
void bt_sink_app_battery_level_handler(int32_t charger_exist, uint8_t capacity);
#ifdef BT_SINK_APP_NO_ACTION_AUTO_POWER_OFF
void bt_sink_app_auto_power_off_by_state(bt_sink_srv_state_t current);
#endif
bool bt_sink_app_get_connected_device(bt_bd_addr_t *address) ;

#endif /* BT_SINK_APP_MAIN_H */


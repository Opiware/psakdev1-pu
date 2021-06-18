/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_APP_LED_INTERNAL_H__
#define __BT_SINK_APP_LED_INTERNAL_H__

#include "bt_sink_app_led.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* LED light States */
typedef uint8_t bt_sink_app_led_lighting_state_t;
#define BT_SINK_APP_LED_LIGHTING_STATE_IDLE               (0x00)
#define BT_SINK_APP_LED_LIGHTING_STATE_FLASH             (0x01)
#define BT_SINK_APP_LED_LIGHTING_STATE_INTERVAL    (0x02)

typedef uint8_t bt_sink_app_led_status_t;
#define BT_SINK_APP_LED_STATUS_OFF              (0x00)
#define BT_SINK_APP_LED_STATUS_ON                (0x01)

typedef enum {
    BT_SINK_APP_LED_MODE_NONE,               
    BT_SINK_APP_LED_MODE_LONG_ON,                
    BT_SINK_APP_LED_MODE_LONG_OFF,
    BT_SINK_APP_LED_MODE_FLASH_INFINITE,
    BT_SINK_APP_LED_MODE_FLASH_NORMAL,
    BT_SINK_APP_LED_MODE_PERIOD_INFINITE
} bt_sink_app_led_mode_t;

typedef struct {
    TimerHandle_t timer_hd;
    bt_sink_app_led_state_config_table_t*curr_config;
    bt_sink_app_led_mode_t mode;
    uint8_t remain_period_count;
    uint8_t remain_flash_count;
    bt_sink_app_led_lighting_state_t state;
    bt_sink_app_led_status_t status; 
} bt_sink_app_led_cntx_t;

const bt_sink_app_led_state_config_table_t *bt_sink_app_led_get_state_cfg_table(void);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_APP_LED_INTERNAL_H__ */


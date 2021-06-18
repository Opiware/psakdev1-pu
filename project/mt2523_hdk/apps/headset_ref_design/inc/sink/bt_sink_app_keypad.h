/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_APP_KEYPAD_H__
#define __BT_SINK_APP_KEYPAD_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal_keypad.h"
#include "sct_key_event.h"
#include "bt_sink_srv.h"
#include "bt_sink_app_event.h"

typedef struct {
    uint8_t value;
    bt_sink_srv_key_value_t sink_key;
} bt_sink_app_keypad_mapping_t;

typedef struct {
    uint8_t  value;              // FUNC, NEXT or PREV key
    sct_key_event_t event;       // Press, release, double click or triple event
} bt_sink_app_keypad_key_t;

typedef void (*bt_sink_app_keypad_post_result_t)(bt_sink_srv_event_t event_id, bt_sink_srv_status_t result, void *parameters);

void bt_sink_app_keypad_init(void);

void bt_sink_app_keypad_callback(sct_key_event_t event, uint8_t key_data, void *user_data);

void bt_sink_app_keypad_powerkey_callback(void *user_data);

void bt_sink_app_keypad_post_callback(bt_sink_srv_event_t event_id, bt_sink_srv_status_t result, void *parameters);

void bt_sink_app_keypad_post_event(bt_sink_srv_event_t key_event, bt_sink_app_keypad_key_t *key, bt_sink_app_keypad_post_result_t callback);

bt_sink_srv_status_t bt_sink_app_keypad_event_handler(bt_sink_srv_event_t event_id, void *parameters);

#endif /* __BT_SINK_APP_KEYPAD_H__ */


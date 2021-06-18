/* Copyright Statement:
 *
 */

#ifndef BT_SINK_APP_CMD_H
#define BT_SINK_APP_CMD_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    BT_SINK_APP_CMD_RESULT_SUCCESS = 0,
    BT_SINK_APP_CMD_RESULT_UNKNOWN,
    BT_SINK_APP_CMD_RESULT_INVALID_FORMAT,
    BT_SINK_APP_CMD_RESULT_INVALID_KEY,
    BT_SINK_APP_CMD_RESULT_INVALID_ACT,
    BT_SINK_APP_CMD_RESULT_NO_MAPPING,
    BT_SINK_APP_CMD_RESULT_LINK_NOT_EXIST
} bt_sink_app_cmd_result_t;

void bt_sink_app_atci_init(void);

void bt_sink_app_atci_indicate(bt_sink_srv_state_t state);

#endif /* BT_SINK_APP_CMD_H */


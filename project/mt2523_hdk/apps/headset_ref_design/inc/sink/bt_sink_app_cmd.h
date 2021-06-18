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

typedef enum {
    BT_SINK_APP_IND_TYPE_NONE,
    BT_SINK_APP_IND_TYPE_STATE,
    BT_SINK_APP_IND_TYPE_CALLER,
    BT_SINK_APP_IND_TYPE_MISSED_CALL,
    BT_SINK_APP_IND_TYPE_LINK_LOST,
    BT_SINK_APP_IND_TYPE_VISIBILITY,
    BT_SINK_APP_IND_TYPE_PROFILE_CONN_STATE,
    BT_SINK_APP_IND_TYPE_HF_SCO_STATE,
    BT_SINK_APP_INT_TYPE_NOTI_NEW,
    BT_SINK_APP_IND_TYPE_NOTI_MISSED_CALL,
    BT_SINK_APP_INT_TYPE_NOTI_SMS
} bt_sink_app_indicate_type_t;

void bt_sink_app_atci_init(void);

void bt_sink_app_atci_indicate(bt_sink_app_indicate_type_t type, uint32_t params);

#endif /* BT_SINK_APP_CMD_H */


/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_A2DP_H__
#define __BT_SINK_SRV_A2DP_H__

#include "bt_sink_srv_conmgr.h"
#include "bt_sink_srv_ami.h"
#include "bt_a2dp.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv_music.h"
#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SINK_SRV_A2DP_DATA_THRESHHOLD        (6 * 1024)

#define BT_SINK_SRV_A2DP_AWS_DATA_THRESHHOLD    (4 * 1024)

#define BT_SINK_SRV_A2DP_PKT_THRESHHOLD         (5)

#define BT_SINK_SRV_A2DP_AWS_PKT_THRESHHOLD     (3)

#define BT_SINK_SRV_A2DP_AWS_TIMER_DUR          (100 * 1000)  /* ums*/

#define BT_SINK_SRV_A2DP_MAGIC_CODE             (0xa0)

#define __BT_SINK_SRV_A2DP_LIST_DEBUG__


typedef enum {
    BT_SINK_SRV_A2DP_EVENT_CONNECT,
    BT_SINK_SRV_A2DP_EVENT_DISCONNECT,
    BT_SINK_SRV_A2DP_EVENT_PLAY,
    BT_SINK_SRV_A2DP_EVENT_SUSPEND,
    BT_SINK_SRV_A2DP_EVENT_STREAMING,

    /* add before this event */
    BT_SINK_SRV_A2DP_EVENT_ALL
} bt_sink_srv_a2dp_event_type_t;

typedef enum {
    VOLUME_UP     = 0,
    VOLUME_DOWN   = 1,

    VOLUME_TOTAL
} volume_change_type_t;

typedef struct {
    bt_sink_srv_a2dp_event_type_t event;
    void *param;
} bt_sink_srv_a2dp_event_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_a2dp_connect_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_a2dp_disconnect_t;

typedef struct {
    uint32_t handle;
} bt_sink_srv_a2dp_play_t;

typedef struct {
    uint32_t handle;
} bt_sink_srv_a2dp_suspend_t;

typedef struct {
    uint32_t handle;
} bt_sink_srv_a2dp_streaming_t;


void bt_sink_srv_a2dp_ami_hdr(bt_sink_srv_am_id_t aud_id, bt_sink_srv_am_cb_msg_class_t msg_id, bt_sink_srv_am_cb_sub_msg_t sub_msg, void *user);

bt_sink_srv_status_t bt_sink_srv_a2dp_action_handler(bt_sink_srv_action_t action, void *param);

bt_status_t bt_sink_srv_a2dp_get_init_params(bt_a2dp_init_params_t *param);

bt_status_t bt_sink_srv_a2dp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

int32_t bt_sink_srv_a2dp_change_volume(uint8_t type);
#ifdef __MUSIC_MODE_SWITCH_SUPPORT__
int32_t bt_sink_srv_a2dp_mode_check(bt_sink_srv_music_mode_t mode);
#endif

#ifdef __cplusplus
}
#endif

#endif

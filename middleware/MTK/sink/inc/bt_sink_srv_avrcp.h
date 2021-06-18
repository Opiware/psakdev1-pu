/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_AVRCP_H__
#define __BT_SINK_SRV_AVRCP_H__

#include "stdint.h"
#include "bt_sink_srv_conmgr.h"
#include "bt_avrcp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BT_SINK_SRV_AVRCP_DISCONNECTED,
    BT_SINK_SRV_AVRCP_CONNECTING,
    BT_SINK_SRV_AVRCP_CONNECTED,
    BT_SINK_SRV_AVRCP_PLAY,
    BT_SINK_SRV_AVRCP_STOP,

    BT_SINK_SRV_AVRCP_TOTAL
} bt_sink_srv_avrcp_state_t;

typedef enum {
    BT_SINK_SRV_AVRCP_EVENT_CONNECT,
    BT_SINK_SRV_AVRCP_EVENT_DISCONNECT,

    /* add before this event */
    BT_SINK_SRV_AVRCP_EVENT_ALL
} bt_sink_srv_avrcp_event_type_t;

typedef struct {
    bt_sink_srv_avrcp_event_type_t event;
    void *param;
} bt_sink_srv_avrcp_event_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_avrcp_connect_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_avrcp_disconnect_t;

typedef enum {
    BT_SINK_SRV_PARTYMODE_INTERRUPT,            /**< partymode barge in */
    BT_SINK_SRV_PARTYMODE_DROP,
    BT_SINK_SRV_PARTYMODE_TOTAL
} bt_sink_srv_partymode_t;

bt_sink_srv_status_t bt_sink_srv_avrcp_action_handler(bt_sink_srv_action_t action, void *param);

int32_t bt_sink_srv_avrcp_play_music(uint32_t handle);

int32_t bt_sink_srv_avrcp_stop_music(uint32_t handle);

int32_t bt_sink_srv_avrcp_change_ntrack(uint32_t handle);

int32_t bt_sink_srv_avrcp_change_ptrack(uint32_t handle);

bt_status_t bt_sink_srv_avrcp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

bt_sink_srv_status_t bt_sink_srv_music_avrcp_action_handler(bt_sink_srv_action_t action, void *param);

uint8_t bt_sink_srv_avrcp_get_volume_value(uint8_t vol_level);
uint8_t bt_sink_srv_avrcp_get_volume_level(uint8_t volume);
bt_status_t bt_sink_srv_avrcp_volume_notification(uint32_t handle, uint8_t vol_level);
#ifdef __cplusplus
}
#endif

#endif

/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_AWS_H__
#define __BT_SINK_SRV_AWS_H__

#include "bt_sink_srv_ami.h"

#ifdef __BT_AWS_SUPPORT__
#include "bt_sink_srv_conmgr.h"
#include "bt_aws.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv.h"


#define BT_SINK_SRV_AWS_DATA_THRESHHOLD    (2 * 1024)

#define BT_SINK_SRV_AWS_PKT_THRESHHOLD     (2)

#define BT_SINK_SRV_AWS_INVALID_TIME       0xFFFFFFFF


/* custom SNK cmd following TLV */
#define BT_SINK_SRV_AWS_CMD_SNK_INTERRUPT              (0x01)
#define BT_SINK_SRV_AWS_CMD_SNK_RESUME                 (0x02)


#define BT_SINK_SRV_AWS_CMD_MODE_SWITCH                (0xf0)
#define BT_SINK_SRV_AWS_CMD_VOLUME_SET                 (0xf1)



#ifdef __cplusplus
extern "C" {
#endif

#define __BT_SINK_SRV_AWS_LIST_DEBUG__


void bt_sink_srv_aws_ami_hdr(bt_sink_srv_am_id_t aud_id, bt_sink_srv_am_cb_msg_class_t msg_id, bt_sink_srv_am_cb_sub_msg_t sub_msg, void *user);

bt_sink_srv_status_t bt_sink_srv_aws_action_handler(bt_sink_srv_action_t action, void *param);

bt_status_t bt_sink_srv_aws_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

int32_t bt_sink_srv_aws_set_pause(uint32_t handle);

int32_t bt_sink_srv_aws_set_play(uint32_t handle, bt_aws_role_t role, uint8_t change_track);

int32_t bt_sink_srv_aws_set_mode_change(uint32_t handle);

int32_t bt_sink_srv_aws_set_resync(uint32_t handle);

int32_t bt_sink_srv_aws_notify_play(uint32_t handle);

int32_t bt_sink_srv_aws_notify_stop(uint32_t handle);

int32_t bt_sink_srv_aws_notify_change_ntrack(uint32_t handle);

int32_t bt_sink_srv_aws_notify_change_ptrack(uint32_t handle);

int32_t bt_sink_srv_aws_notify_resync(uint32_t handle);

int32_t bt_sink_srv_aws_notify_vol_level(uint32_t handle, uint8_t level);

int32_t bt_sink_srv_aws_notify_vol_up(uint32_t handle);

int32_t bt_sink_srv_aws_notify_vol_down(uint32_t handle);

int32_t bt_sink_srv_aws_notify_mode_change(uint32_t handle, uint8_t mode);

void bt_sink_srv_local_mode_check(bt_sink_srv_music_mode_t mode);

#ifdef __cplusplus
}
#endif

#endif
#endif /* __BT_AWS_SUPPORT__ */


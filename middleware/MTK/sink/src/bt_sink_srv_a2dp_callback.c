/* Copyright Statement:
 *
 */


#include "bt_sink_srv_a2dp.h"
#include "bt_sink_srv_avrcp.h"
#include "bt_sink_srv_aws_a2dp.h"
#include "bt_sink_srv_utils.h"


/* A2DP callback function */
bt_status_t bt_sink_srv_music_a2dp_get_init_params(bt_a2dp_init_params_t *param)
{
    return bt_sink_srv_a2dp_get_init_params(param);
}


void bt_sink_srv_music_a2dp_ami_hdr(bt_sink_srv_am_id_t aud_id, bt_sink_srv_am_cb_msg_class_t msg_id, bt_sink_srv_am_cb_sub_msg_t sub_msg, void *param)
{
    bt_sink_srv_a2dp_ami_hdr(aud_id, msg_id, sub_msg, param);
}


bt_sink_srv_status_t bt_sink_srv_music_a2dp_action_handler(bt_sink_srv_action_t action, void *param)
{
   return bt_sink_srv_a2dp_action_handler(action, param);
}


bt_status_t bt_sink_srv_music_a2dp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer)
{
    return bt_sink_srv_a2dp_common_callback(msg, status, buffer);
}


/* AVRCP callback function */
bt_sink_srv_status_t bt_sink_srv_music_avrcp_action_handler(bt_sink_srv_action_t action, void *param)
{
    return bt_sink_srv_avrcp_action_handler(action, param);
}


#ifdef __BT_AWS_A2DP_SUPPORT__
/* AWS_A2DP callback function */
bt_status_t bt_sink_srv_music_aws_a2dp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer)
{
    return bt_sink_srv_aws_a2dp_common_callback(msg, status, buffer);
}


void bt_sink_srv_music_aws_a2dp_ami_hdr(bt_sink_srv_am_id_t aud_id, bt_sink_srv_am_cb_msg_class_t msg_id, bt_sink_srv_am_cb_sub_msg_t sub_msg, void *param)
{
    bt_sink_srv_aws_a2dp_ami_hdr(aud_id, msg_id, sub_msg, param);
}


bt_sink_srv_status_t bt_sink_srv_music_aws_a2dp_action_handler(bt_sink_srv_action_t action, void *param)
{
   return bt_sink_srv_aws_a2dp_action_handler(action, param);
}
#endif


/* Pseudo device common callback handle */
void bt_sink_srv_music_play_handle(audio_src_srv_handle_t *handle)
{
    if (AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP == handle->type) {
        bt_sink_srv_a2dp_play(handle);
    }
#ifdef __BT_AWS_SUPPORT__
    else if (AUDIO_SRC_SRV_PSEUDO_DEVICE_AWS_A2DP == handle->type) {
        bt_sink_srv_aws_a2dp_play(handle);
    }
#endif
    else {
        bt_sink_srv_report("[sink][music_cb]play(error)--type: %d", handle->type);
    }
}


void bt_sink_srv_music_stop_handle(audio_src_srv_handle_t *handle)
{
    if (AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP == handle->type) {
        bt_sink_srv_a2dp_stop(handle);
    } 
#ifdef __BT_AWS_SUPPORT__
    else if (AUDIO_SRC_SRV_PSEUDO_DEVICE_AWS_A2DP == handle->type) {
        bt_sink_srv_aws_a2dp_stop(handle);
    }
#endif
    else {
        bt_sink_srv_report("[sink][music_cb]stop(error)--type: %d", handle->type);
    }
}


void bt_sink_srv_music_suspend_handle(audio_src_srv_handle_t *handle, audio_src_srv_handle_t *int_hd)
{
    if (AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP == handle->type) {
        bt_sink_srv_a2dp_suspend(handle, int_hd);
    }
#ifdef __BT_AWS_SUPPORT__
    else if (AUDIO_SRC_SRV_PSEUDO_DEVICE_AWS_A2DP == handle->type) {
        bt_sink_srv_aws_a2dp_suspend(handle, int_hd);
    }  
#endif
    else {
        bt_sink_srv_report("[sink][music_cb]suspend(error)--type: %d", handle->type);
    }
}


void bt_sink_srv_music_reject_handle(audio_src_srv_handle_t *handle)
{
    if (AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP == handle->type) {
        bt_sink_srv_a2dp_reject(handle);
    } 
#ifdef __BT_AWS_SUPPORT__
    else if (AUDIO_SRC_SRV_PSEUDO_DEVICE_AWS_A2DP == handle->type) {
        bt_sink_srv_aws_a2dp_reject(handle);
    }
#endif
    else {
        bt_sink_srv_report("[sink][music_cb]reject(error)--type: %d", handle->type);
    }
}


void bt_sink_srv_music_exception_handle(audio_src_srv_handle_t *handle, int32_t event, void *param)
{
    if (AUDIO_SRC_SRV_PSEUDO_DEVICE_A2DP == handle->type) {
        bt_sink_srv_a2dp_exception(handle, event, param);
    }
#ifdef __BT_AWS_SUPPORT__
    else if (AUDIO_SRC_SRV_PSEUDO_DEVICE_AWS_A2DP == handle->type) {
        bt_sink_srv_aws_a2dp_exception(handle, event, param);
    }  
#endif
    else {
        bt_sink_srv_report("[sink][music_cb]exception(error)--type: %d", handle->type);
    }
}


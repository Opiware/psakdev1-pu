/* Copyright Statement:
 *
 */

#ifndef __BT_SOURCE_SRV_A2DP_H__
#define __BT_SOURCE_SRV_A2DP_H__

#include "bt_a2dp.h"
#include "bt_avrcp.h"
#include "bt_codec.h"
  
#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    BT_SOURCE_SRV_A2DP_IDLE = 0,
    BT_SOURCE_SRV_A2DP_OPEN, //open
    BT_SOURCE_SRV_A2DP_STREAMING, //
    BT_SOURCE_SRV_A2DP_READY, //
    BT_SOURCE_SRV_A2DP_PLAYING,

    BT_SOURCE_SRV_A2DP_TOTAL
} bt_source_srv_a2dp_state_t;



//void bt_source_srv_a2dp_init(void);
//void bt_source_srv_a2dp_deinit(void);

bt_status_t bt_source_srv_a2dp_get_init_params(bt_a2dp_init_params_t *param);
bt_status_t bt_source_srv_a2dp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer); // recieve event from a2dp profile
void bt_source_srv_a2dp_codec_handler(bt_media_handle_t *handle, bt_codec_media_event_t event_id);

#ifdef __cplusplus
}
#endif

#endif

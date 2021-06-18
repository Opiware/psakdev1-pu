/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_VP_PESUDO_DEV_H__
#define __BT_SINK_SRV_VP_PESUDO_DEV_H__

#include <stdint.h>
#include "bt_type.h"
#include "bt_sink_srv_resource.h"
#include "audio_src_srv.h"
#include "bt_sink_srv_ami.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    audio_src_srv_handle_t *audio_src;
    bt_sink_srv_action_t action;
} bt_sink_srv_vp_dev_context_t;

void bt_sink_srv_vp_dev_init(void) ;
audio_src_srv_handle_t * bt_sink_srv_vp_dev_get_audio_handle(void);
void bt_sink_srv_vp_dev_set_action(bt_sink_srv_action_t action);
void bt_sink_srv_vp_send_voice_prompt_event(bt_sink_srv_action_t action);
#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_VP_PESUDO_DEV_H__ */

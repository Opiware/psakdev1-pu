/* Copyright Statement:
 *
 */

#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#ifdef MTK_AUDIO_MP3_ENABLED
#define __LOCAL_PLAYER_ENABLE__
#endif

#ifdef __LOCAL_PLAYER_ENABLE__

#include <stdbool.h>
#include <stdint.h>
#include "bt_sink_srv.h"

void audio_player_init(void);

int32_t audio_player_play(void);

int32_t audio_player_pause(void);

int32_t audio_player_next_track(void);

int32_t audio_player_previous_track(void);

int32_t audio_player_volume_up(void);

int32_t audio_player_volume_down(void);

int32_t audio_player_stop(void);

bt_sink_srv_status_t audio_player_sink_key_action(bt_sink_srv_key_value_t key_value,
        bt_sink_srv_key_action_t key_action);

#endif /* __LOCAL_PLAYER_ENABLE__ */
#endif /* AUDIO_PLAYER_H */


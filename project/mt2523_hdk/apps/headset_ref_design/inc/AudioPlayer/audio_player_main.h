/* Copyright Statement:
 *
 */

#ifndef AUDIO_PLAYER_MAIN_H
#define AUDIO_PLAYER_MAIN_H

#include "audio_player.h"

#ifdef __LOCAL_PLAYER_ENABLE__

#include <stdbool.h>
#include <stdint.h>
#include "task_def.h"


#define AUDIO_PLAYER_TASK_NAME              "audply_task"
#define AUDIO_PLAYER_TASK_STACKSIZE         (1024 * 4) /* unit byte */
#define AUDIO_PLAYER_TASK_PRIORITY          TASK_PRIORITY_NORMAL


void audio_player_task_main(void *param);

int32_t bt_sink_srv_mp3_file_callback(bt_sink_srv_mp3_file_event_type_t msg,  bt_sink_srv_mp3_event_t event);

#endif /* __LOCAL_PLAYER_ENABLE__ */
#endif /* AUDIO_PLAYER_MAIN_H */


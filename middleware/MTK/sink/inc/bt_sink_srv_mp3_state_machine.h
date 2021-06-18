/* Copyright Statement:
 *
 */

#ifndef BT_SINK_SRV_MP3_STATE_MACHINE_H
#define BT_SINK_SRV_MP3_STATE_MACHINE_H

typedef enum{
    BT_SINK_SRV_MP3_RECOVERY_STATUS_DISCONNECT,
    BT_SINK_SRV_MP3_RECOVERY_STATUS_END
} bt_sink_srv_mp3_recovery_status_t;

void bt_sink_srv_music_mp3_set_target_state(bt_sink_srv_music_state_t state);

void bt_sink_srv_music_mp3_state_process();

bool bt_sink_srv_music_mp3_set_target_and_process(bt_sink_srv_music_state_t state);

void bt_sink_srv_music_mp3_recovery_local_state(bt_sink_srv_mp3_recovery_status_t status);

#endif /* BT_SINK_SRV_MP3_STATE_MACHINE_H */


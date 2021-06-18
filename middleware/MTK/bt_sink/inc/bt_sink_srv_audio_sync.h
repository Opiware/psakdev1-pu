/* Copyright Statement:
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "bt_a2dp.h"
#include "bt_codec.h"
#include "bt_sink_srv_am_med_mgr.h"
#include "bt_aws.h"
#include "hal_audio.h"
#ifndef __BT_SINK_SRV_AUDIO_SYNC_H__
#define __BT_SINK_SRV_AUDIO_SYNC_H__
/**** Definition ****/
#define A2DP_SILENCE_BUF_LEN 516

//--------------------------------------------
// Functionality:
//   Parse the sample count in a packet.
//--------------------------------------------

void bt_aws_clear_gpio(hal_gpio_pin_t gpio_num);

/**** Public API           ****/
// Call this API after set flag.
void bt_a2dp_plh_init(bt_media_handle_t *handle);

// // Call this API after clear flag.
void bt_a2dp_plh_deinit(void);

// Call this API after set flag.
void bt_mp3_plh_init(bt_media_handle_t *handle);

// // Call this API after clear flag.
void bt_mp3_plh_deinit(void);

void bt_a2dp_plh_write_frame_done(bt_hci_packet_t *packet );

void bt_a2dp_plh_check_packet(bt_hci_packet_t *packet, uint32_t *retSilenceNum, bool *retDrop);

uint16_t bt_sink_srv_fill_silence_frame(uint8_t **ptr, uint32_t numFrame);

bt_status_t bt_sink_srv_audio_clock_init(void);
#ifdef __BT_AWS_SUPPORT__
bt_status_t bt_sink_srv_audio_clock_calibrate(
    bt_media_handle_t *media_handle,
    bt_aws_codec_type_t type,
    uint32_t sampling_rate);
#endif
#endif // __BT_SINK_SRV_AUDIO_SYNC_H__

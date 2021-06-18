/* Copyright Statement:
 *
 */

#include "bt_codec.h"
const bt_a2dp_sbc_codec_t sink_capability_sbc[1] = {
   {
      18,  /* min_bit_pool       */
      75,  /* max_bit_pool       */
      0xf, /* block_len: all     */
      0xf, /* subband_num: all   */
      0x3, /* both snr/loudness  */
      0xf, /* sample_rate: all   */
      0xf  /* channel_mode: all  */
   }
};

const bt_a2dp_aac_codec_t sink_capability_aac[1] = {
   {
      true,    /*VBR         */
      0xc0,    /*Object type */
      0x03,    /*Channels    */
      0x0ff8,  /*Sample_rate */
      0x60000  /*bit_rate, 384 Kbps */
   }
};

bt_media_handle_t *bt_a2dp_open_codec(bt_a2dp_callback_t bt_a2dp_callback , const bt_a2dp_audio_codec_t *param)
{
    return 0;
}

bt_status_t bt_a2dp_close_codec(bt_media_handle_t *handle)
{
    return BT_STATUS_MEDIA_OK;
}

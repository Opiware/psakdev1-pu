/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_AUDIO_SETTING_H__
#define __BT_SINK_SRV_AUDIO_SETTING_H__


#ifndef MTK_NO_PSRAM_ENABLE
#define __BT_SINK_SRV_AUDIO_SETTING_SUPPORT__
#endif

#include "stdint.h"
#include "audio_coefficient.h"


#define BT_SINK_SRV_AUDIO_SETTING_FALG_GEN_VOL_READY                    (0x0001)


/* EAPS_GAIN_PARAMETER_STREAM_OUT_GAIN_SIZE */
#if PRODUCT_VERSION == 2533
#define BT_SINK_SRV_AUDIO_SETTING_STREAM_OUT_GAIN_LEV                   (16)
#else
#define BT_SINK_SRV_AUDIO_SETTING_STREAM_OUT_GAIN_LEV                   (16)
#endif

/* EAPS_GAIN_PARAMETER_STREAM_IN_GAIN_SIZE */
#define BT_SINK_SRV_AUDIO_SETTING_STREAM_IN_GAIN_LEV                    (1)


typedef uint16_t device_t;

typedef enum {
    VOL_A2DP = 0,
    VOL_HFP,
    VOL_PCM,
    VOL_MP3,

    VOL_DEF, /* stream out only */
    VOL_TOTAL
} vol_type_t;

typedef struct {
    uint32_t digital;
    uint32_t analog;
} vol_t;

typedef struct {
    device_t dev;
    uint8_t lev;
} a2dp_vol_info_t;

typedef struct {
    vol_t vol;
} a2dp_vol_t;

typedef struct {
    uint8_t codec;
    device_t dev_in;
    uint8_t lev_in;
    device_t dev_out;
    uint8_t lev_out;
} hfp_vol_info_t;

typedef struct {
    vol_t vol_in;
    vol_t vol_out;
} hfp_vol_t;

typedef struct {
    device_t dev;
    uint8_t lev;
} pcm_vol_info_t;

typedef struct {
    vol_t vol;
} pcm_vol_t;

typedef struct {
    device_t dev;
    uint8_t lev;
} mp3_vol_info_t;

typedef struct {
    vol_t vol;
} mp3_vol_t;

typedef struct {
    device_t dev;
    uint8_t lev;
} def_vol_info_t;

typedef struct {
    vol_t vol;
} def_vol_t;

typedef struct {
    vol_type_t type;
    union {
        a2dp_vol_info_t a2dp_vol_info;
        hfp_vol_info_t hfp_vol_info;
        pcm_vol_info_t pcm_vol_info;
        mp3_vol_info_t mp3_vol_info;
        def_vol_info_t def_vol_info;
    } vol_info;
} bt_sink_srv_audio_setting_vol_info_t;

typedef struct {
    vol_type_t type;
    union {
        a2dp_vol_t a2dp_vol;
        hfp_vol_t hfp_vol;
        pcm_vol_t pcm_vol;
        mp3_vol_t mp3_vol;
        def_vol_t def_vol;
    } vol;
} bt_sink_srv_audio_setting_vol_t;

typedef struct {
    uint32_t flag;
} bt_sink_srv_audio_setting_context_t;

void bt_sink_srv_audio_setting_init(void);

int32_t bt_sink_srv_audio_setting_get_vol(bt_sink_srv_audio_setting_vol_info_t *vol_info,
            bt_sink_srv_audio_setting_vol_t *vol);

void bt_sink_srv_audio_setting_update_voice_fillter_setting(bt_sink_srv_audio_setting_vol_info_t *vol_info,
        audio_eaps_t *am_speech_eaps);

#endif /* __BT_SINK_SRV_AUDIO_SETTING_H__ */


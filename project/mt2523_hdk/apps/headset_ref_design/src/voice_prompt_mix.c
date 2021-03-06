/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#ifdef MTK_PROMPT_SOUND_ENABLE

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "voice_prompt_mix.h"
#include "audio_mixer.h"
#include "audio_codec.h"
#include "bt_sink_srv.h"
#include "mp3_codec.h"
#include "hal_audio_internal_service.h"
#include "prompt_control.h"

log_create_module(VPM, PRINT_LEVEL_INFO);

/********************************************************
 * Macro & Define
 *
 ********************************************************/

typedef struct {
    const uint8_t *buf;
    uint32_t size;
} voice_prompt_tone_buf_t;

/********************************************************
 * Global variable
 *
 ********************************************************/

/* WAV Tone */
static const uint8_t voice_prompt_mix_wav_tone_8k[] = {
    #include "8k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_11k[] = {
//    #include "Batterylow_16k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_12k[] = {
//    #include "12k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_16k[] = {
    #include "battery low_MADPCM.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_22k[] = {
//    #include "Batterylow_22k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_24k[] = {
//    #include "24k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_32k[] = {
//    #include "Batterylow_32k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_44_1k[] = {
    // #include "Batterylow_44o1k.wav.hex"
};

static const uint8_t voice_prompt_mix_wav_tone_48k[] = {
    #include "battery low_MADPCM_10times.wav.hex"
};

/* MP3 Tone */
static const uint8_t voice_prompt_mix_mp3_tone_8k[] = {
    // #include "8k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_11k[] = {
//    #include "11k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_12k[] = {
//    #include "12k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_16k[] = {
//    #include "16k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_22k[] = {
//    #include "22k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_24k[] = {
//    #include "24k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_32k[] = {
//    #include "32k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_44_1k[] = {
    // #include "Batterylow_44o1k.mp3.hex"
};

static const uint8_t voice_prompt_mix_mp3_tone_48k[] = {
//    #include "48k.mp3.hex"
};

/*WAV*/
static voice_prompt_tone_buf_t voice_prompt_tone_wav[] = {
    {
        .buf = voice_prompt_mix_wav_tone_8k,
        .size = sizeof(voice_prompt_mix_wav_tone_8k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_11k,
        .size = sizeof(voice_prompt_mix_wav_tone_11k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_12k,
        .size = sizeof(voice_prompt_mix_wav_tone_12k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_16k,
        .size = sizeof(voice_prompt_mix_wav_tone_16k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_22k,
        .size = sizeof(voice_prompt_mix_wav_tone_22k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_24k,
        .size = sizeof(voice_prompt_mix_wav_tone_24k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_32k,
        .size = sizeof(voice_prompt_mix_wav_tone_32k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_44_1k,
        .size = sizeof(voice_prompt_mix_wav_tone_44_1k),
    },
    {
        .buf = voice_prompt_mix_wav_tone_48k,
        .size = sizeof(voice_prompt_mix_wav_tone_48k),
    },
};

/*MP3*/
static voice_prompt_tone_buf_t voice_prompt_tone_mp3[] = {
    {
        .buf = voice_prompt_mix_mp3_tone_8k,
        .size = sizeof(voice_prompt_mix_mp3_tone_8k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_11k,
        .size = sizeof(voice_prompt_mix_mp3_tone_11k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_12k,
        .size = sizeof(voice_prompt_mix_mp3_tone_12k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_16k,
        .size = sizeof(voice_prompt_mix_mp3_tone_16k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_22k,
        .size = sizeof(voice_prompt_mix_mp3_tone_22k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_24k,
        .size = sizeof(voice_prompt_mix_mp3_tone_24k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_32k,
        .size = sizeof(voice_prompt_mix_mp3_tone_32k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_44_1k,
        .size = sizeof(voice_prompt_mix_mp3_tone_44_1k),
    },
    {
        .buf = voice_prompt_mix_mp3_tone_48k,
        .size = sizeof(voice_prompt_mix_mp3_tone_48k),
    },
};


/********************************************************
 * Function
 *
 ********************************************************/
void voice_prompt_mix_callback(prompt_control_event_t event_id)
{
    LOG_I(VPM, "[VPM]callback event=%d\n", event_id);
    
    if (event_id == PROMPT_CONTROL_MEDIA_END) {
        LOG_I(VPM, "[VPM]callback: playback complete\n");
    }
}

void voice_prompt_mix_play_tone(prompt_control_tone_type_t tone_type, uint8_t tone_idx)
{
    uint8_t *tone_buf = NULL;
    uint32_t tone_size = 0;
    bool ret;

    LOG_I(VPM, "[VPM]mix play type=%d.idx=%d\n", tone_type, tone_idx);

    if (tone_type == VPC_WAV) {
        tone_buf = (uint8_t *)voice_prompt_tone_wav[tone_idx].buf;
        tone_size = voice_prompt_tone_wav[tone_idx].size;
    } else if (tone_type == VPC_MP3) {
        tone_buf = (uint8_t *)voice_prompt_tone_mp3[tone_idx].buf;
        tone_size = voice_prompt_tone_mp3[tone_idx].size;
    }
    ret = prompt_control_play_tone(tone_type, tone_buf, tone_size, voice_prompt_mix_callback);
    
    LOG_I(VPM, "[VPM]mix play result=%d\n", ret);
}

void voice_prompt_mix_stop_tone(void)
{
    LOG_I(VPM, "[VPM]stop codec done.\n");

    prompt_control_stop_tone();
}

#endif


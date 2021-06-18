/* Copyright Statement:
 *
 */

#ifndef __VOICE_PROMPT_H__
#define __VOICE_PROMPT_H__

#include "prompt_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************
 * Macro & Define
 *
 ********************************************************/

/********************************************************
 * Enum & Structures
 *
 ********************************************************/
typedef struct {
    prompt_control_tone_type_t tone_type;
    uint8_t tone_idx;
} voice_prompt_mix_tone_info_t;

/********************************************************
 * External Function
 *
 ********************************************************/
void voice_prompt_mix_set_mixer_gain(uint16_t main, uint16_t side);
void voice_prompt_mix_play_tone(prompt_control_tone_type_t tone_type, uint8_t tone_idx);
void voice_prompt_mix_stop_tone(void);
void voice_prompt_mix_hfp_on(void);
void voice_prompt_mix_hfp_off(void);

#ifdef __cplusplus
}
#endif

#endif /*__VOICE_PROMPT_H__ */


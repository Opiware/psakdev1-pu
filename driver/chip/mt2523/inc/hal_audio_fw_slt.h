/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_FW_SLT_H__
#define __HAL_AUDIO_FW_SLT_H__

#include <stdint.h>

/*******************************************************************************\
| Value Defines                                                                 |
\*******************************************************************************/

#define DSP_AUDIO_FW_SLT_PASS      1
#define DSP_AUDIO_FW_SLT_FAIL      0

/*******************************************************************************\
| Interface                                                                     |
\*******************************************************************************/

int32_t dsp_audio_fw_slt_entry(void);

#endif  /* __HAL_AUDIO_FW_SLT_H__ */

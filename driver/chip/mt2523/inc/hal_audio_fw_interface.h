/* Copyright Statement:
 *
 */

/*******************************************************************************\
|                                                                               |
|  Filename:                                                                    |
|  ---------                                                                    |
|   hal_audio_fw_interface.h                                                    |
|                                                                               |
|  Description:                                                                 |
|  ------------                                                                 |
|   Audio FW DSP interface header file                                          |
|                                                                               |
\*******************************************************************************/

#ifndef __HAL_AUDIO_FW_INTERFACE_H__
#define __HAL_AUDIO_FW_INTERFACE_H__

#include <stdint.h>

/*******************************************************************************\
| Value Defines                                                                 |
\*******************************************************************************/

#define DDID_NONE                   0
#define DDID_HEADER_KERNEL          1
#define DDID_AUDIO_HEADER           2
#define DDID_I2S                    3
#define DDID_AAC                    4
#define DDID_SBC_DECODE             5
#define DDID_SPH_ENH                6000
#define DDID_SPH_ENH_1              6001
#define DDID_SPH_ENH_2              6002
#define DDID_SPH_ENH_3              6003

/*******************************************************************************\
| Interface                                                                     |
\*******************************************************************************/

void dsp_audio_fw_reboot(void);
void dsp_audio_fw_init(void);
int32_t dsp_audio_fw_dynamic_download(uint32_t fw_id);

#endif  /* __HAL_AUDIO_FW_INTERFACE_H__ */



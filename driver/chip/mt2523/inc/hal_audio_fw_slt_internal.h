/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_FW_SLT_INTERNAL_H__
#define __HAL_AUDIO_FW_SLT_INTERNAL_H__

#include "hal_audio_fw_interface.h"
#include "hal_audio_fw_library.h"
#include "hal_audio_fw_sherif.h"
#include <stdint.h>

/*******************************************************************************\
| Value Defines                                                                 |
\*******************************************************************************/

#define SLT_READY_MAGIC_WORD    0x8888
#define SLT_CHECKSUM_ANSWER     18
#define DSP_PM_3_RAM_ADDRESS    DSP_PM_ADDR(3, 0x0000)  /* PM 3 RAM (0x0000, 6.5K) */
#define DSP_PM_3_RAM_LENGTH     6656
#define DSP_PM_F_RAM_ADDRESS    DSP_PM_ADDR(3, 0x3C00)  /* PM all non-overlay RAM (0x3C00, 1K) */
#define DSP_PM_F_RAM_LENGTH     1024

#endif  /* __HAL_AUDIO_FW_SLT_INTERNAL_H__ */

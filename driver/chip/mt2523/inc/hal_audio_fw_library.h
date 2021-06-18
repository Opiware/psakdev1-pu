/* Copyright Statement:
 *
 */

/*******************************************************************************\
|                                                                               |
|  Filename:                                                                    |
|  ---------                                                                    |
|   hal_audio_fw_library.h                                                      |
|                                                                               |
|  Description:                                                                 |
|  ------------                                                                 |
|   AUDIO FW DSP library header file                                            |
|                                                                               |
\*******************************************************************************/

#ifndef __HAL_AUDIO_FW_LIBRARY_H__
#define __HAL_AUDIO_FW_LIBRARY_H__

/*******************************************************************************\
| Include Files                                                                 |
\*******************************************************************************/

#include <stdint.h>
#include "hal_audio_fw_internal_common.h"

/*******************************************************************************\
| Interface                                                                     |
\*******************************************************************************/

void dsp_audio_fw_slt_process(void);
void dsp_audio_fw_lib_reboot(void);
void dsp_audio_fw_lib_init(void);
int32_t dsp_audio_fw_lib_dynamic_download(uint32_t count, const dsp_audio_fw_type_address_entry_t *entry);

#endif  /* __HAL_AUDIO_FW_LIBRARY_H__ */

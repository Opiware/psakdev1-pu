/* Copyright Statement:
 *
 */

#ifndef __AUDIO_NVDM_H__
#define __AUDIO_NVDM_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "audio_coefficient.h"

void audio_nvdm_init(void);

audio_eaps_t audio_nvdm_get_eaps_data(void);
const audio_eaps_t* audio_nvdm_get_global_eaps_address(void);
void audio_nvdm_get_eaps_data_by_memcpy(audio_eaps_t *eaps);
int audio_nvdm_set_eaps_data(audio_eaps_t eaps);
int audio_nvdm_save_eaps_data_to_nvdm(audio_eaps_t eaps);
audio_eaps_t audio_get_audio_default_coefficient(void);


typedef void (*audio_nvdm_callback_funtion_t)(void *data);

typedef int audio_nvdm_callback_id;  // don't care the value, since we just want its address. Must define as global or static id, that means this parameter will not be died out during the system runing

int audio_nvdm_register_eaps_is_changed_callback(audio_nvdm_callback_id *callback_id, audio_nvdm_callback_funtion_t func, void *data);
int audio_nvdm_unregister_eaps_is_changed_callback(audio_nvdm_callback_id *callback_id);

int16_t audio_nvdm_save_dc_data_to_nvdm(void);

#ifdef __cplusplus
}
#endif


#endif //__AUDIO_NVDM_H__

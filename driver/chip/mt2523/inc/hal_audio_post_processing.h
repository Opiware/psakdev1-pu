/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_POST_PROCESSING_H__
#define __HAL_AUDIO_POST_PROCESSING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t audio_update_iir_design(const uint32_t *parameter);

#ifdef __cplusplus
}
#endif

#endif  /* __HAL_AUDIO_POST_PROCESSING_H__ */

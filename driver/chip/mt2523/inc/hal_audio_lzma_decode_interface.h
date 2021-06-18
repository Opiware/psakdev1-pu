/* Copyright Statement:
 *
 */

#ifndef __HAL_AUDIO_LZMA_DECODE_INTERFACE_H__
#define __HAL_AUDIO_LZMA_DECODE_INTERFACE_H__

#include "hal_audio_7z_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



/*
LZMA_decode_interface
--------------
In:
  destination                - the destination for output data
  destination_length         - the maximum limit of output data size
  source                     - compressed input data
  source_length              - compressed input data length
  compression_property       - compression proerty
  compression_property_Size  - compression property Size
Out:
  destination          - the decompressed output data
  destination_length   - the decompressed output size
  source_length        - decompressed input size
Returns:
  SZ_OK                - OK
  SZ_ERROR_DATA        - Data error
  SZ_ERROR_MEM         - Memory allocation arror
  SZ_ERROR_UNSUPPORTED - Unsupported properties
  SZ_ERROR_INPUT_EOF   - it needs more bytes in input buffer (src)
*/

SRes hal_audio_LZMA_decode(uint32_t *destination, unsigned int *destination_length, const unsigned char *source, unsigned int *source_length,
  const unsigned char *compression_property, unsigned int compression_property_Size, ISzAlloc *g_Alloc);

void hal_audio_LZMA_decode_set_memory(void *memory);


#ifdef __cplusplus
}
#endif

#endif

/* Copyright Statement:
 *
 */


#ifndef __AAC_DECODER_H__
#define __AAC_DECODER_H__

#include <stdint.h>

typedef struct {
    uint32_t internal_buffer_size;  /* Required size of internal buffer (unit: Byte)          */
    uint32_t temporary_buffer_size; /* Required size of temporary buffer (unit: Byte)         */
    uint32_t pcm_buffer_size;       /* Required size of PCM buffer (unit: Byte)               */
    uint32_t bitstream_buffer_size; /* Minimum required size of bitstream buffer (unit: Byte) */
} aac_decoder_buffer_size_t;

typedef struct {
    uint32_t sampling_rate;     /* Sampling rate of the output PCM data (unit: Hz) */
    uint32_t channel_number;    /* Channel number of the output PCM data           */
    uint32_t frame_size;        /* PCM frame size per channel (unit: sample)       */
    uint32_t sbr_flag;          /* SBR bitstream detected or not
                                   0 --> no SBR
                                   1 --> with SBR                                  */
} aac_decoder_runtime_information_t;

/*
    Description
        This function is used to get current version of the library.
    
    Return Value
        Version number
*/
uint32_t aac_decoder_get_version (void);

/*
    Description
        This function get the buffer sizes for AAC decoder.
    
    Output Parameters
        buffer_size : Pointer to the buffer size information structure
    
    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_get_buffer_size (aac_decoder_buffer_size_t *buffer_size);

/*
    Description
        This function initializes the internal buffer for AAC decoder.
    
    Input Parameters
        internal_buffer   : AAC decoder internal buffer
    
    Output Parameters
        handle_pointer    : pointer to the AAC decoder handle
    
    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_init (void **handle_pointer, uint8_t *internal_buffer);

/*
    Description
        This function decodes AAC bitstreams and output PCM data as the following:
        1024 PCM samples per channel
    
    Input Parameters
        handle              : AAC decoder handle
        temp_buffer         : pointer to the temporary buffer
        input_buffer        : pointer to the input bitstream buffer
        input_byte_count    : available input bitstream size (unit: Byte)
        output_buffer       : pointer to the output PCM buffer
        output_byte_count   : available output PCM size (unit: Byte)

    Output Parameters
        input_byte_count    : consumed input bitstream size (unit: Byte)
        output_byte_count   : produced output PCM size (unit: Byte)
        runtime_information : AAC decoder runtime information

    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_process (void *handle, uint8_t *temp_buffer, uint8_t *input_buffer, uint32_t *input_byte_count, int16_t *output_buffer, uint32_t *output_byte_count, aac_decoder_runtime_information_t *runtime_information);

/*
    Description
        This function is used to set optional AAC decoder parameter "dual_sce_config".
    
    Input Parameters
        handle          : AAC decoder handle
        dual_sce_config : 0      --> Output main channel, mono (default)
                          1      --> Output main channel, mono
                          2      --> Output sub-channel, mono
                          3      --> Output both channels, stereo
                          Others --> Undefined

    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_set_parameter_dual_sce_config (void *handle, int32_t dual_sce_config);

/*
    Description
        This function is used to set optional HEAAC decoder parameter "bypass_decode".
    
    Input Parameters
        handle        : HEAAC decoder handle
        bypass_decode : 0      --> Normal decode
                        1      --> Bypass decode
                        Others --> Undefined

    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_set_parameter_bypass_decode (void *handle, int32_t bypass_decode);

/*
    Description
        This function is used to set optional AAC decoder parameter "bypass_crc_check".
    
    Input Parameters
        handle           : AAC decoder handle
        bypass_crc_check : 0      --> Normal CRC check
                           1      --> Bypass CRC check
                           Others --> Undefined

    Return Value
        >= 0 : Normal
        <  0 : Error
*/
int32_t aac_decoder_set_parameter_bypass_crc_check (void *handle, int32_t bypass_crc_check);
 
#endif

/* Copyright Statement:
 *
 */

#ifndef __SBC_ENCODER_H__
#define __SBC_ENCODER_H__

#include <stdint.h>

/* sampling rate */
typedef enum {
    SBC_ENCODER_SAMPLING_RATE_16000HZ = 0x00,
    SBC_ENCODER_SAMPLING_RATE_32000HZ = 0x01,
    SBC_ENCODER_SAMPLING_RATE_44100HZ = 0x02,
    SBC_ENCODER_SAMPLING_RATE_48000HZ = 0x03
} sbc_encoder_sampling_rate_t;

/* blocks */
typedef enum {
    SBC_ENCODER_BLOCK_NUMBER_4  = 0x00,
    SBC_ENCODER_BLOCK_NUMBER_8  = 0x01,
    SBC_ENCODER_BLOCK_NUMBER_12 = 0x02,
    SBC_ENCODER_BLOCK_NUMBER_16 = 0x03
} sbc_encoder_block_number_t;

/* subbands */
typedef enum {
    SBC_ENCODER_SUBBAND_NUMBER_4  = 0x00,
    SBC_ENCODER_SUBBAND_NUMBER_8  = 0x01
} sbc_encoder_subband_number_t;

/* channel mode */
typedef enum {
    SBC_ENCODER_MONO         = 0x00,
    SBC_ENCODER_DUAL_CHANNEL = 0x01,
    SBC_ENCODER_STEREO       = 0x02,
    SBC_ENCODER_JOINT_STEREO = 0x03
} sbc_encoder_channel_mode_t;

/* allocation method */
typedef enum {
    SBC_ENCODER_LOUDNESS = 0x00,
    SBC_ENCODER_SNR      = 0x01
} sbc_encoder_allocation_method_t;

typedef struct {
    sbc_encoder_sampling_rate_t     sampling_rate;
    sbc_encoder_block_number_t      block_number;
    sbc_encoder_subband_number_t    subband_number;
    sbc_encoder_channel_mode_t      channel_mode;
    sbc_encoder_allocation_method_t allocation_method;
} sbc_encoder_initial_parameter_t;

typedef struct {
    uint32_t bitpool_value; /* valid bitpool value range : 2 ~ 250 */
} sbc_encoder_runtime_parameter_t;

/*
    Output Parameter
        internal_buffer_size    SBC encoder internal buffer size, unit: byte
*/
uint32_t sbc_encoder_get_buffer_size (void);

/*
    Input Parameters
        internal_buffer     SBC encoder internal buffer
        initial_parameter   SBC encoder initial parameters
    Output Parameters
        handle_pointer      pointer to the SBC encoder handle
    Return Value
        >= 0    Normal
        < 0     Error
*/
int32_t sbc_encoder_init (void **handle_pointer, uint8_t *internal_buffer, sbc_encoder_initial_parameter_t *initial_parameter);

/*
    Input Parameters
        handle              SBC encoder handle
        input_buffer        pointer to the input PCM buffer
        input_byte_count    pointer to the input PCM buffer size, unit: byte
        output_byte_count   pointer to the available output bitstream buffer size, unit: byte
        runtime_parameter   SBC encoder runtime parameters
    Output Parameters
        input_byte_count    pointer to the consumed input PCM buffer size, unit: byte
        output_buffer       pointer to the output bitstream buffer
        output_byte_count   pointer to the produced output bitstream buffer size, unit: byte
    Return Value
        >= 0    Normal
        < 0     Error
*/
int32_t sbc_encoder_process (void *handle, int16_t *input_buffer, uint32_t *input_byte_count, uint8_t *output_buffer, uint32_t *output_byte_count, sbc_encoder_runtime_parameter_t *runtime_parameter);

#endif // __SBC_ENCODER_H__

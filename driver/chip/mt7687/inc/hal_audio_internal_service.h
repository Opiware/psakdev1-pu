/* Copyright Statement:
 *
 */

 #ifndef __HAL_AUDIO_INTERNAL_SERVICE_H__
#define __HAL_AUDIO_INTERNAL_SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define     MAXIMUM(A,B)                  (((A)>(B))?(A):(B))
#define     MINIMUM(A,B)                  (((A)<(B))?(A):(B))

typedef struct {
    uint32_t write_pointer;
    uint32_t read_pointer;
    uint32_t buffer_byte_count;
    uint8_t *buffer_base_pointer;
} ring_buffer_information_t;

uint32_t ring_buffer_get_data_byte_count(ring_buffer_information_t *p_info);
uint32_t ring_buffer_get_space_byte_count(ring_buffer_information_t *p_info);
void ring_buffer_get_write_information(ring_buffer_information_t *p_info, uint8_t **pp_buffer, uint32_t *p_byte_count);
void ring_buffer_get_read_information(ring_buffer_information_t *p_info, uint8_t **pp_buffer, uint32_t *p_byte_count);
void ring_buffer_write_done(ring_buffer_information_t *p_info, uint32_t write_byte_count);
void ring_buffer_read_done(ring_buffer_information_t *p_info, uint32_t read_byte_count);


#ifdef __cplusplus
}
#endif

#endif /*__HAL_AUDIO_INTERNAL_SERVICE_H__*/


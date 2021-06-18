/* Copyright Statement:
 *
 */

#ifndef __HAL_LZMA_DECODE_INTERFACE_H__
#define __HAL_LZMA_DECODE_INTERFACE_H__

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define LZMA_OK                   0
#define LZMA_ERROR_DATA           1
#define LZMA_ERROR_MEM            2
#define LZMA_ERROR_CRC            3
#define LZMA_ERROR_UNSUPPORTED    4
#define LZMA_ERROR_PARAM          5
#define LZMA_ERROR_INPUT_EOF      6
#define LZMA_ERROR_OUTPUT_EOF     7
#define LZMA_ERROR_READ           8
#define LZMA_ERROR_WRITE          9
#define LZMA_ERROR_PROGRESS       10
#define LZMA_ERROR_FAIL           11
#define LZMA_ERROR_THREAD         12
#define LZMA_ERROR_ARCHIVE        16
#define LZMA_ERROR_NO_ARCHIVE     17

typedef int LZMA_ret;


typedef struct {
    void *(*Alloc)(void *p, size_t size);
    void (*Free)(void *p, void *address);   /* address can be 0 */
} lzma_alloc_t;

/*
    lzma_decode
    --------------
    In:
        destination                 - the destination for output data
        destination_length          - the maximum limit of output data size
        source                      - compressed input data
        source_length               - compressed input data length
        compression_property        - compression proerty
        compression_property_size   - compression property Size
		lzma_alloc                  - the allocator for memory allocate and free
    Out:
        destination                 - the decompressed output data
        destination_length          - the decompressed output size
        source_length               - decompressed input size
    Returns:
        SZ_OK                       - OK
        SZ_ERROR_DATA               - Data error
        SZ_ERROR_MEM                - Memory allocation arror
        SZ_ERROR_UNSUPPORTED        - Unsupported properties
        SZ_ERROR_INPUT_EOF          - it needs more bytes in input buffer (src)
*/

LZMA_ret lzma_decode (
    uint8_t *destination, 
    uint32_t *destination_length, 
    const uint8_t *source, 
    uint32_t *source_length,
    const uint8_t *compression_property, 
    uint32_t compression_property_size, 
    lzma_alloc_t *lzma_alloc);

/*
    lzma_decode to flash, use for decode from flash to flash
    --------------
    In:

        destination                 - the destination address on flash for output data
        reserved_size               - the reserved size for decompressed data
        source                      - the source address on flash of compressed input data
        lzma_alloc                  - the allocator for memory allocate and free

    Returns:
        SZ_OK                       - OK
        SZ_ERROR_DATA               - Data error
        SZ_ERROR_MEM                - Memory allocation arror
        SZ_ERROR_UNSUPPORTED        - Unsupported properties
        SZ_ERROR_INPUT_EOF          - it needs more bytes in input buffer (src)
*/
LZMA_ret lzma_decode2flash(
    uint8_t *destination,
    uint32_t reserved_size,
    const uint8_t *source,
    lzma_alloc_t *lzma_alloc);

#ifdef __cplusplus
}
#endif

#endif  /* __LZMA_DECODE_INTERFACE_H__ */

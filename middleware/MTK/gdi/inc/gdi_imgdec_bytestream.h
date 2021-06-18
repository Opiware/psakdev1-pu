/* Copyright Statement:
 *
 */

#ifndef _GDI_IMGDEC_BYTESTREAM_H_
#define _GDI_IMGDEC_BYTESTREAM_H_

#include "gdi_const.h"
#include "gdi_datatype.h"

#define GDI_IMGDEC_BYTESTREAM_BUFFER_SIZE      2048 /* size of file buffer cache */

typedef struct
{
    int file_size;
    int buffer_content_size;
    int file_offset;
    uint8_t *buffer_reader;
    uint8_t *buffer;
    uint8_t *buffer_ptr;
    uint32_t buffer_ptr_size;
    void *jmpbuf;
    bool is_from_memory;
} gdi_imgdec_bytestream_struct;

extern gdi_result_t gdi_imgdec_bytestream_init(gdi_imgdec_bytestream_struct *handle, uint8_t* src, uint32_t size);
extern gdi_result_t gdi_imgdec_bytestream_deinit(gdi_imgdec_bytestream_struct *handle);

extern gdi_result_t gdi_imgdec_bytestream_read(gdi_imgdec_bytestream_struct *handle, void *ptr, uint32_t size);
extern gdi_result_t gdi_imgdec_bytestream_seek(gdi_imgdec_bytestream_struct *handle, int32_t offset);

#endif /* _GDI_IMGDEC_BYTESTREAM_H_ */ 



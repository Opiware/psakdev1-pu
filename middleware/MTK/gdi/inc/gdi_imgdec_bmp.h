/* Copyright Statement:
 *
 */

#ifndef _GDI_IMGDEC_BMP_H_
#define _GDI_IMGDEC_BMP_H_

#include "gdi_imgdec.h"
#include "gdi_imgdec_internal.h"
#include "gdi_imgdec_bytestream.h"
#include "gdi_imgdec_resizer.h"

typedef enum
{
    GDI_IMGDEC_BMP_DITHER_DISABLE,
    GDI_IMGDEC_BMP_DITHER_RGB565,
    GDI_IMGDEC_BMP_DITHER_RGB8882BITS,
    GDI_IMGDEC_BMP_DITHER_END_OF_ENUM
} gdi_imgdec_bmp_dithering_enum;

typedef struct
{
    GDI_IMGDEC_BASE_STRUCT

    gdi_imgdec_resizer_struct resizer;
    
    gdi_imgdec_bytestream_struct bs;
    uint8_t *bs_buf_ptr;
    uint32_t bs_buf_size;

    gdi_color_t *palette;
    uint32_t palette_size;
    uint8_t compression;
    int32_t width;
    int32_t height;
    int32_t src_x;
    int32_t src_y;
    int32_t run_length;
    int32_t run_length_used;
    int32_t run_length_odd;
    uint8_t code;
    bool is_raw_mode;
    bool is_from_file;
    gdi_imgdec_bmp_dithering_enum dither_mode;    
} gdi_imgdec_bmp_struct;


/****************************************************************************
* Function                                                               
*****************************************************************************/
extern void gdi_imgdec_bmp_init(gdi_imgdec_bmp_struct *dec, gdi_layer_handle_t out_layer, void *bs_buf, uint32_t bs_buf_size, bool *is_aborted, uint32_t flag);
extern void gdi_imgdec_bmp_deinit(gdi_imgdec_bmp_struct *dec);
extern gdi_result_t gdi_imgdec_bmp_draw_resized(
            gdi_imgdec_bmp_struct *dec,
            int32_t offset_x,
            int32_t offset_y,
            bool is_resized,
            int32_t resized_width,
            int32_t resized_height,
            uint8_t *BMP_src,
            uint32_t size,
            uint32_t aspect_flag);
extern gdi_result_t gdi_imgdec_bmp_get_dimension(uint8_t *src, uint32_t size, uint32_t *width, uint32_t *height);
extern gdi_result_t gdi_imgdec_bmp_draw_handler(gdi_layer_handle_t out_layer, int32_t x, int32_t y, uint32_t w, uint32_t h, uint8_t *data_ptr, uint32_t img_size, bool *is_aborted, int32_t aspect_flag);

#endif /* _GDI_IMGDEC_BMP_H_ */ 



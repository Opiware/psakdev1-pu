/* Copyright Statement:
 *
 */

#ifndef _GDI_IMAGE_BMP_H_
#define _GDI_IMAGE_BMP_H_

#include "gdi_datatype.h"
#include "gdi_const.h"


/****************************************************************************
* Function                                                               
*****************************************************************************/

extern gdi_result_t gdi_image_bmp_draw_handler(
                    int32_t x,
                    int32_t y,
                    int32_t w,
                    int32_t h,
                    uint8_t *data_ptr,
                    uint32_t img_size);
extern gdi_result_t gdi_image_bmp_get_dimension_handler(uint32_t flag, uint8_t *data_ptr, uint32_t img_size, uint32_t *width, uint32_t *height);

#define gdi_image_bmp_draw( offset_x,  offset_y, BMP_src,  size)  \
    gdi_image_bmp_draw_handler(0, 0, offset_x, offset_y, 0, 0, BMP_src, size)

#define gdi_image_bmp_draw_file( offset_x,  offset_y, filename) \
    gdi_image_bmp_draw_handler(GDI_IMAGE_CODEC_FLAG_IS_FILE, 0, offset_x, offset_y, 0, 0, filename,  0)

#define gdi_image_bmp_draw_resized( offset_x, offset_y, resized_width, resized_height, BMP_src, size) \
    gdi_image_bmp_draw_handler(0, 0, offset_x, offset_y, resized_width, resized_height, BMP_src,  size)

#define gdi_image_bmp_draw_resized_file( offset_x, offset_y, resized_width, resized_height, filename) \
    gdi_image_bmp_draw_handler(GDI_IMAGE_CODEC_FLAG_IS_FILE, 0, offset_x, offset_y, resized_width, resized_height, filename,  0)

#define gdi_image_bmp_get_dimension(BMP_src, width, height) \
    gdi_image_bmp_get_dimension_handler(0, BMP_src, 1, width, height)
#define gdi_image_bmp_get_dimension_file(filename, width, height) \
    gdi_image_bmp_get_dimension_handler(GDI_IMAGE_CODEC_FLAG_IS_FILE, filename, 0, width, height)


#define GDI_BMP_EXCEPTION_ESCAPE_MODE_END_OF_BITMAP     100
#endif /* _GDI_IMAGE_BMP_H_ */ 



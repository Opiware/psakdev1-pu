/* Copyright Statement:
 *
 */

#include "gdi_const.h"
#include "gdi_datatype.h"
#include "gdi_primitive.h"

#ifndef __GD_PRIMITIVE_ARM__
#define __GD_PRIMITIVE_ARM__

extern int GDI_GRAY16SET(int add_end, int add);

/* fast sw resizer */
//extern GDI_RESULT gdi_bitblt_resized_sw(gdi_handle src_layer_handle, int32_t sx1, int32_t sy1, int32_t sx2, int32_t sy2, int32_t dx1, int32_t dy1, int32_t dx2, int32_t dy2, BOOL is_high_quality);


extern gdi_color_t gdi_img_buf_convert_color(
    gdi_color_t from_color, 
    gdi_img_buf_color_format_enum to_format,
    gdi_img_buf_color_format_enum from_format);

extern void gdi_img_buf_fill_byte(
    gdi_img_buf_struct *dst_buf, 
    uint8_t dst_byte,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_fill_color_16(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t dst_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_fill_color_24(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t dst_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_fill_color_32(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t dst_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_color_16(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t pargb8888_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_color_24(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t pargb8888_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_color_PARGB8888(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t pargb8888_color,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_flatten_16_16(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t dst_color_key,
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_flatten_general(
    gdi_img_buf_struct *dst_buf, 
    gdi_color_t dst_color_key,
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_copy_same_format(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_copy_general(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_16_PARGB8888(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_24_PARGB8888(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_PARGB8888_PARGB8888(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_PARGB8888_to_PARGB6666(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_convert_PARGB8888_from_ARGB8888(
    gdi_img_buf_struct *buf, 
    int32_t width,
    int32_t height);

extern void gdi_img_buf_convert_ARGB8888_from_PARGB8888(
    gdi_img_buf_struct *buf, 
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_PARGB6666_to_PARGB6666(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

extern void gdi_img_buf_blending_PARGB6666_to_RGB565(
    gdi_img_buf_struct *dst_buf, 
    const gdi_img_buf_struct *src_buf,
    int32_t width,
    int32_t height);

#endif /* __GD_PRIMITIVE_ARM__ */


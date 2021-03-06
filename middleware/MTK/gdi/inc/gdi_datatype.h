/* Copyright Statement:
 *
 */
#ifndef _GDI_DATATYPE_H_
#define _GDI_DATATYPE_H_

#include "gdi.h"

typedef uint32_t gdi_layer_handle_t;     /**< Define the GDI layer handle type. */
typedef uint8_t  gdi_image_type_t;

typedef struct
{
    int32_t x;
    int32_t y;
} gdi_point_S32_struct;

 typedef struct _gdi_polygon_edge_struct
{
    int32_t Ymin;       /* min Y */
    int32_t Ymax;       /* max Y */
    int32_t Xint;       /* the round up value of real current x */
    int32_t Xfra;       /* the nuerator of fraction part of x, if Xfra==slope_y, actually that meas Xfra==0. */
    int32_t slope_x;    /* numerator of slope */
    int32_t slope_y;    /* denominator of slope */
    struct _gdi_polygon_edge_struct *next;
} gdi_polygon_edge_struct;

typedef struct
{
    gdi_image_type_t type;
    int32_t width;
    int32_t height;
} gdi_image_info_struct;

typedef gdi_color_t (*gd_color_from_rgb_func)(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
typedef void (*gd_color_to_rgb_func) (uint8_t *A, uint8_t *R, uint8_t *G, uint8_t *B, gdi_color_t c);

typedef gdi_color_t(*gd_get_pixel_func) (int x, int y);
typedef void (*gd_put_pixel_func) (int x, int y, gdi_color_t c);
typedef void (*gd_put_pixel_to_layer_func) (gdi_layer_handle_t layer_handle, int x, int y, gdi_color_t c);
typedef gdi_color_t(*gd_get_buf_pixel_func) (const uint8_t *buf_ptr, uint32_t buf_width, int x, int y);
typedef void (*gd_put_buf_pixel_func) (uint8_t *buf_ptr, uint32_t buf_width, int x, int y, gdi_color_t c);
typedef void (*gd_replace_src_key_func) (uint8_t *dest_ptr, int32_t dest_pitch, int32_t dest_offset_x, int32_t dest_offset_y,
                                         int32_t clipx1, int32_t clipy1, int32_t clipx2, int32_t clipy2, gdi_color_t src_key, int32_t width,
                                         int32_t height);
typedef void (*gd_bitblt_func) (uint8_t *dest, int32_t dw, int32_t dh, int32_t dx1, int32_t dy1, int32_t dx2, int32_t dy2, uint8_t *src, int32_t sw, int32_t sh, int32_t sx1, int32_t sy1, int32_t sx2, int32_t sy2, int32_t clipx1, int32_t clipy1, int32_t clipx2, int32_t clipy2,
                                gdi_color_t src_key, gdi_color_t layer_key);
typedef void (*gd_memset_func) (uint8_t *dest, uint32_t value, uint32_t len);
typedef void (*gd_fill_dot_rect_func)(uint8_t *dest,int32_t dw,int32_t dh,int32_t dx1,int32_t dy1,int32_t dx2,int32_t dy2,int32_t clipx1,int32_t clipy1,int32_t clipx2,int32_t clipy2,gdi_color_t c);
typedef void (*gd_image_bits_draw_func)(uint8_t *dest,int32_t dw, int32_t dh, int32_t dx1, int32_t dy1, int32_t dx2, int32_t dy2, uint8_t *src, int32_t sw,int32_t sh,int32_t sx1,int32_t sy1, int32_t sx2, int32_t sy2, int32_t src_size,int32_t bits_per_pixel,gdi_color_t palette[],int32_t clipx1, int32_t clipy1, int32_t clipx2, int32_t clipy2);


typedef enum
{
    GDI_MEM_TYPE_CACHEABLE,
    GDI_MEM_TYPE_FRAMEBUFFER,
    GDI_MEM_TYPE_END_OF_ENUM
} gdi_mem_type_enum;

typedef void* (*gdi_mem_allocate_func)(uint32_t size, gdi_mem_type_enum type, uint32_t alignment);
typedef bool (*gdi_mem_free_func)(void *mem);


#endif /* _GDI_DATATYPE_H_ */ 



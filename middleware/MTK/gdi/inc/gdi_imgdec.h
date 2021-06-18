/* Copyright Statement:
 *
 */

#ifndef __GDI_IMGDEC_H__
#define __GDI_IMGDEC_H__

/***************************************************************************** 
 * Include
 *****************************************************************************/
#include "gdi_const.h"
#include "gdi_datatype.h"
#include "gdi.h"

/***************************************************************************** 
 * Define
 *****************************************************************************/
/*
 * IMGDEC APIs */
typedef void (*gdi_imgdec_nb_done_callback_funcptr)(gdi_result_t result, gdi_layer_handle_t handle);

#define gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, img_ptr, img_type, img_size, src_type, frame_index) \
            gdi_imgdec_draw_internal( \
                output_layer, \
                GDI_NULL_HANDLE, \
                src_type, \
                img_ptr, \
                img_type, \
                img_size, \
                x, \
                y, \
                w, \
                h, \
                frame_index, \
                NULL, \
                0, \
                0)

#define gdi_imgdec_draw(output_layer, x, y, img_ptr) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, img_ptr, 0, 0, GDI_IMAGE_SRC_FROM_RESOURCE, 0)
#define gdi_imgdec_draw_resized(output_layer, x, y, w, h, img_ptr) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, img_ptr, 0, 0, GDI_IMAGE_SRC_FROM_RESOURCE, 0)
#define gdi_imgdec_draw_mem(output_layer, x, y, img_ptr, img_type, img_size) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, img_ptr, img_type, img_size, GDI_IMAGE_SRC_FROM_MEMORY, 0)
#define gdi_imgdec_draw_resized_mem(output_layer, x, y, w, h, img_ptr, img_type, img_size) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, img_ptr, img_type, img_size, GDI_IMAGE_SRC_FROM_MEMORY, 0)
#define gdi_imgdec_draw_file(output_layer, x, y, filename_ptr) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, filename_ptr, 0, 0, GDI_IMAGE_SRC_FROM_FILE, 0)
#define gdi_imgdec_draw_resized_file(output_layer, x, y, w, h, filename_ptr) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, filename_ptr, 0, 0, GDI_IMAGE_SRC_FROM_FILE, 0)

#define gdi_imgdec_draw_frames(output_layer, x, y, img_ptr, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, img_ptr, 0, 0, GDI_IMAGE_SRC_FROM_RESOURCE, frame_index)
#define gdi_imgdec_draw_resized_frames(output_layer, x, y, w, h, img_ptr, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, img_ptr, 0, 0, GDI_IMAGE_SRC_FROM_RESOURCE, frame_index)
#define gdi_imgdec_draw_mem_frames(output_layer, x, y, img_ptr, img_type, img_size, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, img_ptr, img_type, img_size, GDI_IMAGE_SRC_FROM_MEMORY, frame_index)
#define gdi_imgdec_draw_resized_mem_frames(output_layer, x, y, w, h, img_ptr, img_type, img_size, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, img_ptr, img_type, img_size, GDI_IMAGE_SRC_FROM_MEMORY, frame_index)
#define gdi_imgdec_draw_file_frames(output_layer, x, y, filename_ptr, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, 0, 0, filename_ptr, 0, 0, GDI_IMAGE_SRC_FROM_FILE, frame_index)
#define gdi_imgdec_draw_resized_file_frames(output_layer, x, y, w, h, filename_ptr, frame_index) gdi_imgdec_draw_resized_frames_internal(output_layer, x, y, w, h, filename_ptr, 0, 0, GDI_IMAGE_SRC_FROM_FILE, frame_index)

/***************************************************************************** 
 * Typedef
 *****************************************************************************/

/***************************************************************************** 
 * Global Function
 *****************************************************************************/
extern bool g_imgdec_timer_timeout_flag;
extern gdi_result_t gdi_imgdec_draw_internal(
            gdi_layer_handle_t output_layer,
            gdi_layer_handle_t source_layer,
            gdi_image_source_t src_type,
            uint8_t *img_src,
            uint8_t img_type,
            int32_t img_size,
            int32_t x,
            int32_t y,
            uint32_t resize_width,
            uint32_t resize_height,
            uint32_t frame_index,
            bool *is_aborted,
            uint32_t flag,
            uint32_t aspect_flag);

#endif /* __GDI_IMGDEC_H__ */



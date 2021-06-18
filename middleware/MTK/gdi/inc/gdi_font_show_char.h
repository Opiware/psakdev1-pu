/* Copyright Statement:
 *
 */

#ifndef __GDI_FONT_SHOW_CHAR_H__
#define __GDI_FONT_SHOW_CHAR_H__
#include "gdi_datatype.h"
#include "gdi.h"

extern const uint32_t gdi_tilt_table[61];
extern gdi_result_t gdi_show_char(
                int32_t x,
                int32_t y,
                gdi_color_t color,
                uint8_t *font_data,
                uint32_t font_data_size,
                uint16_t char_width,
                uint16_t char_height,
                uint8_t font_attr,
                bool is_gray_bitmap);
extern gdi_result_t gdi_show_char_bordered(
                int32_t x,
                int32_t y,
                gdi_color_t text_color,
                gdi_color_t border_color,
                uint8_t *font_data,
                uint32_t font_data_size,
                uint16_t char_width,
                uint16_t char_height,
                uint8_t font_attr,
                bool is_gray_bitmap);

extern void gdi_font_begin(void);
extern void gdi_font_end(void);
#endif


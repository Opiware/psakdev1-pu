/* Copyright Statement:
 *
 */

#ifndef _GDI_LCD_H_
#define _GDI_LCD_H_

#include "gdi_internal.h"
#include "gdi.h"

typedef struct
{
    /* active LCD */
    gdi_layer_handle_t act_handle;
    gdi_layer_handle_t act_layer_handle;
    gdi_layer_handle_t bind_handle;
    uint32_t act_width;
    uint32_t act_height;
    gdi_layer_handle_t blt_handle[GDI_LAYER_HW_LAYER_COUNT];
    uint32_t blt_counter;                  /* Venus use this counter to know whether their setting ever blt out or not. */
    gdi_color_format_t cf;
    bool is_freeze;
    bool is_high_priority_freeze;   /* this freeze flag can override is_freeze */
    gdi_lcd_type_enum lcd_type;

    /* validate update area. */
    int32_t blt_lock;
    gdi_rect_t blt_rect;       /* blt region */
    bool blt_rect_is_used;    /* blt_rect is validate */
    uint8_t rotate_value;
    bool rotate_by_layer;
} gdi_lcd_cntx_struct;

extern gdi_lcd_cntx_struct GDI_LCD_ARRAY[];

/****************************************************************************
* Function Declar                                                              
*****************************************************************************/
extern void gdi_lcd_init(void);

#endif /* _GDI_LCD_H_ */ 



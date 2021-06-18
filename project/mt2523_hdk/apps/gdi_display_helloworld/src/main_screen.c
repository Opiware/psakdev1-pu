/* Copyright Statement:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "gdi.h"
#include "gdi_font_engine.h"
#include "custom_resource_def.h"
#include "main_screen.h"

#include "memory_attribute.h"
#include "mt25x3_hdk_lcd.h"
#include "bsp_lcd.h"
#include "mt25x3_hdk_backlight.h"

#define DEFAULT_LCD_W 320
#define DEFAULT_LCD_H 320
 
static uint32_t LCD_WIDTH = 320;
static uint32_t LCD_HEIGHT = 320;

ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN unsigned char layer_buffer[DEFAULT_LCD_W*DEFAULT_LCD_H*2];


void main_screen_init(){ 
    bsp_lcd_init(0xF800);
    bsp_backlight_init();
    bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &LCD_WIDTH); // Get the LCD size.
    bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &LCD_HEIGHT);
    gdi_init(LCD_WIDTH, LCD_HEIGHT, GDI_COLOR_FORMAT_16, layer_buffer);  // Initialize the GDI buffer.
}

void common_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{

}

uint8_t* convert_string_to_wstring(uint8_t* string)
{
    static uint8_t wstring[50];
    int32_t index = 0;
    if (!string) {
        return NULL;
    }
    while (*string) {
        wstring[index] = *string;
        wstring[index + 1] = 0;
        string++;
        index+=2;
    }
    return wstring;
}

void main_screen_show(){
    gdi_font_engine_display_string_info_t param;
    
     // Set the font size and color.
    gdi_font_engine_color_t font_color = {0, 255, 255, 255};
    gdi_font_engine_set_font_size(GDI_FONT_ENGINE_FONT_MEDIUM);
    gdi_font_engine_set_text_color(font_color);

    // Set the screen background color.
    gdi_draw_filled_rectangle(0,0,LCD_WIDTH,LCD_HEIGHT,gdi_get_color_from_argb(0, 0, 0, 0));

    // Draw an image (source ID IMAGE_ID_BT_DISCONNECT_BMP) at position of (20, 140).
    gdi_image_draw_by_id(20,140,IMAGE_ID_BT_DISCONNECT_BMP);

    // Draw the string "Hello World!" at position of (100, 150).
    param.x = 100;
    param.y = 150;
    param.string = convert_string_to_wstring((uint8_t*) "Hello World!");
    param.length = strlen("Hello World!");
    param.baseline_height = -1;
    gdi_font_engine_display_string(&param);

    // Update the screen.
    gdi_lcd_update_screen(0, 0, LCD_WIDTH, LCD_HEIGHT);
}













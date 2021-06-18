/* Copyright Statement:
 *
 */

#include "hal_platform.h"

#ifndef __MT25X3_HDK_LCD_H__
#define __MT25X3_HDK_LCD_H__

#ifdef HAL_DISPLAY_LCD_MODULE_ENABLED
#include "bsp_lcd.h"

#ifdef __cplusplus
    extern "C" {
#endif

typedef enum {
    BSP_LCD_STATUS_ERROR = -1,
    BSP_LCD_STATUS_OK = 0
} bsp_lcd_status_t;

typedef void (*bsp_lcd_callback_t)(void *data);

bsp_lcd_status_t bsp_lcd_init(uint16_t bgcolor);
bsp_lcd_status_t bsp_lcd_set_layer_to_default(void);
bsp_lcd_status_t bsp_lcd_display_on(void);
bsp_lcd_status_t bsp_lcd_display_off(void);
bsp_lcd_status_t bsp_lcd_enter_idle(void);
bsp_lcd_status_t bsp_lcd_exit_idle(void);
bsp_lcd_status_t bsp_lcd_update_screen(uint32_t start_x,  uint32_t start_y, uint32_t end_x, uint32_t end_y);
bsp_lcd_status_t bsp_lcd_clear_screen(uint16_t color);
bsp_lcd_status_t bsp_lcd_clear_screen_bw(void);
bsp_lcd_status_t bsp_lcd_get_parameter(LCM_IOCTRL_ID_ENUM ID, void* parameters);
bsp_lcd_status_t bsp_lcd_config_roi(hal_display_lcd_roi_output_t *roi_para);
bsp_lcd_status_t bsp_lcd_config_layer(hal_display_lcd_layer_input_t *layer_data);
bsp_lcd_status_t bsp_lcd_set_index_color_table(uint32_t* index_table);
bsp_lcd_status_t bsp_lcd_register_callback(bsp_lcd_callback_t bsp_lcd_callback);
bsp_lcd_status_t bsp_lcd_power_on(void);
bsp_lcd_status_t bsp_lcd_power_off(void);
bsp_lcd_status_t bsp_lcd_lock(void);
bsp_lcd_status_t bsp_lcd_unlock(void);

#ifdef __cplusplus
}
#endif
#endif

#endif //__MT25X3_HDK_LCD_H__

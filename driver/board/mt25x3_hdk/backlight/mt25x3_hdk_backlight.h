/* Copyright Statement:
 *
 */

#include "hal_platform.h"

#ifndef __MT25X3_HDK_BACKLIGHT_H__
#define __MT25X3_HDK_BACKLIGHT_H__

#ifdef HAL_ISINK_MODULE_ENABLED
#include "hal_isink.h"
#endif
#ifdef HAL_DISPLAY_PWM_MODULE_ENABLED
#include "hal_display_pwm.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BSP_BACKLIGHT_STATUS_ERROR = -1,
    BSP_BACKLIGHT_STATUS_OK = 0
} bsp_backlight_status_t;

bsp_backlight_status_t bsp_backlight_enable(bool enable);
bsp_backlight_status_t bsp_backlight_init(void);
bsp_backlight_status_t bsp_backlight_deinit(void);

#ifdef HAL_ISINK_MODULE_ENABLED
bsp_backlight_status_t bsp_backlight_init_isink(hal_isink_channel_t channel, bool isDouble, hal_isink_current_t current);
bsp_backlight_status_t bsp_backlight_set_clock_source_isink(hal_isink_channel_t channel, hal_isink_clock_source_t source_clock);
bsp_backlight_status_t bsp_backlight_set_step_current_isink(hal_isink_channel_t channel, hal_isink_current_t current);
bsp_backlight_status_t bsp_backlight_set_double_current_isink(hal_isink_channel_t channel, hal_isink_current_t current);
#endif

#ifdef HAL_DISPLAY_PWM_MODULE_ENABLED
bsp_backlight_status_t bsp_backlight_init_display_pwm(void);
bsp_backlight_status_t bsp_backlight_set_clock_source_display_pwm(hal_display_pwm_clock_t source_clock);
bsp_backlight_status_t bsp_backlight_set_duty_display_pwm(uint8_t percent);
bsp_backlight_status_t bsp_backlight_set_width_display_pwm(uint32_t width);
#endif

bsp_backlight_status_t bsp_backlight_init_lcm_brightness(void);
bsp_backlight_status_t bsp_backlight_deinit_lcm_brightness(void);
bsp_backlight_status_t bsp_backlight_set_step_lcm_brightness(uint8_t level);

#ifdef MTK_EXTERNAL_PMIC
bsp_backlight_status_t bsp_backlight_init_external_isink(void);
bsp_backlight_status_t bsp_backlight_deinit_external_isink(void);
#endif

#ifdef __cplusplus
}
#endif

#endif //__MT25X3_HDK_BACKLIGHT_H__

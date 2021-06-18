/* Copyright Statement:
 *
 */

#include "hal_platform.h"

#ifdef HAL_DISPLAY_PWM_MODULE_ENABLED

#include "hal_display_pwm.h"
#include "hal_display_pwm_internal.h"
#include "hal_clock.h"
#include "hal_clock_internal.h"

#ifdef __cplusplus
extern "C" {
#endif


volatile DISP_PWM_REGISTER_T *disp_pwm_register_ptr = (DISP_PWM_REGISTER_T *)(DISP_PWM_BASE);

hal_display_pwm_status_t display_pwm_init(hal_display_pwm_clock_t clock)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    display_pwm_set_clock(clock);
    disp_pwm_register_ptr->DISP_PWM_CON_0_REGISTER.field.PWM_DONT_UPDATE = 0;
    disp_pwm_register_ptr->DISP_PWM_CON_0_REGISTER.field.PWM_UPDATE_SEL = 0;
    disp_pwm_register_ptr->DISP_PWM_CON_0_REGISTER.field.PWM_FRAME_SYNC = 0;
    disp_pwm_register_ptr->DISP_PWM_CON_0_REGISTER.field.PWM_AUTO_MODE = 0;
    disp_pwm_register_ptr->DISP_PWM_DEBUG_REGISTER.field.PWM_DOUBLE_BUFFER_DIS = 1;
    disp_pwm_register_ptr->DISP_PWM_EN_REGISTER.field.PWM_EN = 1;

    return ret;
}

hal_display_pwm_status_t display_pwm_deinit(void)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    disp_pwm_register_ptr->DISP_PWM_EN_REGISTER.field.PWM_EN = 0;

    return ret;
}

hal_display_pwm_status_t display_pwm_set_clock(hal_display_pwm_clock_t source_clock)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    if (source_clock == HAL_DISPLAY_PWM_CLOCK_104MHZ) {
        clock_mux_sel(DISP_PWM_MUX_SEL, 3);
    } else {
        clock_mux_sel(DISP_PWM_MUX_SEL, 1);
        clock_mux_sel(DISP_PWM_MUX_SEL, 0);
    }

    return ret;
}

hal_display_pwm_status_t display_pwm_set_duty(uint8_t percent)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    uint32_t value;
    value = 1024 * percent / 100;

    disp_pwm_register_ptr->DISP_PWM_CON_1_REGISTER.field.PWM_HIGH_WIDTH = value;
    disp_pwm_register_ptr->DISP_PWM_COMMIT_REGISTER.field.PWM_COMMIT = 1;
    disp_pwm_register_ptr->DISP_PWM_COMMIT_REGISTER.field.PWM_COMMIT = 0;

    return ret;
}

hal_display_pwm_status_t display_pwm_set_width(uint32_t width)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    disp_pwm_register_ptr->DISP_PWM_CON_1_REGISTER.field.PWM_HIGH_WIDTH = width;
    disp_pwm_register_ptr->DISP_PWM_COMMIT_REGISTER.field.PWM_COMMIT = 1;
    disp_pwm_register_ptr->DISP_PWM_COMMIT_REGISTER.field.PWM_COMMIT = 0;

    return ret;
}

#ifdef __cplusplus
}
#endif

#endif // HAL_DISPLAY_PWM_MODULE_ENABLED

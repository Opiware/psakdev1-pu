/* Copyright Statement:
 *
 */

#include "hal_platform.h"

#ifdef HAL_DISPLAY_PWM_MODULE_ENABLED

#include "hal_display_pwm.h"
#include "hal_display_pwm_internal.h"
#include "hal_clock.h"

#ifdef __cplusplus
extern "C" {
#endif

hal_display_pwm_status_t  hal_display_pwm_init(hal_display_pwm_clock_t clock)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;
    hal_clock_status_t clock_ret;

    clock_ret = hal_clock_enable(HAL_CLOCK_CG_DISP_PWM);

    if (HAL_CLOCK_STATUS_OK != clock_ret) {
        return HAL_DISPLAY_PWM_STATUS_ERROR;
    }

    ret = display_pwm_init(clock);

    return ret;
}

hal_display_pwm_status_t  hal_display_pwm_deinit(void)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;
    hal_clock_status_t clock_ret;

    clock_ret = hal_clock_disable(HAL_CLOCK_CG_DISP_PWM);

    if (HAL_CLOCK_STATUS_OK != clock_ret) {
        return HAL_DISPLAY_PWM_STATUS_ERROR;
    }

    ret = display_pwm_deinit();

    return ret;
}

hal_display_pwm_status_t hal_display_pwm_set_clock(hal_display_pwm_clock_t source_clock)
{

    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    if (source_clock >= HAL_DISPLAY_PWM_CLOCK_NUM) {
        return HAL_DISPLAY_PWM_STATUS_INVALID_PARAMETER;
    }

    ret = display_pwm_set_clock(source_clock);

    return ret;
}

hal_display_pwm_status_t hal_display_pwm_set_duty(uint8_t percentage)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    ret = display_pwm_set_duty(percentage);

    return ret;
}

hal_display_pwm_status_t hal_display_pwm_set_width(uint32_t width)
{
    hal_display_pwm_status_t ret = HAL_DISPLAY_PWM_STATUS_OK;

    if (width > 1024) {
        return HAL_DISPLAY_PWM_STATUS_INVALID_PARAMETER;
    }

    ret = display_pwm_set_width(width);

    return ret;
}
#ifdef __cplusplus
}
#endif

#endif

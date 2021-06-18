/* Copyright Statement:
 *
 */

#include "hal_audio_custom.h"

#if defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED)

extern afe_t afe;

void afe_switch_external_amp(bool on)
{
    hal_gpio_status_t ret;
    hal_pinmux_status_t ret_pinmux_status;
    extern const char BSP_SPEAKER_EBABLE_PIN;
    ret = hal_gpio_init((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN);
    if (ret != HAL_GPIO_STATUS_OK) {
        return;
    }
    ret_pinmux_status = hal_pinmux_set_function((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN, 0);
    if (ret_pinmux_status != HAL_PINMUX_STATUS_OK) {
        return;
    }
    ret = hal_gpio_set_direction((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN, HAL_GPIO_DIRECTION_OUTPUT);
    if (ret != HAL_GPIO_STATUS_OK) {
        return;
    }

    if (on && (!afe.ext_pa_on)) {
        ret = hal_gpio_set_output((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN, HAL_GPIO_DATA_HIGH);
        if (ret != HAL_GPIO_STATUS_OK) {
            return;
        }
        afe.ext_pa_on = true;
    } else {
        if (!afe.ext_pa_on) {
            return;
        }
        afe_volume_ramp_down();
        ret = hal_gpio_set_output((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN, HAL_GPIO_DATA_LOW);
        if (ret != HAL_GPIO_STATUS_OK) {
            return;
        }
        afe.ext_pa_on = false;
    }
    ret = hal_gpio_deinit((hal_gpio_pin_t)BSP_SPEAKER_EBABLE_PIN);
    if (ret != HAL_GPIO_STATUS_OK) {
        return;
    }
}

#endif  /* defined(HAL_I2S_MODULE_ENABLED) || defined(HAL_AUDIO_MODULE_ENABLED) */

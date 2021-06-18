/* Copyright Statement:
 *
 */

#ifdef MTK_LED_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_gpio.h"
#include "bsp_led.h"


const char __attribute__((weak)) BSP_LED0_PIN = 0xff;
const char __attribute__((weak)) BSP_LED1_PIN = 0xff;
const char __attribute__((weak)) BSP_LED2_PIN = 0xff;


/** initialzie selected LED **/
bsp_led_status_t bsp_led_init(uint32_t led_number)
{
    hal_gpio_status_t ret_gpio;
    hal_pinmux_status_t ret_pinmux;

    if (led_number >= BSP_LED_MAX) {
        return BSP_LED_INVALID_PARAMETER;
    }

	#ifdef BSP_LED_EPT_SUPPORT
	bsp_led_custom_init(led_number);
	#endif

    ret_gpio = hal_gpio_init(led_gpio_number[led_number]);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    ret_pinmux = hal_pinmux_set_function(led_gpio_number[led_number], PINMUX_GPIO_FUNCTION_INDEX);
    if (HAL_PINMUX_STATUS_OK != ret_pinmux) {
        return BSP_LED_ERROR;
    }

    ret_gpio = hal_gpio_set_direction(led_gpio_number[led_number], HAL_GPIO_DIRECTION_OUTPUT);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    ret_gpio = hal_gpio_set_output(led_gpio_number[led_number], BSP_LED_STATE_OFF);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    return BSP_LED_OK;
}


/** turn on the selected LED **/
bsp_led_status_t bsp_led_on(uint32_t led_number)
{
    hal_gpio_status_t ret_gpio;

    if (led_number >= BSP_LED_MAX) {
        return BSP_LED_INVALID_PARAMETER;
    }

    ret_gpio = hal_gpio_set_output(led_gpio_number[led_number], BSP_LED_STATE_ON);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    return BSP_LED_OK;
}


/** turn off the selected LED **/
bsp_led_status_t bsp_led_off(uint32_t led_number)
{
    hal_gpio_status_t ret_gpio;

    if (led_number >= BSP_LED_MAX) {
        return BSP_LED_INVALID_PARAMETER;
    }

    ret_gpio = hal_gpio_set_output(led_gpio_number[led_number], BSP_LED_STATE_OFF);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    return BSP_LED_OK;
}


/** toggle the selected LED **/
bsp_led_status_t bsp_led_toggle(uint32_t led_number)
{
    hal_gpio_status_t ret_gpio;

    if (led_number >= BSP_LED_MAX) {
        return BSP_LED_INVALID_PARAMETER;
    }

    ret_gpio = hal_gpio_toggle_pin(led_gpio_number[led_number]);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    return BSP_LED_OK;
}

/* Return the current state of a selected LED */
bsp_led_status_t bsp_led_get_state(uint32_t led_number, bsp_led_state_t *led_state)
{
    hal_gpio_status_t ret_gpio;
    hal_gpio_data_t gpio_data;

    if (led_number >= BSP_LED_MAX || NULL == led_state) {
        return BSP_LED_INVALID_PARAMETER;
    }

    ret_gpio = hal_gpio_get_output(led_gpio_number[led_number], &gpio_data);
    if (HAL_GPIO_STATUS_OK != ret_gpio) {
        return BSP_LED_ERROR;
    }

    if (HAL_GPIO_DATA_HIGH == gpio_data) {
        *led_state = BSP_LED_ON;
    }
    else {
        *led_state = BSP_LED_OFF;
    }

    return BSP_LED_OK;

}

#ifdef __cplusplus
}
#endif

#endif /*MTK_LED_ENABLE*/


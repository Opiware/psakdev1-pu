/* Copyright Statement:
 *
 */

#ifdef MTK_LED_ENABLE
#include "hal_gpio.h"
#include "bsp_led_internal.h"

hal_gpio_pin_t led_gpio_number[BSP_LED_MAX] = {HAL_GPIO_6, HAL_GPIO_31, HAL_GPIO_33, HAL_GPIO_34, HAL_GPIO_35};    /**< The data of this array means pin number corresponding to LED, it is decided by configuration of the board */

#endif /*MTK_LED_ENABLE*/


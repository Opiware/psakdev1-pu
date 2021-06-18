/* Copyright Statement:
 *
 */

#ifdef MTK_LED_ENABLE

#ifndef _BSP_LED_INTERNAL_H_
#define _BSP_LED_INTERNAL_H_

#include "hal_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_LED_MAX  5                                         /**< This value is decided by configuration of the board */
#define PINMUX_GPIO_FUNCTION_INDEX   8                         /**< This value is decided by configuration of the board */

#define BSP_LED_STATE_ON  HAL_GPIO_DATA_HIGH    
#define BSP_LED_STATE_OFF HAL_GPIO_DATA_LOW

extern hal_gpio_pin_t led_gpio_number[BSP_LED_MAX];

#ifdef __cplusplus
}
#endif

#endif /*_BSP_LED_INTERNAL_H_*/

#endif /*MTK_LED_ENABLE*/


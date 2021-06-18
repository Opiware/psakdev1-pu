/* Copyright Statement:
 *
 */

#ifdef MTK_LED_ENABLE

#include "hal_gpio.h"
#include "bsp_led_internal.h"
#include "hal_log.h"
#include "assert.h"

extern const char BSP_LED0_PIN;
extern const char BSP_LED1_PIN;
extern const char BSP_LED2_PIN;

hal_gpio_pin_t led_gpio_number[BSP_LED_MAX];            /**< The data of this array means pin number corresponding to LED, it is decided by configuration of the board */

void bsp_led_custom_init(uint32_t led_number)
{

    if ((BSP_LED0_PIN == 0xff) && (BSP_LED1_PIN == 0xff) && (BSP_LED1_PIN == 0xff)) {
        log_hal_info("[LED]led pin has not been configured by ept tool\r\n");
        assert(0);      
    }

    if (led_number == 0) {
        log_hal_info("[LED]BSP_LED0_PIN = %d init\r\n",BSP_LED0_PIN);
        led_gpio_number[0] = BSP_LED0_PIN;
    }

    if (led_number == 1) {
        log_hal_info("[LED]BSP_LED1_PIN = %d init\r\n",BSP_LED1_PIN);
        led_gpio_number[1] = BSP_LED1_PIN;
    }

    if (led_number == 2) {
        log_hal_info("[LED]BSP_LED2_PIN = %d init\r\n",BSP_LED2_PIN);
        led_gpio_number[2] = BSP_LED2_PIN;
    }
}

#endif /*MTK_LED_ENABLE*/



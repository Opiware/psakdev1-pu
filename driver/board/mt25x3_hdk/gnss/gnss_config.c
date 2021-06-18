/* Copyright Statement:
 *
 */

#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_eint.h"

extern char BSP_GNSS_POWER_PIN;
extern char BSP_GNSS_EINT;

hal_gpio_pin_t gnss_hrst;
hal_gpio_pin_t gnss_ldo_en = HAL_GPIO_10;
hal_gpio_clock_t gnss_32k_clock = HAL_GPIO_CLOCK_3;
hal_gpio_pin_t gnss_clock_pin = HAL_GPIO_13;
hal_eint_number_t gnss_eint = HAL_EINT_NUMBER_10;
hal_uart_port_t gnss_uart = HAL_UART_3;

void cust_gnss_gpio_config()
{
    gnss_ldo_en = (hal_gpio_pin_t) BSP_GNSS_POWER_PIN;
    gnss_eint = (hal_eint_number_t) BSP_GNSS_EINT;
}

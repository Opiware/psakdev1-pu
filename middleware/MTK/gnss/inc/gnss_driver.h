/* Copyright Statement:
 *
 */

#ifndef GNSS_UART_H
#define GNSS_UART_H

#if defined(_MSC_VER)
#include "maui_adapter.h"
#else
#include <stdint.h>
#endif
#include "hal_platform.h"
#include "hal_gpio.h"

typedef enum gnss_uart_callback_type_s {
    GNSS_UART_CALLBACK_TYPE_CAN_READ,
    GNSS_UART_CALLBACK_TYPE_CAN_WRITE,
    GNSS_UART_CALLBACK_TYPE_WAKEUP
} gnss_uart_callback_type_t;

typedef void (*gnss_driver_uart_callback)(gnss_uart_callback_type_t type);

extern uint8_t gnss_driver_init(gnss_driver_uart_callback callback_function);

extern int32_t gnss_driver_uart_read(uint8_t port, int8_t *buffer, int32_t length);

extern int32_t gnss_driver_uart_write(uint8_t port, int8_t *buffer, int32_t length);

extern void gnss_driver_uart_deinit(uint8_t port);

extern void gnss_driver_power_on(void);

extern void gnss_driver_power_off(void);

#ifdef __ICCARM__
__weak void gnss_driver_init_coclock(void);
__weak void gnss_driver_deinit_coclock(void);
#else
__attribute__((weak)) void gnss_driver_init_coclock(void);
__attribute__((weak)) void gnss_driver_deinit_coclock(void);
#endif

extern hal_gpio_pin_t gnss_hrst;
extern hal_gpio_pin_t gnss_ldo_en;
extern hal_gpio_clock_t gnss_32k_clock;
extern hal_gpio_pin_t gnss_clock_pin;
extern hal_eint_number_t gnss_eint;
extern hal_uart_port_t gnss_uart;
extern void cust_gnss_gpio_config(void);

#endif /*GNSS_UART_H*/


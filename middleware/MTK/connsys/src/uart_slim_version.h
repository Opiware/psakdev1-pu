/* Copyright Statement:
 *
 */

#ifndef __UART_SLIM_VERSION_H__
#define __UART_SLIM_VERSION_H__

#include <stdint.h>

/*slim version for uart logging*/

void uart_init_boot_phase(void);

void uart_deinit_boot_phase(void);

void uart_put_onechar_boot_phase(uint8_t c);

void uart_put_char_boot_phase(uint8_t *data, uint32_t size);

#endif /* __UART_SLIM_VERSION_H__ */


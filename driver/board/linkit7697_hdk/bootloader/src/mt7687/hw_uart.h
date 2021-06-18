/* Copyright Statement:
 *
 */

#ifndef __HW_UART_H__
#define __HW_UART_H__

/*
 * UART init. */
void hw_uart_init(void);

/*
 * print string to UART. */
void hw_uart_puts(const char *str);

/*
 * put a character to uart. */
void hw_uart_putc(char c);

/*
 * print string with args to UART */
void hw_uart_printf(char *fmt, ...);

/*
 * get a character from uart. */
int hw_uart_getc(void);

#endif /* __HW_UART_H__ */

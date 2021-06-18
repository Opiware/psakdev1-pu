/* Copyright Statement:
 *
 */

#ifndef __IO_DEF_H__
#define __IO_DEF_H__


#ifndef __GNUC__
#include <stdlib.h> /* for FILE */
#endif

#include "hal_uart.h"

#ifdef __cplusplus
extern "C" {
#endif


#if !defined(MTK_MAIN_CONSOLE_UART2_ENABLE)
#define CONSOLE_UART    HAL_UART_0
#else
#define CONSOLE_UART    HAL_UART_1
#endif


#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

#else

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE* stream)

#endif


/*****************************************************************************
 * API Functions
 *****************************************************************************/


/**
 * This is transient declaration before __io_getchar and __io_putchar were
 * implemented in project folders.
 *
 * @note deprecated. */
int __io_putchar(int ch);


/**
 * This is transient declaration before __io_getchar and __io_putchar were
 * implemented in project folders.
 *
 * @note deprecated. */
int __io_getchar(void);


void bsp_io_def_uart_init(void);


int bsp_io_def_uart_putchar(int ch);


int bsp_io_def_uart_getchar(void);


#if defined (__CC_ARM) || defined (__ICCARM__)
int fputc(int ch, FILE *f);
int fgetc(FILE* stream);
#endif


#ifdef __cplusplus
}
#endif

#endif /* __IO_DEF_H__ */


/* Copyright Statement:
 *
 */

/*
    Module Name:
    connsys_log.c

    Abstract:
    Provide CONNSYS module logging wrapping interface to unify the print mechanisms.

    Revision History:
    Who         When            What
    --------    ----------      ----------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "memory_attribute.h"

#include "uart_slim_version.h"

#include "connsys_log.h"


ATTR_ZIDATA_IN_TCM static uint8_t _g_connsys_util_uart_slim_disable;


int connsys_util_uart_slim_printf(const char *format, ...)
{
    int len;
    char buf[256];

    if (_g_connsys_util_uart_slim_disable)
        return 0;

    va_list ap;

    va_start(ap, format);

    len = vsprintf(buf, format, ap);

    uart_init_boot_phase();
    uart_put_char_boot_phase((uint8_t *)buf, len);
    uart_deinit_boot_phase();

    va_end(ap);

    return len;
}


int connsys_util_uart_slim_dump(
    const char      level,
    const char      *msg,
    const char      *p,
    size_t          s
    )
{
    size_t          len;
    size_t          i = 0;

    if (_g_connsys_util_uart_slim_disable)
        return 0;

    uart_init_boot_phase();

    len = strlen(msg);

    /* description */

    connsys_util_uart_slim_printf("  ");
    uart_put_char_boot_phase((uint8_t *)msg, len);
    uart_put_char_boot_phase((uint8_t *)"\n", 1);

    /* bytes */

    while (i < s) {
        if ((i % 16) == 0)
            connsys_util_uart_slim_printf("  %04x  ", i);
        connsys_util_uart_slim_printf("%02x%s",
                                        p[i] & 0xFF,
                                        i == s - 1  ? "\n" :
                                        !(~i & 15)  ? "\n" :
                                        !(~i &  7)  ? " - " : " ");
        i++;
        len++;
    }

    uart_deinit_boot_phase();

    return len;
}


void connsys_util_uart_slim_enable(
    uint8_t         enable
    )
{
    _g_connsys_util_uart_slim_disable = !enable;
}


uint8_t connsys_util_uart_slim_status(
    void
    )
{
    return !_g_connsys_util_uart_slim_disable;
}

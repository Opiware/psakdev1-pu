/* Copyright Statement:
 *
 */

/*
    Module Name:
    connsys_log.h

    Abstract:
    Provide CONNSYS module logging wrapping interface to unify the print mechanisms.

    Revision History:
    Who         When            What
    --------    ----------      ----------------------------------------------
*/

#ifndef __CONNSYS_LOG_H__
#define __CONNSYS_LOG_H__


#include <stdint.h>


#ifdef OVERRIDE_LOG
#define ERR(mod, format...)                                 \
    do {                                                    \
        if (connsys_util_uart_slim_status())                \
                connsys_util_uart_slim_printf("! " format); \
            else                                            \
                LOG_E(mod, format);                         \
        } while (0)
#else
#define ERR(mod, format...)                                 \
                LOG_E(mod, format);
#endif


#ifdef OVERRIDE_LOG
#define INFO(mod, format...)                                \
    do {                                                    \
        if (connsys_util_uart_slim_status())                \
                connsys_util_uart_slim_printf("  " format); \
            else                                            \
                LOG_I(mod, format);                         \
        } while (0)
#else
#define INFO(mod, format...)                                \
                LOG_I(mod, format);
#endif


#ifdef OVERRIDE_LOG
#define CONNSYS_D(mod, msg)                                 \
    do {                                                    \
        if (connsys_util_uart_slim_status())                \
                connsys_util_uart_slim_printf msg;          \
            else                                            \
                DBG_CONNSYS(mod, msg);                      \
        } while (0)
#else
#define CONNSYS_D(mod, msg)                                 \
                DBG_CONNSYS(mod, msg);
#endif


#ifdef OVERRIDE_LOG
#define CONNSYS_DUMP_E(mod, msg, p, s)                                      \
    do {                                                                    \
        if (connsys_util_uart_slim_status())                                \
                connsys_util_uart_slim_dump('E', msg, (const char *)p, s);  \
            else                                                            \
                LOG_HEXDUMP_E(mod, msg, p, s);                              \
        } while (0)
#else
#define CONNSYS_DUMP_E(mod, msg, p, s)                                      \
                LOG_HEXDUMP_E(mod, msg, p, s);
#endif


#ifdef OVERRIDE_LOG
#define CONNSYS_DUMP_I(mod, msg, p, s)                                      \
    do {                                                                    \
        if (connsys_util_uart_slim_status())                                \
                connsys_util_uart_slim_dump('I', msg, (const char *)p, s);  \
            else                                                            \
                LOG_HEXDUMP_I(mod, msg, p, s);                              \
        } while (0)
#else
#define CONNSYS_DUMP_I(mod, msg, p, s)                                      \
                LOG_HEXDUMP_I(mod, msg, p, s);
#endif


int connsys_util_uart_slim_printf(
    const char *format,
    ...
    );


int connsys_util_uart_slim_dump(
    const char      level,
    const char      *msg,
    const char      *p,
    size_t          s
    );


void connsys_util_uart_slim_enable(
    uint8_t         enable
    );


uint8_t connsys_util_uart_slim_status(
    void
    );


#endif /* __CONNSYS_LOG_H__ */

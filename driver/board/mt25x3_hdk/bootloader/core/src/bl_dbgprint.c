/* Copyright Statement:
 *
 */

#include "bl_common.h"
#include "bl_uart_sw.h"
#include <stdarg.h>
#include <stdint.h>

#if defined(BL_DEBUG)

#define __ADV_DBG_PRINT__

#define BL_MAX_CHARS     512
#define BL_MAX_FRACT     10000
#define BL_NUM_FRACT     4
#define BL_LEN           20

static char buf[BL_MAX_CHARS] = {0} ;


static bl_log_level_t debug_level ;

static void bl_itoa(char **buf, uint32_t i, uint32_t base)
{
    char *s;
    uint32_t rem;
    static char rev[BL_LEN + 1];

    rev[BL_LEN] = 0;
    if (i == 0) {
        (*buf)[0] = '0';
        ++(*buf);
        return;
    }
    s = &rev[BL_LEN];
    while (i) {
        i = BL_SLIM_UDIV_R(i, base, rem);
        if (rem < 10) {
            *--s = rem + '0';
        } else if (base == 16) {
            *--s = "abcdef"[rem - 10];
        }
    }
    while (*s) {
        (*buf)[0] = *s++;
        ++(*buf);
    }
}

static void bl_itof(char **buf, int32_t i)
{
    char *s;
    int32_t rem, j;
    static char rev[BL_LEN + 1];

    rev[BL_LEN] = 0;
    s = &rev[BL_LEN];
    for (j = 0 ; j < BL_NUM_FRACT ; j++) {
        i = BL_SLIM_UDIV_R(i, 10, rem);
        *--s = rem + '0';
    }
    while (*s) {
        (*buf)[0] = *s++;
        ++(*buf);
    }
}

void bl_print_internal(bl_log_level_t level, char *fmt, va_list ap)
{
    int32_t    ival;
    char    *p, *sval;
    char    *bp, cval;
    int64_t   dval;
    int32_t    fract;
#ifdef __ADV_DBG_PRINT__
    uint32_t    uival, uival1, uival2;
    char    *bp_old;
    int32_t    i, j;
#endif /* __ADV_DBG_PRINT__ */

    bp = buf;
    *bp = 0;

    if ((level) < debug_level) {
        return;
    }

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            *bp++ = *p;
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int32_t);
                if (ival < 0) {
                    *bp++ = '-';
                    ival = -ival;
                }
                bl_itoa (&bp, ival, 10);
                break;

            case 'o':
                ival = va_arg(ap, int32_t);
                if (ival < 0) {
                    *bp++ = '-';
                    ival = -ival;
                }
                *bp++ = '0';
                bl_itoa (&bp, ival, 8);
                break;

            case 'x':
                ival = va_arg(ap, int32_t);
                if (ival < 0) {
                    *bp++ = '-';
                    ival = -ival;
                }
                *bp++ = '0';
                *bp++ = 'x';
                bl_itoa (&bp, ival, 16);
                break;
#ifdef __ADV_DBG_PRINT__
            case 'u':
                uival= va_arg(ap, unsigned int);
                *bp++= '0';
                *bp++= 'x';
                bp_old = bp;
                uival1 = uival >> 16;
                uival2 = uival & 0x0000ffff;
                bl_itoa(&bp, uival1, 16);
                i = (unsigned int)bp - (unsigned int)bp_old;
                if (i < 4) {           
                    for (j = 3; j > (3 - i); j--) {
                        bp_old[j] = bp_old[j - (3 - i) - 1];
                    }          
                    for (j = 0; j <= (3 - i); j++)
                        bp_old[j] = '0';
                }
                bp = bp_old + 4;
                bp_old = bp;
                bl_itoa(&bp, uival2, 16);
                i = (unsigned int)bp - (unsigned int)bp_old;
                if (i < 4) {            
                    for (j = 3; j > (3 - i); j--) {
                        bp_old[j] = bp_old[j - (3 - i) - 1];
                    }            
                    for (j = 0; j <= (3 - i); j++)
                        bp_old[j] = '0';
                }
                bp = bp_old + 4;
                break;
#endif /* __ADV_DBG_PRINT__ */
            case 'p':
                ival = va_arg(ap, int32_t);
                *bp++ = '0';
                *bp++ = 'x';
                bl_itoa (&bp, ival, 16);
                break;

            case 'c':
                cval = va_arg(ap, int32_t);
                *bp++ = cval;
                break;

            case 'f':
                dval = va_arg(ap, int64_t);
                if (dval < 0) {
                    *bp++ = '-';
                    dval = -dval;
                }
                if (dval >= 1.0) {
                    bl_itoa (&bp, (int32_t)dval, 10);
                } else {
                    *bp++ = '0';
                }
                *bp++ = '.';
                fract = (int32_t)((dval - (int64_t)(int32_t)dval) * (int64_t)(BL_MAX_FRACT));
                bl_itof(&bp, fract);
                break;

            case 's':
                for (sval = va_arg(ap, char *) ; *sval ; sval++ ) {
                    *bp++ = *sval;
                }
                break;
        }
    }

    *bp = 0;

    for (bp = buf; *bp; bp++) {
        bl_uart_put_byte(*bp);
    }
}

void bl_print(bl_log_level_t level, char *fmt, ...)
{
    va_list     ap;
    va_start (ap, fmt);

    bl_print_internal(level, fmt, ap);

    va_end (ap);
}

void bl_set_debug_level(bl_log_level_t level)
{
    debug_level = level;
}

#else

void bl_print(bl_log_level_t level, char *fmt, ...)
{
}

void bl_set_debug_level(bl_log_level_t level)
{
}

#endif /* BL_DEBUG */

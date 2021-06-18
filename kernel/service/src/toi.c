/* Copyright Statement:
 *
 */

#include "toi.h"

#define is_0_to_1(_c)   (_c == '0' || _c == '1')
#define is_0(_c)        (_c == '0')
#define is_x(_c)        (_c == 'x' || _c == 'X')
#define is_b(_c)        (_c == 'b' || _c == 'B')
#define is_0_to_7(_c)   (_c >= '0' && _c <= '7')
#define is_0_to_9(_c)   (_c >= '0' && _c <= '9')
#define is_1_to_9(_c)   (_c >= '1' && _c <= '9')
#define is_a_to_f(_c)   (_c >= 'a' && _c <= 'f')
#define is_A_to_F(_c)   (_c >= 'A' && _c <= 'F')

#define dec_to_dec(_c)  (_c - '0')
#define hex_to_dec(_c)  (_c - 'a' + 10)
#define heX_to_dec(_c)  (_c - 'A' + 10)

/**
 * Detect integer type.
 *
 * @param b     input string buffer.
 * @param type  the detected type.
 *
 * @return      Pointer address. The address is not useful if type is error. */
static char *_toi_detect(char *b, uint8_t *type)
{
    *type = TOI_ERR;

    if (is_1_to_9( *b )) {
        *type = TOI_DEC;
    } else if (is_0( *b )) {
        b++;
        if (is_x( *b )) {
            b++;
            *type = TOI_HEX;
        } else if (is_b( *b )) {
            b++;
            *type = TOI_BIN;
        } else if (is_0_to_7( *b )) {
            *type = TOI_OCT;
        } else if (*b == 0) {
            *type = TOI_DEC; // a single '0'.
        }
    }

    return b;
}

uint32_t toi(char *b, uint8_t *type)
{
    uint32_t    v       = 0;

    b = _toi_detect(b, type);

    if (*type == TOI_ERR)
        return v;

    if (*type == TOI_BIN) {
        while (*b != 0) {
            if (!is_0_to_1( *b )) {
                *type = TOI_ERR; break;
            }
            v  = v << 1;
            v += *b - '0';
            b++;
        }
    }

    if (*type == TOI_OCT) {
        while (*b != 0) {
            if (!is_0_to_7( *b )) {
                *type = TOI_ERR; break;
            }
            v  = v << 3;
            v += *b - '0';
            b++;
        }
    }

    if (*type == TOI_DEC) {
        while (*b != 0) {
            if (!is_0_to_9( *b )) {
                *type = TOI_ERR; break;
            }
            v  = v * 10;
            v += *b - '0';
            b++;
        }
    }

    if (*type == TOI_HEX) {
        while (*b != 0) {
            v  = v << 4;
            if (is_0_to_9( *b )) {
                v += *b - '0';
            } else if (is_a_to_f( *b )) {
                v += *b - 'a' + 10;
            } else if (is_A_to_F( *b )) {
                v += *b - 'A' + 10;
            } else {
                *type = TOI_ERR; break;
            }
            b++;
        }
    }

    return (*type == TOI_ERR) ? 0 : (uint32_t)v;
}


uint8_t tov(char *b, uint32_t *value)
{
    uint8_t     type;

    *value = toi(b, &type);

    return type;
}


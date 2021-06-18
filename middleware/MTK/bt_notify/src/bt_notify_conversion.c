/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The string conversion for bt notify module.
 *
 ****************************************************************************/



#include "stdbool.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*****************************************************************************
 * define
 *****************************************************************************/


#define CAST_PU8_1(RAW)   ((uint8_t*)(RAW))
#define STR_SIZE_1(len) ((len)<<1)
#define STR_AT_1(RAW, n) ((void*)(CAST_PU8_1(RAW)+STR_SIZE_1(n)))

/*****************************************************************************
 * function
 *****************************************************************************/
static void SET_CHR_AT_1(uint8_t *RAW, int32_t n, uint16_t value)
{
    do {
        uint8_t *_p = STR_AT_1(RAW, n);
        uint16_t v = (uint16_t) (value);
        _p[0] = (uint8_t) (v & 0xff);
        _p[1] = (uint8_t) (v >> 8);
    } while (0);

}

static const uint8_t g_cheset_utf8_bytes_per[16] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 2, 2, 3, 4
};

static int32_t utf8_to_ucs2(uint8_t *dest, const uint8_t *utf8)
{
    uint8_t c = utf8[0];
    int count = g_cheset_utf8_bytes_per[c >> 4];
    uint16_t ucs2 = 0xFFFF;   /* invalid character */

    switch (count) {
        case 1:
            ucs2 = (uint16_t)c;
            break;
        case 2:
            if (utf8[1]) {
                ucs2 = ((uint16_t)(c & 0x1f) << 6) | (uint16_t)(utf8[1] ^ 0x80);
            }
            break;
        case 3:
            if (utf8[1] && utf8[2]) {
                ucs2 = ((uint16_t)(c & 0x0f) << 12)
                       | ((uint16_t)(utf8[1] ^ 0x80) << 6) | (uint16_t)(utf8[2] ^ 0x80);
            }
            break;
        case 4:
            break;
        default:
            count = 1;   /* the character cannot be converted, return 1 means always consume 1 byte */
            break;
    }

    SET_CHR_AT_1(dest, 0, ucs2);

    return count;
}

int32_t utf8_to_ucs2_string_ex(
    uint8_t *dest,
    int32_t dest_size,
    const uint8_t *src,
    uint32_t *src_end_pos)
{
    int pos = 0;
    int cnt;
    int src_len = strlen((const char *)src);

    dest_size -= (dest_size % 2);
    *src_end_pos = (uint32_t)src; /* set src_end_pos first */

    if (dest_size < 2) {
        return 0;
    }

    while (*src && pos < dest_size - 2) {
        cnt = utf8_to_ucs2(dest + pos, src);
        if (((uint32_t)src - (*src_end_pos)) >= (uint32_t)(src_len - cnt) &&
                (*(dest + pos) == 0xFF && *(dest + pos + 1) == 0xFF) &&
                !(*src == 0xEF && *(src + 1) == 0xBF && *(src + 2) == 0xBF)) {
            /*
             * If src isn't 0xEF, 0xBF, 0xBF and its remain length is not enough but dest is 0xFFFF, we will abort the process.
             * dest data is invalid character because src data is not enough to convert
             */
            break;
        }
        if (cnt == 0) {  /* abnormal case */
            break;
        } else {   /* normal case */
            src += cnt;
            pos += 2;
        }
    }
    *src_end_pos = (uint32_t)src;
    dest[pos] = 0;
    dest[pos + 1] = 0;
    return pos + 2;
}

int32_t utf8_to_ucs2_string(uint8_t *dest, int32_t dest_size, const uint8_t *src)
{
    uint32_t src_end_pos = (uint32_t) src;

    if (NULL == src || NULL == dest) {
        return 0;
    }
    return utf8_to_ucs2_string_ex(dest, dest_size, src, &src_end_pos);
}

uint16_t asc_to_ucs2(int8_t *pOutBuffer, int8_t *pInBuffer)
{
    int16_t count = -1;

    while (*pInBuffer != '\0') {
        pOutBuffer[++count] = *pInBuffer;
        pOutBuffer[++count] = 0;
        pInBuffer++;
    }

    pOutBuffer[++count] = '\0';
    pOutBuffer[++count] = '\0';
    return count + 1;
}
uint16_t asc_n_to_ucs2(int8_t *pOutBuffer, int8_t *pInBuffer, uint32_t len)
{
    uint16_t nLength;

    nLength = 0;
    if (NULL == pOutBuffer) {
        return 0;
    }

    for (nLength = 0; *pInBuffer; nLength++) {
        *pOutBuffer = *pInBuffer;
        pOutBuffer++;
        *pOutBuffer = 0;
        pOutBuffer++;

        pInBuffer++;
        if ((nLength * 2) >= (uint16_t)(len - 2)) {
            break;
        }
    }

    *pOutBuffer = 0;
    pOutBuffer++;
    *pOutBuffer = 0;
    pOutBuffer++;

    return nLength;
}


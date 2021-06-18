/* Copyright Statement:
 *
 */

#ifndef __TOI_H__
#define __TOI_H__

#include <stdint.h>

/**
 * @file: toi.h
 *
 * This file contains the APIs for converting strings to integers.
 */

#ifdef __cplusplus
extern "C" {
#endif

enum {
    TOI_BIN,
    TOI_OCT,
    TOI_DEC,
    TOI_HEX,
    TOI_ERR
};

/**
 * Convert octal, binary, hex, decimal integer strings into a variable and
 * returns it. The string type and failure is notified in parameter 
 * <i>type</i>.
 *
 * @param   b       input buffer.
 * @param   type    the detected string type of the input buffer.
 *
 * @return  the value of the string.
 */
uint32_t toi(char *b, uint8_t *type);


/**
 * Convert octal, binary, hex, decimal integer strings into a variable and
 * pass the result in pointer <i>value</i>. The string type or failure number
 * is notified by return value.
 *
 * @param   b       input buffer.
 * @param   value   the converted value.
 * @return  the string type or TOI_ERR if an error occurred.
 */
uint8_t tov(char *b, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* __TOI_H__ */


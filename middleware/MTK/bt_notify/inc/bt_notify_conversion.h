/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The header file of 'bt_notify_conversion.c'.
 *
 ****************************************************************************/


#ifndef __BT_NOTIFY_CONVERSION_H__
#define __BT_NOTIFY_CONVERSION_H__
#include "stdbool.h"
#include <stdint.h>
/*#define SHOW_UCS2 */ /*the default value is UTF8, if you want get ucs2 , you can open the macro. or add into project's makefile.*/

int32_t utf8_to_ucs2_string(uint8_t *dest, int32_t dest_size, const uint8_t *src);

uint16_t asc_n_to_ucs2(int8_t *pOutBuffer, int8_t *pInBuffer, uint32_t len);

uint16_t asc_to_ucs2(int8_t *pOutBuffer, int8_t *pInBuffer);

#endif/*__BT_NOTIFY_CONVERSION_H__*/


/* Copyright Statement:
 *
 */


#ifndef __GDI_FONT_RESOURCE_H__
#define __GDI_FONT_RESOURCE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define FONT_LOAD(x)  x


#define  MAX_FONT_TYPES      3

typedef struct Range {
    uint16_t nMin;
    uint16_t nMax;
} RangeData;

typedef struct RangeInfo {
    uint16_t nNoOfRanges;
    const RangeData *pRangeData;
} RangeDetails;

typedef struct _CustFontData {
    uint8_t nHeight;
    uint8_t nWidth;
    uint8_t nAscent;
    uint8_t nDescent;
    uint8_t nEquiDistant;
    uint8_t nCharBytes;
    uint16_t nMaxChars;
    uint8_t *pDWidthArray;
    uint8_t *pWidthArray;
    uint32_t *pOffsetArray;
    uint8_t *pDataArray;
    uint16_t *pRange;
    const RangeDetails *pRangeDetails;
    uint32_t language_flag;
} sCustFontData;

typedef struct {
    uint16_t nTotalFonts;
    const sCustFontData *const *fontData;
} font_group_struct;

#define MAX_FONT_SIZE MAX_FONT_TYPES

#ifdef __cplusplus
}
#endif

#endif /* __GDI_FONT_RESOURCE_H__ */



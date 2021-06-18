/* Copyright Statement:
 *
 */

#ifndef _GDI_IMGDEC_BMP_CODEC_H_
#define _GDI_IMGDEC_BMP_CODEC_H_

#include "gdi_imgdec_resizer.h"
#include "gdi_imgdec_bytestream.h"
#include "gdi_internal.h"
#include "gdi_image_bmp.h"
#include "gdi_imgdec_internal.h"
#include "gdi_const.h"
#include "gdi_datatype.h"
#include "gdi.h"
#include "gdi_primitive.h"
#include "gdi_features.h"
#include "gdi_layer.h"
#include "gd_include.h"

#include "gdi_imgdec_bmp.h"

typedef struct
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} bitmap_file_header;

typedef struct
{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bitmap_info_header;

typedef struct
{
    uint32_t biSize;
    uint16_t biWidth;
    uint16_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
} bitmap_core_header;

#define GDI_BI_RGB  0
#define GDI_BI_RLE8  1
#define GDI_BI_RLE4  2
#define GDI_BI_BITFIELDS  3
#define GDI_BMP_BYTESTREM_BUF_SIZE 4096

#undef GDI_RESIZER_PUT
#undef GDI_RESIZER_PUT_PIXEL
#undef GDI_RESIZER_INCREASE_DEST

#define GDI_IMGDEC_RESIZER_PUT(COLOR,WANT_DRAW)     gdi_imgdec_resizer_put(&dec->resizer, COLOR, WANT_DRAW)

#undef MY_GET_U8
#undef MY_FLUSH

#define SUPPORT_BMP_COMPRESSION



#endif

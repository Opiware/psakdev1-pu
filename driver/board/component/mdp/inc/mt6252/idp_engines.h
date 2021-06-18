/* Copyright Statement:
 *
 */

#ifndef __idp_engines_mt6252_h__
#define __idp_engines_mt6252_h__

#ifndef THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL
#error "Hay~! Man~! You can not include this file directly~!"
#endif

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

#include "mt6252/idp_hw/idp_resz_crz.h"
#include "mt6252/idp_hw/idp_imgdma_rotdma0.h"

extern idp_resz_crz_struct          crz_struct;
extern idp_imgdma_rotdma0_struct    rotdma0_struct;

extern void idp_hw_init(void);

#if defined(IDP_DRVPDN_SUPPORT)
extern void turn_off_idp_power(void);
#endif

#endif // #if defined(DRV_IDP_6252_SERIES)
#endif // #ifndef __idp_engines_mt6252_h__


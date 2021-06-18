/* Copyright Statement:
 *
 */

/**
 * \defgroup resizer Resizer
 * \ingroup idp
 * @{ */
#ifndef __idp_resz_mt6252_h__
#define __idp_resz_mt6252_h__

#ifndef THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL
#error "Hay~! Man~! You can not include this file directly~!"
#endif

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

//#define RESZ_H_RATIO_SHIFT_BITS  20
//#define RESZ_V_RATIO_SHIFT_BITS  20

extern void idp_resz_init(void);

#endif // #if defined(DRV_IDP_6252_SERIES)

#endif // #ifndef __idp_resz_mt6252_h__
/** @} */


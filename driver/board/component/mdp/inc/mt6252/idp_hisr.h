/* Copyright Statement:
 *
 */

#ifndef __idp_hisr_mt6252_h__
#define __idp_hisr_mt6252_h__

#ifndef THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL
#error "Hay~! Man~! You can not include this file directly~!"
#endif

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

#include <idp_core.h>

enum idp_hisr_cb_type
{
  IDP_HISR_CB_TYPE_IMGDMA,
  IDP_HISR_CB_TYPE_RESZ,
  IDP_HISR_CB_TYPE_IMGPROC
};
typedef enum idp_hisr_cb_type idp_hisr_cb_type;

typedef void *idp_hisr_handle_t;

extern idp_hisr_handle_t
idp_hisr_register(
    kal_uint32 const key,
    idp_hisr_cb_type const type,
    idp_hisr_intr_cb_t const cb,
    idp_hisr_intr_cb_param_t const param);

extern void
idp_hisr_activate(
    idp_hisr_handle_t const handle);

extern void
idp_hisr_clear_all(
    kal_uint32 const key,
    idp_hisr_cb_type const type);

extern void idp_hisr_imgdma(void);

extern void idp_hisr_resz(void);

//extern void idp_hisr_imgproc(void);

#endif // #if defined(DRV_IDP_6252_SERIES)
#endif // #ifndef __idp_hisr_mt6252_h__


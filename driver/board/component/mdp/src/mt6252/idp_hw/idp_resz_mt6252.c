/* Copyright Statement:
 *
 */

#define THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

#include <idp_core.h>
#include <mt6252/idp_hw/idp_resz.h>
#include <mt6252/idp_hw/idp_resz_crz.h>

void
idp_resz_init(void)
{
    idp_resz_crz_init();
}

#endif // #if defined(DRV_IDP_6252_SERIES)


/* Copyright Statement:
 *
 */

#define THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

#include "mt6252/idp_engines.h"

idp_resz_crz_struct         crz_struct;
idp_imgdma_rotdma0_struct    rotdma0_struct;

void
idp_hw_init(void)
{
    idp_imgdma_init();
    idp_resz_init();
}

// This function not ready! should use mm_power_ctrl
#if defined(IDP_DRVPDN_SUPPORT)
void
turn_off_idp_power(void)
{

}
#endif


kal_bool
idp_jpeg_encode_is_in_use(void)
{
    return KAL_TRUE;
}

kal_bool
idp_jpeg_resize_is_in_use(void)
{
    return KAL_TRUE;
}
#endif // #if defined(DRV_IDP_6252_SERIES)


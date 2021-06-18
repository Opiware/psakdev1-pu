/* Copyright Statement:
 *
 */

#include "hal_mpu.h"

#ifdef HAL_MPU_MODULE_ENABLED

#include "hal_mpu_internal.h"
#include "memory_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif


ATTR_RWDATA_IN_TCM MPU_CTRL_Type g_mpu_ctrl;
ATTR_RWDATA_IN_TCM MPU_REGION_EN_Type g_mpu_region_en;
ATTR_RWDATA_IN_TCM MPU_ENTRY_Type g_mpu_entry[HAL_MPU_REGION_MAX];

ATTR_TEXT_IN_TCM void mpu_status_save(void)
{

}

/* restores only regions that are enabled before entering into deepsleep */
ATTR_TEXT_IN_TCM void mpu_status_restore(void)
{
    MPU_REGION_EN_Type mpu_region_en;
    hal_mpu_region_t region;

    mpu_region_en = g_mpu_region_en;
    for (region = HAL_MPU_REGION_0; region < HAL_MPU_REGION_MAX; region ++) {
        if (mpu_region_en & 1) {
            /* If the region is enabled, restore the previous setting of the corresponding region*/
            MPU->RBAR = g_mpu_entry[region].mpu_rbar.w;
            MPU->RASR = g_mpu_entry[region].mpu_rasr.w;
        }
        mpu_region_en = mpu_region_en >> 1;
    }
    MPU->CTRL = g_mpu_ctrl.w;
}


#ifdef __cplusplus
}
#endif

#endif /* HAL_MPU_MODULE_ENABLED */


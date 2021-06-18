/* Copyright Statement:
 *
 */

#ifndef _EPT_GPIO_DRV_GENERAL_H
#define _EPT_GPIO_DRV_GENERAL_H

#if defined(MTK_CORD_FREE_HEADSET_ENABLE)
    #include "ept_gpio_drv_cordfree.h"
#elif defined(MTK_INEAR_NOODLES_HEADSET_ENABLE)
    #include "ept_gpio_drv_inear.h"
#else
    #include "ept_gpio_drv_hdk.h"
#endif

#endif /* _EPT_GPIO_DRV_GENERAL_H */

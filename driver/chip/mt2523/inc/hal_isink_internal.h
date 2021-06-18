/* Copyright Statement:
 *
 */

#ifndef __HAL_ISINK_INTERNAL_H__
#define __HAL_ISINK_INTERNAL_H__

#include "hal_pmu.h"

#ifdef HAL_ISINK_MODULE_ENABLED
#include "hal_mt2523_pmu_platform.h"

#ifdef __cplusplus
extern "C" {
#endif



#define PMU_ISINK_STATUS0_MASK 			         (0x1)
#define PMU_ISINK_STATUS0_SHIFT 			     (3)


#define PMU_ISINK_STATUS1_MASK 			         (0x1)
#define PMU_ISINK_STATUS1_SHIFT 			     (2)


#ifdef __cplusplus
}
#endif

#endif /*HAL_ISINK_MODULE_ENABLED*/

#endif /* __HAL_ISINK_INTERNAL_H__ */


/* Copyright Statement:
 *
 */

#ifndef __HAL_PMU_WRAP_INTERFACE_H__
#define __HAL_PMU_WRAP_INTERFACE_H__

#include "hal_platform.h"
#ifdef HAL_PMU_MODULE_ENABLED
#include "hal_pmu.h"
typedef enum {
    PMU_STATUS_INVALID_PARAMETER  = -1,     /**< pmu error invalid parameter */
    PMU_STATUS_ERROR              = 0,     /**< pmu undefined error */
    PMU_STATUS_SUCCESS            = 1       /**< pmu function ok */
} pmu_status_t;

typedef enum {
    PMU_STATUS_DISABLE            = 0,     /**< pmu undefined error */
    PMU_STATUS_ENABLE          = 1       /**< pmu function ok */
} pmu_control_status_t;

typedef enum{
    PMU_NORMAL=0,
    PMU_SLEEP,
    PMU_RETENTION,
    PMU_POWER_OFF
}hal_pmu_stage;

typedef enum{
    SLEEP_NORMAL=0,
    RETENTION_NORMAL
}hal_pmu_stage_flow;

typedef enum {
  PMU_FORCE_PFM       = 0,
  PMU_FORCE_PWM       = 1,
} pmu_force_mode_t;

typedef enum {
  PMU_VCORE_1p3V         = 0,
  PMU_VCORE_1p45v,
  PMU_VCORE_1p5v,
  PMU_VCORE_1p7v,
  PMU_VCORE_2p08v
} pmu_vcore_vosel_t;

typedef enum {
  PMU_CONTROL_OFF         = 0,
  PMU_CONTROL_ON,
} pmu_control_t;

typedef enum {
  PMU_RETENTION_LDO_OFF         = 0,
  PMU_RETENTION_LDO_ON,
} pmu_retention_status_t;

typedef struct{
    void (*init)(void);
    void (*init_power_mode)(void);
    void (*set_vcore_voltage)(hal_pmu_stage mode,pmu_vcore_vosel_t vol);
    void (*enter_sleep_mode)(void);
    void (*enter_retention_mode)(pmu_retention_status_t status);
    void (*resume_to_normal)(hal_pmu_stage_flow mode);
    void (*set_cldo_voltage)(int index);
    void (*set_mldo_voltage)(int adjust_value);
    void (*control_retention_lod)(pmu_control_t status);
    void (*sram_power_switch_control)(pmu_control_t status);
    void (*set_retention_ldo)(int adjust_value);
}hal_pmu_wrap_struct;
#endif /* HAL_PMU_MODULE_ENABLED */
#endif

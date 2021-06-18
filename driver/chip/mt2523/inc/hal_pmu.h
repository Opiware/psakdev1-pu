/* Copyright Statement:
 *
 */

#ifndef __HAL_PMU_H__
#define __HAL_PMU_H__
#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"
#include "hal_mt2523_pmu_platform.h"

#ifdef HAL_PMU_MODULE_ENABLED
#ifndef MTK_EXTERNAL_PMIC

typedef enum {
    PMU_NONE          = 0,                 /**< NONE Trigger */
    PMU_EDGE_RISING   = 1,                 /**< edge and rising trigger */
    PMU_EDGE_FALLING  = 2,                 /**< edge and falling trigger */
    PMU_EDGE_FALLING_AND_RISING = 3        /**< edge and falling or rising trigger */
} pmu_int_trigger_mode_t;

typedef enum {
    PMU_NOT_INIT = 0,
    PMU_INIT = 1
} pmu_int_driver_status_t;

typedef enum {
    PMU_INT_ALDO_OC         = 0,
    PMU_INT_ALDO_PG         = 1,
    PMU_INT_DLDO_OC         = 2,
    PMU_INT_DLDO_PG         = 3,
    PMU_INT_VC_BUCK_OC      = 4,
    PMU_INT_VCORE_PG        = 5,
    PMU_INT_VC_LDO_OC       = 6,
    PMU_INT_PKEYLP          = 7,
    PMU_INT_THM1            = 8,
    PMU_INT_THM2            = 9,
    PMU_INT_AXPKEY          = 10,
    PMU_INT_PWRKEY          = 11,
    PMU_INT_CHGOV           = 12,
    PMU_INT_CHRDET          = 13,
    PMU_INT_THR_H           = 14,
    PMU_INT_THR_L           = 15,
    PMU_INT_OVER110         = 16,
    PMU_INT_OVER40          = 17,
    PMU_INT_PSW_PG          = 18,
    PMU_INT_BAT_H           = 19,
    PMU_INT_BAT_L           = 20,
    PMU_INT_VBATON_HV_LV    = 21,
    PMU_INT_VBAT_UNDET_LV   = 22,
    PMU_INT_BVALID_DET_LV   = 23,
    PMU_INT_CHRWDT_LV       = 24,
    PMU_INT_HOT_LV          = 25,
    PMU_INT_WARM_LV         = 26,
    PMU_INT_COOL_LV         = 27,
    PMU_INT_COLD_LV         = 28,
    PMU_INT_IMP_LV          = 29,
    PMU_INT_NAG_C_LV        = 30,
    PMU_INT_AD_LBAT_LV      = 31,
    PMU_INT_MAX             = 32
} pmu_int_ch_t;


typedef enum {
    PMU_STATUS_ERROR_EINT_NUMBER  = -3,     /**< pmu error number */
    PMU_STATUS_INVALID_PARAMETER  = -2,     /**< pmu error invalid parameter */
    PMU_STATUS_ERROR              = -1,     /**< pmu undefined error */
    PMU_STATUS_SUCCESS            = 0       /**< pmu function ok */
} pmu_status_t;

typedef struct {
    void (*pmu_callback)(uint8_t trigger_source, void *user_data);
    void *user_data;
    uint8_t trigger_mode;
    bool init_status;
} pmu_function_t;

typedef void (*pmu_callback_t)(uint8_t trigger_source, void *user_data);

void pmu_init_mt6385(void);
bool pmu_set_register_value_mt6385(unsigned short int address, unsigned short int mask, unsigned short int shift, unsigned short int value);
unsigned char pmu_get_register_value_mt6385(unsigned short int address, unsigned short int mask, unsigned short int shift);

pmu_status_t pmu_register_callback(pmu_int_ch_t pmu_int_ch, pmu_int_trigger_mode_t trigger_mode, pmu_callback_t callback, void *user_data);
pmu_status_t pmu_disable_interrupt(pmu_int_ch_t int_ch, pmu_int_trigger_mode_t trigger_mode);
pmu_status_t pmu_enable_interrupt(pmu_int_ch_t int_ch, pmu_int_trigger_mode_t trigger_mode, unsigned char enable);
void pmu_init_power_mode(unsigned char power_mode_setting[10][8]);

#endif /* MTK_EXTERNAL_PMIC */
#endif /* HAL_PMU_MODULE_ENABLED */
#endif /* __HAL_PMU_H__ */

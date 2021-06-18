/* Copyright Statement:
 *
 */

#ifndef __HAL_PMU_AUXADC_H__
#define __HAL_PMU_AUXADC_H__
#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"
#include "hal_mt2523_pmu_platform.h"

#ifdef HAL_PMU_AUXADC_MODULE_ENABLED
#ifndef MTK_EXTERNAL_PMIC

typedef enum {
    PMU_AUX_BATSNS = 0,
    PMU_AUX_ISENSE,
    PMU_AUX_VCDT,
    PMU_AUX_BATON,
    PMU_AUX_CH4,
    PMU_AUX_ACCDET,
    PMU_AUX_CH6,
    PMU_AUX_TSX,
    PMU_AUX_CH8,
    PMU_AUX_CH9,
    PMU_AUX_CH10,
    PMU_AUX_CH11,
    PMU_AUX_CH12,
    PMU_AUX_WAKEUP_PCHR,
    PMU_AUX_MAX
} pmu_adc_channel_t;

void pmu_auxadc_init(void);
unsigned int pmu_auxadc_get_channel_value(pmu_adc_channel_t dwChannel, int deCount, int trimd);
int pmu_get_auxadc_temperature(void);
void pmu_get_efuse(unsigned char addr, unsigned char *lowbyte, unsigned char *highbyte);
unsigned char pmu_get_thermal_status(unsigned char mode, unsigned char data);

#endif /* MTK_EXTERNAL_PMIC */
#endif /* HAL_PMU_AUXADC_MODULE_ENABLED */
#endif /* __HAL_PMU_AUXADC_H__ */



/* Copyright Statement:
 *
 */

#ifndef __PMIC_MAX14745_H__
#define __PMIC_MAX14745_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"
#include "external_pmic_driver.h"

#define MAX14745_DEVICE_ID 	0x28//0x50
#define MAX14745_CHIP_ID	0x02
typedef enum {
    EXT_PMIC_MAXIM_BUCK1,
    EXT_PMIC_MAXIM_BUCK2,
    EXT_PMIC_MAXIM_LDO1,
    EXT_PMIC_MAXIM_LDO2,
    EXT_PMIC_MAXIM_LDO3
} external_pmic_maxim_vr_t;

typedef enum {
    EXT_PMIC_MAXIM_CHARGER_OFF_MODE = 0,
    EXT_PMIC_MAXIM_CHARGING_SUSPEND_MODE,
    EXT_PMIC_MAXIM_PRE_CHARGE_MODE,
    EXT_PMIC_MAXIM_FAST_CHARGE_CC_MODE,
    EXT_PMIC_MAXIM_FAST_CHARGE_CV_MODE,
    EXT_PMIC_MAXIM_MAINTAIN_CHARGE_MODE,
    EXT_PMIC_MAXIM_MAINTAIN_CHARGE_DONE_MODE,
    EXT_PMIC_MAXIM_CHARGER_FAULT_MODE
} external_pmic_maxim_status_of_charger_mode_t;

void pmic_init_maxim(void);
void pmic_charger_restore_setup(void);
unsigned char pmic_charger_get_charging_status(void);
unsigned char pmic_charger_get_charger_exist(void);
external_pmic_status_t pmic_ctrl_power_maxim(external_pmic_maxim_vr_t power_name, external_pmic_vr_ctl_t enable);
external_pmic_status_t pmic_vosel_config_maxim(external_pmic_maxim_vr_t power_name, external_pmic_voltage_t voltage);

#endif


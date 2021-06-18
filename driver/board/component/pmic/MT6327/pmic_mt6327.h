/* Copyright Statement:
 *
 */

#ifndef __PMIC_MT6237_H__
#define __PMIC_MT6237_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"
#include "external_pmic_driver.h"

#define MT6327_DEVICE_ID 	0x60//0xC0 0xC1
#define MT6327_CHIP_ID	0x27


typedef enum {
    EXT_PMIC_MT6327_VMD,
    EXT_PMIC_MT6327_VRF18,
    EXT_PMIC_MT6327_VTCXO,
    EXT_PMIC_MT6327_VA25,
    EXT_PMIC_MT6327_VM,
    EXT_PMIC_MT6327_VSIM1,
    EXT_PMIC_MT6327_VIO18,
    EXT_PMIC_MT6327_VMC
} external_pmic_mt6327_vr_t;

typedef enum {
    EXT_PMIC_MAXIM_CHARGER_OFF_MODE = 0,
    EXT_PMIC_MAXIM_CHARGING_SUSPEND_MODE,
    EXT_PMIC_MAXIM_PRE_CHARGE_MODE,
    EXT_PMIC_MAXIM_FAST_CHARGE_CC_MODE,
    EXT_PMIC_MAXIM_FAST_CHARGE_CV_MODE,
    EXT_PMIC_MAXIM_MAINTAIN_CHARGE_MODE,
    EXT_PMIC_MAXIM_MAINTAIN_CHARGE_DONE_MODE,
    EXT_PMIC_MAXIM_CHARGER_FAULT_MODE
} external_pmic_mt6327_status_of_charger_mode_t;

void pmic_init_mt6327(void);
void pmic_charger_restore_setup(void);
unsigned char pmic_charger_get_charging_status(void);
unsigned char pmic_charger_get_charger_exist(void);
external_pmic_status_t pmic_ctrl_power_mt6327(external_pmic_mt6327_vr_t power_name, external_pmic_vr_ctl_t enable);
external_pmic_status_t pmic_vosel_config_mt6327(external_pmic_mt6327_vr_t power_name, external_pmic_voltage_t voltage);

#endif


/* Copyright Statement:
 *
 */

#ifndef __EXTERNAL_PMIC_PORT_H__
#define __EXTERNAL_PMIC_PORT_H__

#include "external_pmic_driver.h"
#include "hal_pmu_wrap_interface.h"

void external_pmic_init(void);
void external_pmic_ctrl_power(unsigned char driver_name, unsigned char enable);
external_pmic_status_t external_pmic_vosel_config(platform_device_t driver_name, external_pmic_voltage_t voltage);
void external_pmic_eint_init(void);
void external_pmic_eint_handler(void *parameter);
unsigned char external_pmic_set_vcore_voltage(unsigned char lock, unsigned char vcore_vosel);
unsigned char external_pmic_get_vcore_voltage(void);
void external_pmic_audio_lock_voltage(void);
void external_pmic_audio_unlock_voltage(void);
unsigned char external_pmic_get_usb_input_status(void);
void external_pmic_enter_power_off(void);
void external_pmic_reset(void);

#endif

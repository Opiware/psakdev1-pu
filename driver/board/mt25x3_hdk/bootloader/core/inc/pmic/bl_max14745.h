/* Copyright Statement:
 *
 */

#ifndef BL_MAX14745_H_
#define BL_MAX14745_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bl_pmic.h"

#define BL_PMIC_I2C_ADDR_max14745 	0x28//0x50
#define BL_PMIC_MAX14745_CHIP_ID	0x02

unsigned int bl_max14745_init(void);
void bl_max14745_vcore_set_1p3v(void);
void bl_max14745_vusb_vr_control(unsigned char enable);
void bl_max14745_vmc_vr_control(unsigned char enable);

#ifdef __cplusplus
}
#endif

#endif /* BL_MAX14745_H_ */

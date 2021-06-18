/* Copyright Statement:
 *
 */

#ifndef BL_MT6327_H_
#define BL_MT6327_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bl_pmic.h"

#define BL_PMIC_I2C_ADDR_MT6327 	(0x60)// 0xc0   0xc1

#define MT6327_CID0             	((0x00))
#define MT6327_VMD_CON5             ((0x55))


unsigned int bl_mt6327_init(void);
void bl_mt6327_vcore_set_1p3v(void);
void bl_mt6327_vusb_vr_control(unsigned char enable);
void bl_mt6327_vmc_vr_control(unsigned char enable);
#ifdef __cplusplus
}
#endif

#endif /* BL_MT6385_H_ */

/* Copyright Statement:
 *
 */

#ifndef BL_MT6385_H_
#define BL_MT6385_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bl_pmic.h"

#define BL_PMIC_I2C_ADDR_MT6385 	(0x6B)

#define MT6385_PPCCTL0             	((0x004B))
#define MT6385_PSICKEY0             ((0x003E))
#define MT6385_PSICKEY1             ((0x003F))
#define MT6385_PSICTL               ((0x0040))
#define MT6385_VCBUCKPSI0           ((0x013E))
#define MT6385_VCBUCKPSI1           ((0x013F))
#define MT6385_VCLDOPSI0            ((0x0103))
#define MT6385_VCLDOPSI2            ((0x0105))
#define MT6385_VUSBCTL0             ((0x00ED))
#define MT6385_VMCCTL0              ((0x00EC))

unsigned int bl_mt6385_init(void);
void bl_mt6385_vcore_set_1p3v(void);
void bl_mt6385_vusb_vr_control(unsigned char enable);
void bl_mt6385_vmc_vr_control(unsigned char enable);

#ifdef __cplusplus
}
#endif

#endif /* BL_MT6385_H_ */

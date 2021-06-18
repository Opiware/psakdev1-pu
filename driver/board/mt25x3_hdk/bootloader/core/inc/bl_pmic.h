/* Copyright Statement:
 *
 */

#ifndef BL_PMIC_H_
#define BL_PMIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_platform.h"
#include "hal_i2c_pmic.h"

#include "bl_mt6385.h" 
#include "bl_max14745.h" 
#ifdef MTK_EXTERNAL_PMIC_TYPE_MT6327
#include "bl_mt6327.h" 
#endif


extern void (*bl_pmic_vusb_vr_control)(unsigned char enable);
extern void (*bl_pmic_vmc_vr_control)(unsigned char enable);

void bl_pmic_init(void);
bool bl_pmic_set_register_value(uint8_t i2c_address, uint8_t reg_addr_len, uint16_t reg_addr, uint8_t mask, uint8_t shift, uint8_t value);
unsigned char bl_pmic_get_register_value(uint8_t i2c_address, uint8_t reg_addr_len, uint16_t reg_addr, uint8_t mask, uint8_t shift);
/*internal use*/
unsigned char bl_pmic_i2c_read(unsigned char i2c_address, unsigned char reg_addr_len, unsigned char *ptr_send, unsigned char *ptr_read);
unsigned char bl_pmic_i2c_write(unsigned char i2c_address, unsigned char reg_addr_len, unsigned char *ptr_send);
void bl_null_vusb_vr_control(unsigned char enable);

#ifdef __cplusplus
}
#endif

#endif /* BL_PMIC_H_ */

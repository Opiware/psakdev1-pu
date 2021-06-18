/* Copyright Statement:
 *
 */

#ifndef __VSM_I2C_OPERATION_H_
#define __VSM_I2C_OPERATION_H_
#include <stdint.h>
#include "bma2x2.h"

#ifdef __cplusplus
extern "C" {
#endif

s8 BMA2x2_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
s8 BMA2x2_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
s8 I2C_routine(void);


#ifdef __cplusplus
extern }
#endif

#endif /* __VSM_I2C_OPERATION_H_ */

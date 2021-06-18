/* Copyright Statement:
 *
 */

#ifndef __VSM_I2C_OPERATION_H_
#define __VSM_I2C_OPERATION_H_
#include <stdint.h>
#include "hal_i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

void i2c_init(hal_i2c_port_t i2c_port, hal_i2c_frequency_t i2c_freq);

int32_t vsm_i2c_write(uint8_t slave_addr, uint8_t *data, uint16_t len);

vsm_status_t vsm_i2c_write_read(uint8_t slave_addr, uint8_t reg, uint8_t *data, uint16_t len);


#ifdef __cplusplus
extern }
#endif

#endif /* __VSM_I2C_OPERATION_H_ */


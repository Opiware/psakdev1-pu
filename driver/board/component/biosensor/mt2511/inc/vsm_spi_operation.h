/* Copyright Statement:
 *
 */

#ifndef __VSM_I2C_OPERATION_H_
#define __VSM_I2C_OPERATION_H_
#include <stdint.h>
#include "hal_spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

void vsm_spi_init(hal_spi_master_port_t spi_port, uint32_t spi_macro);

int32_t vsm_spi_write(uint8_t addr, uint8_t reg, uint8_t *data, uint32_t size);

int32_t vsm_spi_write_read(uint8_t addr, uint8_t reg, uint8_t *data, uint32_t size);

int32_t vsm_spi_write_read_retry(uint8_t addr, uint8_t reg, uint8_t *data, uint32_t size);

void vsm_spi_speed_modify(int32_t speed);
#ifdef __cplusplus
extern }
#endif

#endif /* __VSM_I2C_OPERATION_H_ */


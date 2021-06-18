/* Copyright Statement:
 *
 */

#ifndef __MEMS_BUS__
#define __MEMS_BUS__

#include "hal_i2c_master.h"
#include "hal_spi_master.h"

void mems_i2c_init(hal_i2c_port_t i2c_port, hal_i2c_frequency_t i2c_freq);

int32_t mems_i2c_write(uint8_t slave_addr, uint8_t *data, uint16_t len);
int32_t mems_i2c_read(uint8_t slave_addr, uint8_t *data, uint16_t len);
int32_t mems_i2c_write_read(uint8_t slave_addr, uint8_t reg, uint8_t *data, uint16_t len);
int32_t mems_i2c_write_read_dma(uint8_t slave_addr, uint8_t reg, uint8_t *data, uint16_t len);

#define SPI_SELECT_BMI160 (0U)
void mems_spi_init(uint32_t select, hal_spi_master_port_t spi_port, hal_spi_master_config_t *spi_cfg, hal_spi_master_macro_select_t spi_macro);
int32_t mems_spi_write(uint32_t select, uint8_t *data, uint32_t size);
int32_t mems_spi_write_read(uint32_t select, uint8_t addr, uint8_t *data, uint32_t size);

#endif /*__MEMS_BUS__*/

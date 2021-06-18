/* Copyright Statement:
 *
 */

#ifndef _CTP_I2C_H_
#define _CTP_I2C_H_

#ifdef MTK_CTP_ENABLE

#include <stdint.h>
#include <stdbool.h>
#include "hal_i2c_master.h"
#include "hal_gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    CTP_USE_HARDWARE_I2C = 0,
    CTP_USE_SOFTWARE_I2C,
} ctp_i2c_type_t;


typedef struct {
    bool 		   		has_initialized;
    hal_i2c_frequency_t speed;
    ctp_i2c_type_t 		i2c_type;
    hal_i2c_port_t		i2c_port;
    hal_gpio_pin_t		sda_pin;
    hal_gpio_pin_t 		scl_pin;
} ctp_i2c_config_t;

/********* varible extern *************/
extern ctp_i2c_config_t *ctp_i2c_state;

/******** funtion extern **************/
bool ctp_hw_i2c_init(ctp_i2c_config_t *i2c_config);
bool ctp_hw_i2c_deinit(void);
bool ctp_i2c_bottom_write(uint8_t device_addr, uint16_t ctp_reg_addr, uint8_t *data_buffer, uint32_t data_length);
bool ctp_i2c_bottom_read(uint8_t device_addr, uint16_t ctp_reg_addr, uint8_t *data_buffer, uint32_t data_length);
bool ctp_sw_i2c_read(uint8_t slave_adress, uint16_t reg_address, uint8_t *data, uint32_t length);
bool ctp_sw_i2c_write(uint8_t slave_adress, uint16_t reg_address, uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /*MTK_CTP_ENABLE*/

#endif /*_CTP_I2C_H_*/


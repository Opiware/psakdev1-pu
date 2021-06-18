/* Copyright Statement:
 *
 */

#ifndef __MAX17048_DRIVER_H__
#define __MAX17048_DRIVER_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"

void max17048_i2c_init(void);
bool max17048_read_word(unsigned char i2c_address, unsigned char address, unsigned char *msb, unsigned char *lsb);
bool max17048_write_word(unsigned char i2c_address, unsigned char address, unsigned char msb, unsigned char lsb);
bool max17048_set_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift, unsigned char value);
unsigned char max17048_get_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift);

#endif

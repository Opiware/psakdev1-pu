/* Copyright Statement:
 *
 */

/*
 * Definitions for ICM-30630 sensor chip. */
#ifndef __ICM30630_H__
#define __ICM30630_H__

#include "stdint.h"

/*ICM-30630 ps sensor register related macro*/
#define ICM30630_REG_CHIP_ID        (0x0)

#define ICM30630_I2C_ADDRESS         (0x6A)

/*----------------------------------------------------------------------------*/
void icm30630_eint_set(uint32_t eint_num);
void icm30630_eint_handler(void *parameter);
int32_t icm30630_operate(void *self, uint32_t command, void *buff_out, int32_t size_out, int32_t *actualout,
                   void *buff_in, int32_t size_in);
void icm30630_init(void);
uint32_t icm_30630_get_step_count(void);
void icm_30630_enable_step_count(uint32_t enable);

#endif


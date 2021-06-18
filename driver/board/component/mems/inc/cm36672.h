/* Copyright Statement:
 *
 */

/*
 * Definitions for CM36672 proximity sensor chip. */
#ifndef __CM36672_H__
#define __CM36672_H__

#include "stdint.h"

/*cm36672 ps sensor register related macro*/
#define CM36672_REG_PS_CONF1_2		0X03
#define CM36672_REG_PS_CONF3_MS		0X04
#define CM36672_REG_PS_CANC			0X05
#define CM36672_REG_PS_LOW_THD  	0X06
#define CM36672_REG_PS_HIGH_THD  	0X07
#define CM36672_REG_PS_DATA			0X08
#define CM36672_REG_INT_FLAG		0X0B
#define CM36672_REG_ID_MODE			0X0C

#define CM36672_I2C_ADDRESS         0x60

/*----------------------------------------------------------------------------*/
void cm36672_eint_set(uint32_t eint_num);

void cm36672_eint_handler(void *parameter);
void ps_init(void);

#endif


/* Copyright Statement:
 *
 */

#ifndef __EXTERNAL_PMIC_DRIVER_H__
#define __EXTERNAL_PMIC_DRIVER_H__

#include <stdio.h>
#include <stdlib.h>
#include "hal_platform.h"

typedef enum {
    EXT_PMIC_STATUS_INVALID_PARAMETER  = -2, 		/**< PMIC error invalid parameter */
    EXT_PMIC_STATUS_ERROR              = -1,     	/**< PMIC undefined error */
    EXT_PMIC_STATUS_SUCCESS            = 0       	/**< PMIC function ok */
} external_pmic_status_t;

typedef enum {
    EXT_PMIC_VR_DISABLE   = 0,
    EXT_PMIC_VR_ENABLE    = 1
} external_pmic_vr_ctl_t;

typedef enum {
    EXT_PMIC_VCORE_UNLOCK = 0,
    EXT_PMIC_VCORE_LOCK = 1
} external_pmic_vcore_lock_ctrl_t;

typedef enum {
    EXT_PMIC_VOL_0P7V = 0,
    EXT_PMIC_VOL_0P8V = 1,
    EXT_PMIC_VOL_0P9V = 2,
    EXT_PMIC_VOL_1P0V = 3,
    EXT_PMIC_VOL_1P1V = 4,
    EXT_PMIC_VOL_1P2V = 5,
    EXT_PMIC_VOL_1P3V = 6,
    EXT_PMIC_VOL_1P4V = 7,
    EXT_PMIC_VOL_1P5V = 8,
    EXT_PMIC_VOL_1P6V = 9,
    EXT_PMIC_VOL_1P7V = 10,
    EXT_PMIC_VOL_1P8V = 11,
    EXT_PMIC_VOL_1P9V = 12,
    EXT_PMIC_VOL_2P0V = 13,
    EXT_PMIC_VOL_2P1V = 14,
    EXT_PMIC_VOL_2P2V = 15,
    EXT_PMIC_VOL_2P3V = 16,
    EXT_PMIC_VOL_2P4V = 17,
    EXT_PMIC_VOL_2P5V = 18,
    EXT_PMIC_VOL_2P6V = 19,
    EXT_PMIC_VOL_2P7V = 20,
    EXT_PMIC_VOL_2P8V = 21,
    EXT_PMIC_VOL_2P9V = 22,
    EXT_PMIC_VOL_3P0V = 23,
    EXT_PMIC_VOL_3P1V = 24,
    EXT_PMIC_VOL_3P2V = 25,
    EXT_PMIC_VOL_3P3V = 26,
    EXT_PMIC_VOL_3P4V = 27,
    EXT_PMIC_VOL_ERROR = 255
} external_pmic_voltage_t;

void external_pmic_i2c_init(void);
bool external_pmic_set_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift, unsigned char value);
unsigned char external_pmic_get_register_value(unsigned char i2c_address, unsigned char address, unsigned char mask, unsigned char shift);

#endif

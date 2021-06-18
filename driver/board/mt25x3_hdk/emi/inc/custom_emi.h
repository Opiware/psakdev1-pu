/* Copyright Statement:
 *
 */

#ifndef __CUSTOM_EMI__
#define __CUSTOM_EMI__

#include "emi_init.h"

EMI_SETTINGS emi_settings[] = {
    {
        0x00000010,	/*EMI_GENA_VAL*/
        0x00000000,	/*EMI_RDCT_VAL*/
        0x00004000,	/*EMI_DSRAM_VAL*/
        0xA0261000,	/*EMI_MSRAM_VAL*/
        0x00000000,	/*EMI_IDL_C_VAL*/
        0x00000000,	/*EMI_IDL_D_VAL*/
        0x00000000,	/*EMI_IDL_E_VAL*/
        0x00000000,	/*EMI_ODL_C_VAL*/
        0x00000000,	/*EMI_ODL_D_VAL*/
        0x00000000,	/*EMI_ODL_E_VAL*/
        0x00000000,	/*EMI_ODL_F_VAL*/
        0x00020002,	/*EMI_IO_A_VAL*/
        0x00020002,	/*EMI_IO_B_VAL*/

    } ,
};

#endif

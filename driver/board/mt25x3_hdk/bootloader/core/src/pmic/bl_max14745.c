/* Copyright Statement:
 *
 */

#include "bl_pmic.h"
#include "bl_max14745.h" 

unsigned int bl_max14745_init(void)
{
	unsigned char chip_id;
	/*Find pmic chip id*/	
	chip_id = bl_pmic_get_register_value(BL_PMIC_I2C_ADDR_max14745,1,0,0xFF,0); 
	
	if(chip_id == BL_PMIC_MAX14745_CHIP_ID)
	{		
		/* Set Vcore Voltage to 1.3V*/
		bl_max14745_vcore_set_1p3v();
		return (0);
	}	
	else{
		return (1);
	}
}

void bl_max14745_vcore_set_1p3v(void)
{   
	/* Set maax14745 buck1 to 1.3V */
	/* Linear Scale from 0.8V to 2.375V in 25mV increments */   
	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_max14745	,1	,0x0E 	,0x3F   ,0  ,20);
}

void bl_max14745_vusb_vr_control(unsigned char enable)
{
	/* VUSB use max14745 LDO3 */
	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_max14745	,1	,0x16 	,0x03   ,1  ,enable);
}

void bl_max14745_vmc_vr_control(unsigned char enable)
{
	/* VUSB use max14745 LDO2 */
	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_max14745	,1	,0x14 	,0x03   ,1  ,enable);
}

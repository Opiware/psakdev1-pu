/* Copyright Statement:
 *
 */

#include "bl_pmic.h"
#include "bl_mt6327.h" 

unsigned int bl_mt6327_init(void)
{
	unsigned char chip_id;
	/*Find pmic chip id*/
	/*read MT6327 pmic chip id = 0x27*/
	chip_id = bl_pmic_get_register_value(BL_PMIC_I2C_ADDR_MT6327,1,MT6327_CID0,0xFF,0);
	if(chip_id == 0x27)
	{
		/* Set Vcore Voltage to 1.3V*/
		//bl_mt6327_vcore_set_1p3v();
		/* Set VMC Voltage to 2.8V*/
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x87,0x07,4,0x04);


		// actual can't disable,why???
		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x57,0x01,0,0x00);// Set VMD is controled by register,not SRCLKEN
	//	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x53,0x01,0,0x00);//disable VMD
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x56,0x1f,0,0x14);//adjust VMD voltage===1.2v   (0.75V~1.525V)

		// actual can't disable,why???
		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x63,0x02,0,0x00);// Set VRF18 is controled by register,not SRCLKEN
	//	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x63,0x01,0,0x00);//disable VRF18
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x65,0x1f,0,0x0e);//adjust VRF18 voltage===1.8v   (1.45V~1.25V)

		// actual can't disable,why???
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x82,0x01,0,0x00);//disable V18

		// actual can't disable,why???
	//	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x84,0x01,0,0x00);//disable VSIM
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x84,0x10,0,0x01);//adjust VSIM voltage===3.0v   (1.8V  3.0V)

		
		//bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x88,0x01,0,0x00);//disable VMC
		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x87,0x70,0,0x40);//adjust VMC voltage===2.8v   (1.3V 1.5V 1.8V 2.5V 2.8V 3.0V 3.1V)

		
		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0x8a,0x31,0,0x21);//default is disable and 1.2v,adjust VM voltage===1.8v   (1.2V 1.5V 1.8V), enable VM
		

		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0xa1,0x02,0,0x00);// Set VTCXO is controled by register,not SRCLKEN
	//	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0xa1,0x01,0,0x00);//disable VTCXO

		
	//	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,0xa4,0x01,0,0x00);//disable VA
		
		return (0);
	}	
	else{
		return (1);
	}
}

void bl_mt6327_vcore_set_1p3v(void)
{
    // psi_mode : OVR/HP/LP/S1
	//PMIC_VCORE_1P3V = 6,
   bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6327,1,MT6327_VMD_CON5,0x1F,0,0x1F);
}

void bl_mt6327_vusb_vr_control(unsigned char enable)
{
    
}

void bl_mt6327_vmc_vr_control(unsigned char enable)
{
    
}

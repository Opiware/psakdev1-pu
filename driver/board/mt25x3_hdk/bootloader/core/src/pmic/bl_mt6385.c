/* Copyright Statement:
 *
 */

#include "bl_pmic.h"
#include "bl_mt6385.h" 

unsigned int bl_mt6385_init(void)
{
	unsigned char chip_id;
	/*Find pmic chip id*/
	/*read MT6385 pmic chip id = 0x85*/
	chip_id = bl_pmic_get_register_value(BL_PMIC_I2C_ADDR_MT6385,2,1,0xFF,0);
	if(chip_id == 0x85)
	{
		/* latch power key */
		bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PPCCTL0	,0x01	,0  ,1);//RG_PWRHOLD
		/* Set Vcore Voltage to 1.3V*/
		bl_mt6385_vcore_set_1p3v();
		return (0);
	}	
	else{
		return (1);
	}
}

void bl_mt6385_vcore_set_1p3v(void)
{
    // psi_mode : OVR/HP/LP/S1
	//PMIC_VCORE_1P3V = 6,
    int vcbuck_voval[7]={2,4,6,8,10,12,14};
    int vc_ldo_vosel[7]={0,2,4,6, 8,10,12};

    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0	,0xFF	,0	,0xFC);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1	,0xFF   ,0  ,0xDA);
	//PMU_RG_PSIOVR
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICTL		,0x01   ,0  ,0x1);  // switch to PSIOVR

    //case PMIC_PSI_HP:
	//RG_HP_VC_BUCK_VOVAL
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VCBUCKPSI0	,0x0F   ,4  ,vcbuck_voval[6]);
	//RG_HP_VC_LDO_VOSEL
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VCLDOPSI0	,0x0F   ,4  ,vc_ldo_vosel[6]);
	
    //case PMIC_PSI_LP:
	//RG_LP_VC_BUCK_VOVAL
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VCBUCKPSI1	,0x0F   ,4  ,vcbuck_voval[6]);
	//RG_LP_VC_LDO_VOSEL
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VCLDOPSI2 	,0x0F   ,4  ,vc_ldo_vosel[6]);

	//PMU_RG_PSIOVR
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICTL   	,0x01   ,0  ,0x0);  // switch to PSI Bus
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0 	,0xFF   ,0  ,0x0);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1 	,0xFF   ,0  ,0x0);
}

void bl_mt6385_vusb_vr_control(unsigned char enable)
{
    int poll_stb_b=1;

    if(enable)  // polling STB status
        poll_stb_b = 0;

    // Fill protection key
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0	,0xFF   ,0  ,0xFC);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1 	,0xFF   ,0  ,0xDA);
	
	//case PMIC_VUSB:
	//PMU_RG_VUSB_EN
	bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VUSBCTL0	,0x01	,0  ,enable);
	while(poll_stb_b==0)
	{
		//PMU_RGS_VUSB_STBSTS
		poll_stb_b = bl_pmic_get_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VUSBCTL0	,0x01	,6);
	}

    // Clear protection key
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0	,0xFF	,0  ,0x0);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1	,0xFF	,0  ,0x0);
}

void bl_mt6385_vmc_vr_control(unsigned char enable)
{
    int poll_stb_b=1;

    if(enable)  // polling STB status
        poll_stb_b = 0;
        
    // Fill protection key
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0	,0xFF   ,0  ,0xFC);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1 	,0xFF   ,0  ,0xDA);

    //PMU_RG_VMC_EN
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VMCCTL0	    ,0x01	,0  ,enable);
    while (poll_stb_b == 0) {        
        poll_stb_b = bl_pmic_get_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_VMCCTL0	,0x01	,6);
    }       

    // Clear protection key
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY0	,0xFF	,0  ,0x0);
    bl_pmic_set_register_value(BL_PMIC_I2C_ADDR_MT6385	,2	,MT6385_PSICKEY1	,0xFF	,0  ,0x0);
}

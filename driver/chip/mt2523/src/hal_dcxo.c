/* Copyright Statement:
 *
 */

#include "hal_dcxo.h"
#include "hal_log.h"
#include "hal_cm4_topsm.h"
void hal_dcxo_init()
{
    log_hal_info("DCXO init\n");

    //check RTC_CON[9]=0
    *PLL_DPM_CON1 = 0x277;

    //ANA CFGSYS_BASE (0XA21D0000) + 0x0014, set [8:0]=0x50 to set DCXO 1612 settle time to 2500uA
    *ACFG_PCLK_CON = 0x50;

    //ANA CFGSYS_BASE (0XA21D0000) + 0x0030, set bit[10] GSM_DCXO_CTL_EN=1, bit[8] EXT_DCXO_CTL_EN=1, bit[3] FRC_DCXO_F26M_RDY=0
    *ACFG_DCXO_PCON0 = 0X500;

    //ANA CFGSYS_BASE (0XA21D0000) + 0x0034, set [15:8]=0xA to set DCXO power switch ready time to 312.5uA, set [7:0]=0x14 to set DCXO 3225 settle time to 625uA
    *ACFG_DCXO_PCON1 = 0xa14;

    //ANA CFGSYS_BASE (0XA21D0000) + 0x0038, set [8:0]=0xA to set VIO18 settle time to 312.5uA
    *ACFG_DCXO_PCON2 = 0xA;
}

bool hal_dcxo_is_32kless(void)
{
    return false;
}

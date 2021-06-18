/* Copyright Statement:
 *
 */

#include <stdint.h>
#include "emi_hw_internal.h"
#include "emi_sw_internal.h"


static EMI_RUNTIME_Info *emi_cur_setting;

kal_int32 EMI_QueryCurSetting(void *emi_setting)
{
    emi_cur_setting = emi_setting ;
    emi_cur_setting->EMI_CONM_value = *EMI_CONM;
    emi_cur_setting->EMI_GENA_value = *EMI_GENA;
    emi_cur_setting->EMI_RDCT_value = *EMI_RDCT;
    emi_cur_setting->EMI_DLLV_value = *EMI_DLLV;

    emi_cur_setting->EMI_IDLC_value = *EMI_IDLC;
    emi_cur_setting->EMI_IDLD_value = *EMI_IDLD;
    emi_cur_setting->EMI_IDLE_value = *EMI_IDLE;

    emi_cur_setting->EMI_ODLC_value = *EMI_ODLC;
    emi_cur_setting->EMI_ODLD_value = *EMI_ODLD;
    emi_cur_setting->EMI_ODLE_value = *EMI_ODLE;
    emi_cur_setting->EMI_ODLF_value = *EMI_ODLF;

    emi_cur_setting->EMI_IOA_value = *EMI_IOA;
    emi_cur_setting->EMI_IOB_value = *EMI_IOB;

    emi_cur_setting->EMI_DSRAM_value = *EMI_DSRAM;
    emi_cur_setting->EMI_MSRAM_value = *EMI_MSRAM;

    emi_cur_setting->EMI_ARBA_value = *EMI_ARBA;
    emi_cur_setting->EMI_ARBB_value = *EMI_ARBB;
    emi_cur_setting->EMI_ARBC_value = *EMI_ARBC;

    emi_cur_setting->EMI_SLCT_value = *EMI_SLCT;
    emi_cur_setting->EMI_ABCT_value = *EMI_ABCT;

    emi_cur_setting->reg_num = 20;

    return 0;
}


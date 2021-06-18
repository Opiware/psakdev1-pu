/* Copyright Statement:
 *
 */

#ifndef __HAL_CLOCK_PLATFORM_MT7686_H__
#define __HAL_CLOCK_PLATFORM_MT7686_H__

#include "hal_platform.h"

#ifdef HAL_CLOCK_MODULE_ENABLED

#define STR_VALUE(arg)      #arg
#define __stringify(name) STR_VALUE(name)


/*************************************************************************
 * Define clock force on register and bits structure
 *************************************************************************/
enum clock_force_on_id {
    CLK_SYS_FORCE_ON,
    CLK_SFC_FORCE_ON,
    CLK_CONN_FORCE_ON,
    CLK_SPIMST_FORCE_ON,
    CLK_SDIOMST_FORCE_ON,
    NR_CLKFORCE_ON,
};

/*************************************************************************
 * Define clock change bit register and bits structure
 *************************************************************************/
typedef enum {
    CHG_SYS,
    CHG_SFC,
    CHG_CONN,
    CHG_SPIMST,
    NR_CLKCHANGE_BIT,
} clock_change_bit_id;

/*************************************************************************
 * Define clock mux register and bits structure
 *************************************************************************/
typedef enum {
    CLK_SYS_SEL,
    CLK_SFC_SEL,
    CLK_CONN_SEL,
    CLK_SPIMST_SEL,
    CLK_XTALCTL_SEL,
    CLK_SDIOMST_SEL,
    NR_MUXS,
    CLK_MUX_SEL_NONE,
} clock_mux_sel_id;

/*************************************************************************
* Define clock gating register and bits structure
* Note: MUST modify clk_cg_mask in hal_clock.c if hal_clock_cg_id is changed
*************************************************************************/
enum {
    NR_CLOCKS           = HAL_CLOCK_CG_END
};

enum {
    GRP_PDN_COND0       = 0,
    GRP_XO_PDN_COND0    = 1,
    NR_GRPS             = 2,
};

#endif /* HAL_CLOCK_MODULE_ENABLED */
#endif /* __HAL_CLOCK_PLATFORM_MT7686_H__ */

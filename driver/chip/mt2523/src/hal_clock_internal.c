/* Copyright Statement:
 *
 */

#include "hal_clock.h"
#include "hal_clock_internal.h"

#ifdef HAL_CLOCK_MODULE_ENABLED

#include <stdio.h>
#include <assert.h>

#include "memory_attribute.h"

#ifdef MTK_SYSTEM_CLOCK_208M
ATTR_RWDATA_IN_TCM clock_cm_freq_state_id cm_freq_state = CM_208M_STA;
#elif defined MTK_SYSTEM_CLOCK_104M
ATTR_RWDATA_IN_TCM clock_cm_freq_state_id cm_freq_state = CM_104M_STA;
#elif defined MTK_SYSTEM_CLOCK_26M
ATTR_RWDATA_IN_TCM clock_cm_freq_state_id cm_freq_state = CM_26M_STA;
#else
ATTR_RWDATA_IN_TCM clock_cm_freq_state_id cm_freq_state = CM_208M_STA;
#endif


ATTR_TEXT_IN_TCM bool is_clk_use_lfosc(void)
{
#ifdef CLK_USE_LFOSC
    return true;
#else
    return false;
#endif
}

ATTR_TEXT_IN_TCM bool is_clk_use_mpll(void)
{
#ifdef CLK_USE_MPLL
    return true;
#else
    return false;
#endif
}

ATTR_TEXT_IN_TCM void cm_bus_clk_208m()
{
    if (is_clk_use_mpll()) {
        cm_bus_clk_208m_mpll_mpll();
    } else {
        cm_bus_clk_208m_mpll_hfosc();
    }
}

ATTR_TEXT_IN_TCM void cm_bus_clk_104m()
{
    if (is_clk_use_mpll()) {
        cm_bus_clk_104m_mpll_mpll();
    } else {
        cm_bus_clk_104m_hfosc_hfosc();
    }
}

ATTR_TEXT_IN_TCM void cm_bus_clk_26m(void)
{
    if (is_clk_use_lfosc()) {
        cm_bus_clk_26m_lfosc_lfosc();
    } else {
        cm_bus_clk_26m_dcxo_dcxo();
    }
}

ATTR_TEXT_IN_TCM void peri_clk_26m(void)
{
    if (is_clk_use_lfosc()) {
        peri_26m_lfosc();
    } else {
        peri_26m_dcxo();
    }
}

#endif


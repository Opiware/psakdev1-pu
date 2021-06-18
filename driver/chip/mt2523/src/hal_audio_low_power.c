/* Copyright Statement:
 *
 */

#include "hal_audio_low_power.h"

#if defined(HAL_AUDIO_LOW_POWER_ENABLED) && defined(HAL_AUDIO_MODULE_ENABLED)

static hal_audio_lowpower_struct_t audio_lowpwr_handle;

bool audio_lowpower_check_status(void)
{
    return audio_lowpwr_handle.audio_lowpower_enable;
}

void audio_lowpower_set_26mclock(bool flag)
{
    if (flag) {
        if ((!audio_lowpwr_handle.clock_switch_26m) & audio_lowpower_check_status()) {
            hal_dsp_topsm_get_resource(RM_MODEM_DSP_1, false);
            audio_lowpwr_handle.clock_switch_26m = true;
        }
    } else {
        if (audio_lowpwr_handle.clock_switch_26m & audio_lowpower_check_status()) {
            hal_dsp_topsm_get_resource(RM_MODEM_DSP_1, true);
            audio_lowpwr_handle.clock_switch_26m = false;
        }
    }
}

void audio_lowpower_set_clock_mode(bool flag)
{
    uint32_t savedmask;
    uint32_t register_value;

    savedmask = save_and_set_interrupt_mask();
    register_value  = *MODEM_ALLOW_26M_CLKSW;
    if (flag) {
        *MODEM2G_TOPSM_SW_CLK_FORCE_ON_SET = ((unsigned int)0x1 << 31);
        register_value |= (0x1 << 0);
    } else {
        *MODEM2G_TOPSM_SW_CLK_FORCE_ON_CLR = ((unsigned int)0x1 << 31);
        register_value &= ~(0x1 << 0);
    }
    *MODEM_ALLOW_26M_CLKSW = register_value;
    restore_interrupt_mask(savedmask);
}

void audio_lowpower_sw_trigger_event_set(bool flag)
{
    hal_dsp_topsm_get_resource(RM_MODEM_DSP_2, flag);
}

void audio_lowpower_set_mode(bool enable)
{
    audio_lowpwr_handle.audio_lowpower_enable = enable;
}

void audio_lowpower_init(void)
{
    audio_lowpwr_handle.audio_lowpower_enable = false;
}

#endif /* defined(HAL_AUDIO_LOW_POWER_ENABLED) && defined(HAL_AUDIO_MODULE_ENABLED) */

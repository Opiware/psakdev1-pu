/* Copyright Statement:
 *
 */

#include "hal_wdt.h"

#if defined(HAL_WDT_MODULE_ENABLED)
#include "hal_wdt_internal.h"

void wdt_set_length(uint32_t seconds)
{
    uint32_t length_register_value = 0;
    /* trasfer seconds to register value */
    length_register_value = (seconds * 10000) / WDT_1_TICK_LENGTH;
    length_register_value <<= WDT_STANDARD_16_OFFSET;
    length_register_value |= WDT_LENGTH_KEY;

    /* write the length register */
    WDT_REGISTER->WDT_LENGTH = length_register_value;

    /*restart WDT to let the new value take effect */
    WDT_REGISTER->WDT_SW_RESTART = WDT_SW_RESTART_KEY;
}

void wdt_set_mode(uint32_t value)
{
    if (HAL_WDT_MODE_INTERRUPT == value) {
        WDT_REGISTER->WDT_IE = (WDT_STANDARD_1_MASK | WDT_IE_KEY);
    } else {
        WDT_REGISTER->WDT_IE = WDT_IE_KEY;
    }
}

void wdt_set_restart(void)
{
    WDT_REGISTER->WDT_SW_RESTART = WDT_SW_RESTART_KEY;
}

void wdt_set_sw_rst(void)
{
    WDT_REGISTER->WDT_SW_RST = WDT_SW_RST_KEY;
}

void wdt_set_enable(uint32_t enable)
{
    if (0 != enable) {
        WDT_REGISTER->WDT_EN = (WDT_STANDARD_1_MASK | WDT_EN_KEY);
        WDT_REGISTER->WDT_AUTO_RESTART_EN = (WDT_STANDARD_1_MASK | WDT_AUTO_RESTART_EN_KEY);
    } else {
        WDT_REGISTER->WDT_EN = WDT_EN_KEY;
        WDT_REGISTER->WDT_AUTO_RESTART_EN = WDT_AUTO_RESTART_EN_KEY;
    }
}

uint32_t wdt_get_reset_status(void)
{
    uint32_t status_register_value = 0;

    status_register_value = WDT_REGISTER->WDT_STA;

    if (0 != (status_register_value & WDT_STA_HW_WDT_MASK)) {
        return HAL_WDT_TIMEOUT_RESET;
    } else if (0 != (status_register_value & WDT_STA_SW_WDT_MASK)) {
        return HAL_WDT_SOFTWARE_RESET;
    }

    return HAL_WDT_NONE_RESET;
}

uint32_t wdt_get_enable_status(void)
{
    return (WDT_REGISTER->WDT_EN >> WDT_STANDARD_1_OFFSET);
}

uint32_t wdt_get_mode_status(void)
{
    return (WDT_REGISTER->WDT_IE >> WDT_STANDARD_1_OFFSET);
}

void wdt_clear_irq(void)
{
    uint32_t status = 0;
    status = WDT_REGISTER->WDT_INT;
    status = status;
}

#endif


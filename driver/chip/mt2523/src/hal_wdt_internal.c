/* Copyright Statement:
 *
 */

#include "hal_wdt.h"
#if defined(HAL_WDT_MODULE_ENABLED)
#include "hal_wdt_internal.h"
#include "hal_log.h"
#include "hal_gpt.h"





void wdt_set_length(uint32_t seconds)
{
    uint32_t length_register_value = 0;
    /* trasfer seconds to register value */
    length_register_value = (seconds * 10000) / WDT_1_TICK_LENGTH;
    length_register_value <<= WDT_LENGTH_KEY_OFFSET;
    length_register_value |= WDT_LENGTH_KEY;

    /* write the length register */
    WDT_REGISTER->WDT_LENGTH = length_register_value;

    /*restart WDT to let the new value take effect */
    WDT_REGISTER->WDT_RESTART = WDT_RESTART_KEY;
}

void wdt_set_mode_register_by_bit(uint32_t bit_offset, uint32_t value)
{
    uint32_t mode_register_value = 0;
    /* read */
    mode_register_value = WDT_REGISTER->WDT_MODE;
    /* modify */
    if (0 == value) {
        mode_register_value &= ~(0x1 << bit_offset) ;
    } else {
        mode_register_value |= (0x1 << bit_offset) ;
    }
    /*write*/
    mode_register_value &= 0x0000FFFF;
    mode_register_value |= (WDT_MODE_KEY << WDT_MODE_KEY_OFFSET);
    WDT_REGISTER->WDT_MODE = mode_register_value;

    /* delay 1 32K tick for hardware requirement */
    hal_gpt_delay_us(35);


}

uint32_t wdt_get_reset_status(void)
{
    uint32_t status_register_value = 0;

    status_register_value = WDT_REGISTER->WDT_STA;

    if (0 != (status_register_value & WDT_STATUS_TIME_OUT_MASK)) {
        return HAL_WDT_TIMEOUT_RESET;
    } else if (0 != (status_register_value & WDT_STATUS_SWRST_MASK)) {
        return HAL_WDT_SOFTWARE_RESET;
    }

    return HAL_WDT_NONE_RESET;
}


#endif

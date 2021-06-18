/* Copyright Statement:
 *
 */

#include "bl_gpt.h"
#include "bl_wdt.h"
#include "hal_wdt.h"
#include "hal_wdt_internal.h"

void wdt_set_length(uint32_t seconds)
{
    uint32_t length_register_value = 0;
    /* trasfer seconds to register value */
    length_register_value = (seconds * 10000) / WDT_1_TICK_LENGTH;
    length_register_value <<= WDT_LENGTH_KEY_OFFSET;
    length_register_value |= WDT_LENGTH_KEY;

    /* write the length register */
    (*((volatile unsigned int *)(BL_WDT_LENGTH)) = (unsigned int)length_register_value);

    /*restart WDT to let the new value take effect */
    (*((volatile unsigned int *)(BL_WDT_RESTART)) = (unsigned int)0x1971);
}


void wdt_set_mode_register_by_bit(uint32_t bit_offset, uint32_t value)
{
    uint32_t mode_register_value = 0;
    /* read */
    mode_register_value = *((volatile unsigned int *)(BL_WDT_MODE));
    /* modify */
    if (0 == value) {
        mode_register_value &= ~(0x1 << bit_offset) ;
    } else {
        mode_register_value |= (0x1 << bit_offset) ;
    }
    /*write*/
    mode_register_value &= 0x0000FFFF;
    mode_register_value |= (WDT_MODE_KEY << WDT_MODE_KEY_OFFSET);
    *((volatile unsigned int *)(BL_WDT_MODE)) = mode_register_value;

    /* delay 1 32K tick for hardware requirement */
    bl_gpt_delay_us(35);
}
hal_wdt_status_t hal_wdt_init(hal_wdt_config_t *wdt_config)
{
    /* parameter check, reset mode only in bootloader. */
    if (wdt_config == NULL || (HAL_WDT_MODE_RESET != wdt_config->mode)) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    if (wdt_config->seconds > WDT_MAX_TIMEOUT_VALUE) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    /*set WDT length*/
    wdt_set_length(wdt_config->seconds);

    /* set WDT mode */
    wdt_set_mode_register_by_bit(WDT_MODE_IRQ, wdt_config->mode);

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_enable(uint32_t magic)
{
    if (HAL_WDT_ENABLE_MAGIC != magic) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    wdt_set_mode_register_by_bit(WDT_MODE_ENABLE, WDT_ENABLE);
    wdt_set_mode_register_by_bit(WDT_MODE_HW_AUTO_RESTART_EN, WDT_ENABLE);
    /* restart wdt */
    (*((volatile unsigned int *)(BL_WDT_RESTART)) = (unsigned int)0x1971);

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_feed(uint32_t magic)
{
    (*((volatile unsigned int *)(BL_WDT_RESTART)) = (unsigned int)0x1971);
    /* Wait for 4T 32k cycle. */
    bl_gpt_delay_us(123);
    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_software_reset(void)
{
    (*((volatile unsigned int *)(BL_WDT_SW_RST)) = (unsigned int)0x1209);
    return HAL_WDT_STATUS_OK;
}


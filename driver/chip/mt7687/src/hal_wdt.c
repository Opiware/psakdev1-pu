/* Copyright Statement:
 *
 */

#include "hal_wdt.h"
#if defined(HAL_WDT_MODULE_ENABLED)
#include "low_hal_wdt.h"
#include "mt7687.h"
#include "hal_nvic.h"
#include "hal_gpt.h"

static hal_wdt_callback_t   s_hal_wdt_callback;
static bool                 s_hal_enable;
static hal_wdt_mode_t       s_hal_mode;

static void hal_wdt_isr(hal_nvic_irq_t irq_number)
{
    if (s_hal_wdt_callback) {
        s_hal_wdt_callback(HAL_WDT_TIMEOUT_RESET);
    }

}


hal_wdt_status_t hal_wdt_init(hal_wdt_config_t *wdt_config)
{
    if (!wdt_config) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    if (wdt_config->mode != HAL_WDT_MODE_RESET &&
            wdt_config->mode != HAL_WDT_MODE_INTERRUPT) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    s_hal_mode = (wdt_config->mode);

    // Call lhal WDT.
    halWDTConfig((wdt_config->mode), 0, 0, 1);
    halWDTSetTimeout((((wdt_config->seconds) * 1000) / 32) - 1);

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_deinit(void)
{
    /* disable wdt */
    halWDTEnable(0);
    s_hal_enable = false;
    return HAL_WDT_STATUS_OK;
}


hal_wdt_status_t hal_wdt_enable(uint32_t magic)
{
    if (magic != HAL_WDT_ENABLE_MAGIC) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    s_hal_enable = true;

    // Call lhal WDT.
    halWDTEnable(1);

    return HAL_WDT_STATUS_OK;
}


hal_wdt_status_t hal_wdt_disable(uint32_t magic)
{
    if (magic != HAL_WDT_DISABLE_MAGIC) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    s_hal_enable = false;

    // Call lhal WDT.
    halWDTEnable(0);

    return HAL_WDT_STATUS_OK;
}


hal_wdt_status_t hal_wdt_feed(uint32_t magic)
{
    if (magic != HAL_WDT_FEED_MAGIC) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    // Call lhal WDT.
    halWDTRestart();
    /* Wait for 4T 32k cycle for HW limitation */
    hal_gpt_delay_us(123);

    return HAL_WDT_STATUS_OK;
}


hal_wdt_callback_t hal_wdt_register_callback(const hal_wdt_callback_t wdt_callback)
{
    hal_wdt_callback_t  old_callback;

    old_callback       = s_hal_wdt_callback;
    s_hal_wdt_callback = wdt_callback;

    // register ISR
    hal_nvic_register_isr_handler(CM4_WDT_IRQ, hal_wdt_isr);
    hal_nvic_set_priority((IRQn_Type)CM4_WDT_IRQ, (uint32_t)CM4_WDT_PRI);
    hal_nvic_enable_irq((IRQn_Type)CM4_WDT_IRQ);

    return old_callback;
}

hal_wdt_status_t hal_wdt_software_reset(void)
{
    halWDTSoftwareReset();
    return HAL_WDT_STATUS_OK;
}


bool hal_wdt_get_enable_status(void)
{
    return s_hal_enable;
}


hal_wdt_mode_t hal_wdt_get_mode(void)
{
    return s_hal_mode;
}

hal_wdt_reset_status_t hal_wdt_get_reset_status(void)
{
    uint32_t return_status;
    return_status = halWDTReadInterruptStatus();
    if (0 != (return_status & (0x1 << WDT_STA_WDT_OFFSET))) {
        return HAL_WDT_TIMEOUT_RESET;
    } else if (0 != (return_status & (0x1 << WDT_STA_SW_WDT_OFFSET))) {
        return HAL_WDT_SOFTWARE_RESET;
    }
    return HAL_WDT_NONE_RESET;
}

#endif

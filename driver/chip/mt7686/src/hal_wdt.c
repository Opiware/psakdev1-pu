/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_wdt.h"

#if defined(HAL_WDT_MODULE_ENABLED)
#include "hal_wdt_internal.h"
#include "hal_nvic.h"
#include "hal_gpt.h"

/* Global variable */
static hal_wdt_callback_t s_hal_wdt_callback = NULL;

static void hal_wdt_isr(void);

/*****************************************************************************
* Function
*****************************************************************************/

hal_wdt_status_t hal_wdt_init(hal_wdt_config_t *wdt_config)
{
    /* parameter check */
    if (wdt_config == NULL || (HAL_WDT_MODE_RESET != wdt_config->mode && HAL_WDT_MODE_INTERRUPT != wdt_config->mode)) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    if (wdt_config->seconds > WDT_MAX_TIMEOUT_VALUE) {
        return HAL_WDT_STATUS_INVALID_PARAMETER;
    }

    s_hal_wdt_callback = NULL;

    /*set WDT length*/
    wdt_set_length(wdt_config->seconds);

    /* set WDT mode */
    wdt_set_mode(wdt_config->mode);

    /* User can not call hal_wdt_register_callback */
    if (HAL_WDT_MODE_INTERRUPT == wdt_config->mode) {

        /* register NVIC */
        hal_nvic_register_isr_handler(RGU_IRQn, (hal_nvic_isr_t)hal_wdt_isr);
        hal_nvic_enable_irq(RGU_IRQn);
    }

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_deinit(void)
{
    /* disable wdt */
    wdt_set_enable(false);

    s_hal_wdt_callback = NULL;

    return HAL_WDT_STATUS_OK;
}

hal_wdt_callback_t hal_wdt_register_callback(hal_wdt_callback_t wdt_callback)
{
    hal_wdt_callback_t current_wdt_callback;
    /* no need error check. allow null register */
    current_wdt_callback = s_hal_wdt_callback;

    s_hal_wdt_callback = wdt_callback;

    return current_wdt_callback;
}

hal_wdt_status_t hal_wdt_feed(uint32_t magic)
{
    if (HAL_WDT_FEED_MAGIC != magic) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    /* write wdt restart register */
    wdt_set_restart();

    /* Wait for 4T 32k cycle for HW limitation */
    hal_gpt_delay_us(123);

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_software_reset(void)
{
    wdt_set_sw_rst();
    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_enable(uint32_t magic)
{
    if (HAL_WDT_ENABLE_MAGIC != magic) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    wdt_set_enable(true);
    /* restart wdt */
    wdt_set_restart();

    return HAL_WDT_STATUS_OK;
}

hal_wdt_status_t hal_wdt_disable(uint32_t magic)
{
    if (HAL_WDT_DISABLE_MAGIC != magic) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    wdt_set_enable(false);

    return HAL_WDT_STATUS_OK;
}

hal_wdt_reset_status_t hal_wdt_get_reset_status(void)
{
    return ((hal_wdt_reset_status_t)wdt_get_reset_status());
}

bool hal_wdt_get_enable_status(void)
{
    return (wdt_get_enable_status());
}

hal_wdt_mode_t hal_wdt_get_mode(void)
{
    return ((hal_wdt_mode_t)wdt_get_mode_status());
}

static void hal_wdt_isr(void)
{
    hal_wdt_reset_status_t wdt_reset_status;

    wdt_reset_status = (hal_wdt_reset_status_t)wdt_get_reset_status();
    if (NULL != s_hal_wdt_callback) {
        s_hal_wdt_callback(wdt_reset_status);
    }
    /* clear WDT IRQ */
    wdt_clear_irq();
}

#endif


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
    wdt_set_mode_register_by_bit(WDT_MODE_IRQ, wdt_config->mode);

    /* User can not call hal_wdt_register_callback */
    if (HAL_WDT_MODE_INTERRUPT == wdt_config->mode) {

        /* register NVIC */
        hal_nvic_register_isr_handler(RGU_IRQn, (hal_nvic_isr_t)hal_wdt_isr);
        hal_nvic_enable_irq(RGU_IRQn);
    }

    /* After FOTA using Flash to replace WDT_retention_flag, we can send
       WDT signal to AIDE to performe cold reset */
    WDT_MASK_ADIE_SIGNAL();

    return HAL_WDT_STATUS_OK;
}


hal_wdt_status_t hal_wdt_deinit(void)
{
    /* disable wdt */
    wdt_set_mode_register_by_bit(WDT_MODE_ENABLE, WDT_DISABLE);

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
    WDT_SET_RESTART();

    /* Wait for 4T 32k cycle for HW limitation */
    hal_gpt_delay_us(123);

    return HAL_WDT_STATUS_OK;
}



hal_wdt_status_t hal_wdt_software_reset(void)
{
    WDT_SET_SOFTWARE_RESET();
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
    WDT_SET_RESTART();

    return HAL_WDT_STATUS_OK;
}



hal_wdt_status_t hal_wdt_disable(uint32_t magic)
{
    if (HAL_WDT_DISABLE_MAGIC != magic) {
        return HAL_WDT_STATUS_INVALID_MAGIC;
    }

    wdt_set_mode_register_by_bit(WDT_MODE_ENABLE, WDT_DISABLE);
    wdt_set_mode_register_by_bit(WDT_MODE_HW_AUTO_RESTART_EN, WDT_DISABLE);

    return HAL_WDT_STATUS_OK;
}



hal_wdt_reset_status_t hal_wdt_get_reset_status(void)
{
    hal_wdt_reset_status_t status;

    status = (hal_wdt_reset_status_t)wdt_get_reset_status();

    return status;
}



bool hal_wdt_get_enable_status(void)
{
    bool wdt_status = 0;

    wdt_status = WDT_GET_MODE_BIT_VALUE(WDT_MODE_ENABLE);

    return wdt_status;
}



hal_wdt_mode_t hal_wdt_get_mode(void)
{
    hal_wdt_mode_t wdt_mode = HAL_WDT_MODE_RESET;

    wdt_mode = (hal_wdt_mode_t)WDT_GET_MODE_BIT_VALUE(WDT_MODE_IRQ);

    return wdt_mode;

}




static void hal_wdt_isr(void)
{
    hal_wdt_reset_status_t wdt_reset_status;

    wdt_reset_status = (hal_wdt_reset_status_t)wdt_get_reset_status();
    if (NULL != s_hal_wdt_callback) {
        s_hal_wdt_callback(wdt_reset_status);
    }
    /* clear WDT IRQ */
    WDT_CLEAR_INTERRUPT();
}

#endif


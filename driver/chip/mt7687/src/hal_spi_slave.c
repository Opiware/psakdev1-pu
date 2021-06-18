/* Copyright Statement:
 *
 */

#include "hal_spi_slave.h"

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED

#include "hal_spi_slave_internal.h"
#include "hal_nvic.h"

static hal_spi_slave_callback_t g_spis_callback = NULL;
static void *g_spis_user_data = NULL;

static void hal_spi_slave_isr(hal_nvic_irq_t irq_number)
{
    SPIS_CLEAR_IRQ();

    g_spis_callback(g_spis_user_data);
}

static bool is_slave_config(const hal_spi_slave_config_t *spi_configure)
{
    bool ret = true;

    ret &= (((spi_configure->polarity) == HAL_SPI_SLAVE_CLOCK_POLARITY0) || \
            ((spi_configure->polarity) == HAL_SPI_SLAVE_CLOCK_POLARITY1));

    ret &= (((spi_configure->phase) == HAL_SPI_SLAVE_CLOCK_PHASE0) || \
            ((spi_configure->phase) == HAL_SPI_SLAVE_CLOCK_PHASE1));

    return ret;
}


hal_spi_slave_status_t hal_spi_slave_init(hal_spi_slave_port_t spi_port, hal_spi_slave_config_t *spi_configure)
{
    uint32_t spis_mode = 0;
    if (spi_port >= HAL_SPI_SLAVE_MAX) {
        return HAL_SPI_SLAVE_STATUS_ERROR_PORT;
    }
    if (!is_slave_config(spi_configure)) {
        return HAL_SPI_SLAVE_STATUS_INVALID_PARAMETER;
    }

    spis_mode = ((spi_configure->polarity << 1) | (spi_configure->phase));
    SPIS_SET_MODE(((spis_mode) & (0x3)));

    SPIS_20M_CLOCK_ENABLE();

    return HAL_SPI_SLAVE_STATUS_OK;
}

hal_spi_slave_status_t hal_spi_slave_register_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t callback, void *user_data)
{
    if (spi_port >= HAL_SPI_SLAVE_MAX) {
        return HAL_SPI_SLAVE_STATUS_ERROR_PORT;
    }
    if (NULL == callback) {
        return HAL_SPI_SLAVE_STATUS_INVALID_PARAMETER;
    }

    /* user_data can be as NULL */
    g_spis_callback = callback;
    g_spis_user_data = user_data;

    /* register lisr to nvic */
    hal_nvic_register_isr_handler(CM4_SPI_SLAVE_IRQ, hal_spi_slave_isr);
    hal_nvic_set_priority(CM4_SPI_SLAVE_IRQ, CM4_SPI_SLAVE_PRI);
    hal_nvic_enable_irq(CM4_SPI_SLAVE_IRQ);

    return HAL_SPI_SLAVE_STATUS_OK;

}


#endif /*HAL_SPI_SLAVE_MODULE_ENABLED*/



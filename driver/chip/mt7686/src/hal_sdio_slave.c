/* Copyright Statement:
 *
 */
#include "hal.h"
#include "hal_sdio_slave.h"
#include "hal_sdio_slave_internal.h"

#ifdef HAL_SDIO_SLAVE_MODULE_ENABLED
#include "hal_log.h"
#include "assert.h"
#include "hal_platform.h"
#include <string.h>

extern sdio_slave_private_t sdio_private;

hal_sdio_slave_status_t hal_sdio_slave_register_callback(hal_sdio_slave_port_t sdio_slave_port, hal_sdio_slave_callback_t sdio_slave_callback, void *user_data)
{
    sdio_private.sdio_property.sdio_slave_callback = sdio_slave_callback;
    sdio_private.sdio_property.sdio_slave_callback_user_data = user_data;

    return HAL_SDIO_SLAVE_STATUS_OK;
}


hal_sdio_slave_status_t hal_sdio_slave_init(hal_sdio_slave_port_t sdio_slave_port)
{
    sdio_slave_init();

    return HAL_SDIO_SLAVE_STATUS_OK;
}



hal_sdio_slave_status_t hal_sdio_slave_read_mailbox(hal_sdio_slave_port_t sdio_slave_port, uint32_t mailbox_number, uint32_t *mailbox_value)
{
    while (true == sdio_slave_check_fw_own());

    sdio_slave_read_mailbox(mailbox_number, mailbox_value);

    return HAL_SDIO_SLAVE_STATUS_OK;
}


hal_sdio_slave_status_t hal_sdio_slave_write_mailbox(hal_sdio_slave_port_t sdio_slave_port, uint32_t mailbox_number, uint32_t mailbox_value)
{
    while (true == sdio_slave_check_fw_own());

    sdio_slave_write_mailbox(mailbox_number, mailbox_value);

    return HAL_SDIO_SLAVE_STATUS_OK;
}


hal_sdio_slave_status_t hal_sdio_slave_trigger_d2h_interrupt(hal_sdio_slave_port_t sdio_slave_port, uint32_t interrupt_number)
{
    while (true == sdio_slave_check_fw_own());

    sdio_slave_set_device_to_host_interrupt(interrupt_number);

    return HAL_SDIO_SLAVE_STATUS_OK;
}



hal_sdio_slave_status_t hal_sdio_slave_send_dma(hal_sdio_slave_port_t sdio_slave_port, hal_sdio_slave_rx_queue_id_t queue_id, const uint32_t *buffer, uint32_t size)
{
    sdio_slave_status_t status;

    while (true == sdio_slave_check_fw_own());

    status = sdio_slave_send((sdio_slave_rx_queue_id_t)queue_id, (uint32_t)buffer, size);
    if (SDIO_SLAVE_STATUS_OK != status) {
        return HAL_SDIO_SLAVE_STATUS_ERROR;
    }

    return HAL_SDIO_SLAVE_STATUS_OK;
}

hal_sdio_slave_status_t hal_sdio_slave_receive_dma(hal_sdio_slave_port_t sdio_slave_port, hal_sdio_slave_tx_queue_id_t queue_id, uint32_t *buffer, uint32_t size)
{
    sdio_slave_status_t status;

    while (true == sdio_slave_check_fw_own());

    status = sdio_slave_receive((sdio_slave_tx_queue_id_t)queue_id, (uint32_t)buffer, size);
    if (SDIO_SLAVE_STATUS_OK != status) {
        return HAL_SDIO_SLAVE_STATUS_ERROR;
    }

    return HAL_SDIO_SLAVE_STATUS_OK;
}

#endif


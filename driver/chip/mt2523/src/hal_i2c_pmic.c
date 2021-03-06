/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_i2c_master.h"
#if defined(HAL_I2C_MASTER_MODULE_ENABLED)
#include "hal_i2c_master_internal.h"
#include "hal_i2c_pmic.h"
#include "mt2523.h"
#include "hal_log.h"

#ifndef BL_LOAD_ENABLE
#include "hal_clock.h"
#endif

extern I2C_REGISTER_T *i2c_master_register[];
extern hal_clock_cg_id g_i2c_pdn_table[];


#define PMIC_I2C_PORT_TO_GLOBAL(i2c_port) ((uint32_t)i2c_port + (uint32_t)HAL_I2C_MASTER_MAX)


pmic_i2c_status_t pmic_i2c_init(pmic_i2c_port_t  i2c_port, const pmic_i2c_config_t *i2c_config)
{
    /* parameter check */
    if (PMIC_I2C_MASTER_MAX <= i2c_port) {
        return PMIC_I2C_STATUS_INVALID_PORT_NUMBER;
    }

#ifndef BL_LOAD_ENABLE
    hal_clock_enable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    /* calculate speed to register value */
    i2c_set_frequency(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), i2c_config->transfer_frequency);

#ifndef BL_LOAD_ENABLE
    hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    return PMIC_I2C_STATUS_OK;
}


pmic_i2c_status_t pmic_i2c_send_polling(pmic_i2c_port_t  i2c_port, uint8_t slave_address, const uint8_t *data, uint32_t size)
{
    i2c_transaction_status_t transaction_status;
    i2c_transaction_size_t config_size;
    /* parameter check */
    if (PMIC_I2C_MASTER_MAX <= i2c_port) {
        return PMIC_I2C_STATUS_INVALID_PORT_NUMBER;
    }
    if (NULL == data || size > I2C_FIFO_DEPTH) {
        return PMIC_I2C_STATUS_INVALID_PARAMETER;
    }

#ifndef BL_LOAD_ENABLE
    hal_clock_enable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    /*mask interrupt*/
    I2C_MASK_INTERRUPT(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));

    /*config i2c hardware*/
    config_size.send_size = size;
    config_size.receive_size = 0;

#ifdef MTK_EXTERNAL_PMIC
    /*for external PMIC*/
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_OPEN_DRAIN_SEND_POLLING, I2C_GET_SEND_ADDRESS(slave_address), &config_size);
#else
    /*for internal PMU*/
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_PUSH_PULL_SEND_POLLING, I2C_GET_SEND_ADDRESS(slave_address), &config_size);
#endif

    /*set data to fifo*/
    i2c_write_fifo(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), data, size);

    /*start i2c*/
    I2C_START(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));

    /* polling till transaction finish */
    while (0 == I2C_QUERY_TRANSACTION_FINISH_STATUS(PMIC_I2C_PORT_TO_GLOBAL(i2c_port))) {
    }

    /* read and status */
    transaction_status = i2c_get_transaction_status(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));

#ifndef BL_LOAD_ENABLE
    hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    if (I2C_TRANSACTION_SUCCESS != transaction_status) {

        log_hal_error("i2c pmic send error:%d\r\n", transaction_status);
        return (pmic_i2c_status_t)transaction_status;
    } else {
        return PMIC_I2C_STATUS_OK;
    }
}


pmic_i2c_status_t pmic_i2c_receive_polling(pmic_i2c_port_t i2c_port, uint8_t slave_address, uint8_t *buffer, uint32_t size)
{
    i2c_transaction_status_t transaction_status;
    i2c_transaction_size_t config_size;
    /* parameter check */
    if (PMIC_I2C_MASTER_MAX <= i2c_port) {
        return PMIC_I2C_STATUS_INVALID_PORT_NUMBER;
    }
    if (NULL == buffer || size > I2C_FIFO_DEPTH) {
        return PMIC_I2C_STATUS_INVALID_PARAMETER;
    }

#ifndef BL_LOAD_ENABLE
    hal_clock_enable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    /*mask interrupt*/
    I2C_MASK_INTERRUPT(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));

    /*config i2c hardware*/
    config_size.send_size = 0;
    config_size.receive_size = size;

#ifdef MTK_EXTERNAL_PMIC
    /*for external PMIC*/
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_OPEN_DRAIN_RECEIVE_POLLING, I2C_GET_RECEIVE_ADDRESS(slave_address), &config_size);
#else
    /*for internal PMU*/
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_PUSH_PULL_RECEIVE_POLLING, I2C_GET_RECEIVE_ADDRESS(slave_address), &config_size);
#endif
    /*start i2c*/
    I2C_START(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));

    /* polling till transaction finish */
    while (0 == I2C_QUERY_TRANSACTION_FINISH_STATUS(PMIC_I2C_PORT_TO_GLOBAL(i2c_port))) {
    }

    /* read and status */
    transaction_status = i2c_get_transaction_status(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));


    if (I2C_TRANSACTION_SUCCESS != transaction_status) {

#ifndef BL_LOAD_ENABLE
        hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

        return (pmic_i2c_status_t)transaction_status;
    } else {
        i2c_read_fifo(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), buffer, size);

#ifndef BL_LOAD_ENABLE
        hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

        return PMIC_I2C_STATUS_OK;
    }
}


pmic_i2c_status_t pmic_i2c_send_to_receive_polling(pmic_i2c_port_t i2c_port, pmic_i2c_send_to_receive_config_t *i2c_send_to_receive_config)
{
    i2c_transaction_status_t transaction_status;
    i2c_transaction_size_t config_size;
    if (PMIC_I2C_MASTER_MAX <= i2c_port) {
        return PMIC_I2C_STATUS_INVALID_PORT_NUMBER;
    }
    if (NULL == i2c_send_to_receive_config->send_data || NULL == i2c_send_to_receive_config->receive_buffer) {
        return PMIC_I2C_STATUS_INVALID_PARAMETER;
    }
    if (i2c_send_to_receive_config->send_length > I2C_FIFO_DEPTH || i2c_send_to_receive_config->receive_length > I2C_FIFO_DEPTH) {
        return PMIC_I2C_STATUS_INVALID_PARAMETER;
    }

#ifndef BL_LOAD_ENABLE
    hal_clock_enable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

    I2C_MASK_INTERRUPT(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));
    config_size.send_size = i2c_send_to_receive_config->send_length;
    config_size.receive_size = i2c_send_to_receive_config->receive_length;
#ifdef MTK_EXTERNAL_PMIC
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_OPEN_DRAIN_SEND_TO_RECEIVE_POLLING, I2C_GET_SEND_ADDRESS(i2c_send_to_receive_config->slave_address), &config_size);
#else
    i2c_config_hardware(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), I2C_TRANSACTION_PUSH_PULL_SEND_TO_RECEIVE_POLLING, I2C_GET_SEND_ADDRESS(i2c_send_to_receive_config->slave_address), &config_size);
#endif
    i2c_write_fifo(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), i2c_send_to_receive_config->send_data, i2c_send_to_receive_config->send_length);
    I2C_START(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));
    while (0 == I2C_QUERY_TRANSACTION_FINISH_STATUS(PMIC_I2C_PORT_TO_GLOBAL(i2c_port))) {
    }
    transaction_status = i2c_get_transaction_status(PMIC_I2C_PORT_TO_GLOBAL(i2c_port));
    if (I2C_TRANSACTION_SUCCESS != transaction_status) {

        log_hal_error("i2c pmic send_to_read error:%d\r\n", transaction_status);

#ifndef BL_LOAD_ENABLE
        hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

        return (pmic_i2c_status_t)transaction_status;
    } else {
        i2c_read_fifo(PMIC_I2C_PORT_TO_GLOBAL(i2c_port), i2c_send_to_receive_config->receive_buffer, i2c_send_to_receive_config->receive_length);

#ifndef BL_LOAD_ENABLE
        hal_clock_disable(g_i2c_pdn_table[PMIC_I2C_PORT_TO_GLOBAL(i2c_port)]);
#endif

        return PMIC_I2C_STATUS_OK;
    }
}

#endif

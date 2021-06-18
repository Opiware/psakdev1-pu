/* Copyright Statement:
 *
 */

#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "at_command.h"
#include "syslog.h"

#ifdef HAL_CHARGER_MODULE_ENABLED
#include "hal_charger.h"

#ifdef MTK_BUILD_SMT_LOAD
#include "cust_charging.h"
#endif

log_create_module(atci_charger, PRINT_LEVEL_INFO);

/* ===================================================*/
/* define */
/* ===================================================*/

/* ===================================================*/
/* function */
/* ===================================================*/

/* ===================================================*/
/* global variable */
/* ===================================================*/

/* ===================================================*/
// AT command handler
atci_status_t atci_cmd_hdlr_charger(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}};
    bool cable_in = false;
    int32_t batt_volt = 0;
    int32_t batt_temp = 0;
    int32_t char_curr = 0;
    int32_t char_volt = 0;

    LOG_I(atci_charger, "[atci_charger]start\r\n");

#ifndef MTK_BUILD_SMT_LOAD
    hal_charger_init();
    hal_charger_get_charger_detect_status(&cable_in);
    hal_charger_meter_get_charging_current(&char_curr);
#else
    hal_charger_init();
    hal_charger_get_charger_detect_status(&cable_in);
    if (cable_in) {
        /* Default pre-charging current. It depends on the battery specifications.
            The USBDL mode current level  = 16.8mV / R_SESNE */
        hal_charger_set_charging_current(16800 / CUST_R_SENSE);

        hal_charger_enable(true);
        LOG_I(atci_charger, "hal_charger_enable delay start\r\n");

        vTaskDelay(1000 / portTICK_RATE_MS);

        hal_charger_meter_get_charging_current(&char_curr);
        LOG_I(atci_charger, "hal_charger_enable delay end\r\n");
        hal_charger_enable(false);
    }
#endif

    hal_charger_meter_get_battery_voltage_sense(&batt_volt);
    hal_charger_meter_get_battery_temperature(&batt_temp);
    hal_charger_meter_get_charger_voltage(&char_volt);

    response.response_flag = 0;

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:
            /* AT+ECHAR=? */
            strcpy((char *)response.response_buf, "+ECHAR=(0,1)\r\nOK\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_READ:
            /* AT+ECHAR? */
            snprintf((char *)response.response_buf, ATCI_UART_TX_FIFO_BUFFER_SIZE, "+ECHAR: %d\r\n", (int)cable_in);
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_ACTIVE:
            /* AT+ECHAR */
            snprintf((char *)response.response_buf, ATCI_UART_TX_FIFO_BUFFER_SIZE, "+ECHAR:%d,%d,%d,%d\r\n", (int)batt_volt, (int)batt_temp, (int)char_curr, (int)char_volt);
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_EXECUTION:
        /* AT+ECHAR=... */

        default :
            // others are invalid command format
            LOG_I(atci_charger, "[atci_charger] mode=%d\r\n", parse_cmd->mode);
            strcpy((char *)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
    }

    return ATCI_STATUS_OK;
}
#endif /* HAL_CHARGER_MODULE_ENABLED */


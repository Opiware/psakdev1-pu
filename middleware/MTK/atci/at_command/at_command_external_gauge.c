/* Copyright Statement:
 *
 */

#ifdef MTK_EXTERNAL_GAUGE
#ifdef MTK_BUILD_SMT_LOAD
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "at_command.h"
#include "syslog.h"

#include "external_ntc.h"
#include "max17048.h"

log_create_module(atci_external_gauge, PRINT_LEVEL_INFO);

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
atci_status_t atci_cmd_hdlr_external_gauge(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}};
    int32_t batt_volt = 0;
    int32_t batt_temp = 0;

    max17048_init();

    LOG_I(atci_external_gauge, "[atci_external_gauge]start\r\n");
    batt_temp = external_ntc_get_temperature();
    batt_volt = max17048_get_vcell();

    response.response_flag = 0;

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:
            /* AT+EEXTGAUGE=? */
            strcpy((char *)response.response_buf, "+EEXTGAUGE=(0,1)\r\nOK\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_READ:
            /* AT+EEXTGAUGE? */
            snprintf((char *)response.response_buf, ATCI_UART_TX_FIFO_BUFFER_SIZE, "+EEXTGAUGE: %d\r\n", 1);
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_ACTIVE:
            /* AT+EEXTGAUGE */
            snprintf((char *)response.response_buf, ATCI_UART_TX_FIFO_BUFFER_SIZE, "+EEXTGAUGE:%d,%d\r\n", (int)batt_volt, (int)batt_temp);
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_EXECUTION:
        /* AT+EEXTGAUGE=... */

        default :
            // others are invalid command format
            LOG_I(atci_external_gauge, "[atci_external_gauge] mode=%d\r\n", parse_cmd->mode);
            strcpy((char *)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
    }

    return ATCI_STATUS_OK;
}
#endif /* MTK_EXTERNAL_GAUGE */
#endif /* MTK_BUILD_SMT_LOAD */

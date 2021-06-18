/* Copyright Statement:
 *
 */

#include "hal_clock.h"

#ifdef HAL_CLOCK_MODULE_ENABLED

#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "at_command.h"

#include "hal_clock_internal.h"

#define LOGE(fmt,arg...)   LOG_E(atcmd, "[clock]"fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atcmd, "[clock]"fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atcmd ,"[clock]"fmt,##arg)

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_clock(atci_parse_cmd_param_t *parse_cmd);

// AT command handler
atci_status_t atci_cmd_hdlr_clock(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response;

    LOGI("atci_cmd_hdlr_clock\r\n");
    memset(&response, 0, sizeof(response));

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:
            /* AT+CLOCK=? */
            strcpy((char *)response.response_buf, "AT+CLOCK=?\r\nTest OK\r\n");
            break;

        case ATCI_CMD_MODE_READ:
            /* AT+CLOCK? */
            clock_dump_info();
            snprintf((char *)response.response_buf, ATCI_UART_TX_FIFO_BUFFER_SIZE, "clock_dump_info\r\n");
            break;

        default :
            /* others are invalid command format */
            strcpy((char *)response.response_buf, "ERROR\r\n");
            break;
    }

    response.response_len = strlen((char *)response.response_buf);
    atci_send_response(&response);

    return ATCI_STATUS_OK;
}

#endif /* HAL_CLOCK_MODULE_ENABLED */


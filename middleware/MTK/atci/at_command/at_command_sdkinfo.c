/* Copyright Statement:
 *
 */

#include "verno.h"
#if defined(MTK_QUERY_SDK_VERSION) && defined(MTK_FW_VERSION)
// System head file
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// For Register AT command handler
#include "at_command.h"

#include "syslog.h"

#define LOGE(fmt,arg...)   LOG_E(atcmd, "ATCMD: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atcmd, "ATCMD: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atcmd ,"ATCMD: "fmt,##arg)

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_sdkinfo(atci_parse_cmd_param_t *parse_cmd);

// AT command handler
atci_status_t atci_cmd_hdlr_sdkinfo(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}};
    char *param = NULL;
    int  param1_val = -1;

    LOGW("atci_cmd_hdlr_sdkinfo\r\n");

    response.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_EXECUTION: // rec: AT+EVERINFO=<p1>  the handler need to parse the parameters
            LOGW("AT Executing...\r\n");
            //parsing the parameter
            param = strtok(parse_cmd->string_ptr, ",\n\r");
            param = strtok(parse_cmd->string_ptr, "AT+EVERINFO=");
	    if (param != NULL)
                param1_val = atoi(param);

            if (param != NULL && (param1_val == 0)) {

                // valid parameter, update the data and return "OK"
		snprintf((char *)response.response_buf, sizeof(response.response_buf), "+EVERINFO: %s\r\nOK\r\n", MTK_FW_VERSION);
		response.response_len = strlen((char *)response.response_buf);
            } else {
                // invalide parameter, return "ERROR"
                response.response_len = 0;
                response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of response buffer
            };

            atci_send_response(&response);
            param = NULL;
            break;
        default :
            strcpy((char *)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
    }
    return ATCI_STATUS_OK;
}

#endif //  defined(MTK_QUERY_SDK_VERSION) && defined(MTK_FW_VERSION)

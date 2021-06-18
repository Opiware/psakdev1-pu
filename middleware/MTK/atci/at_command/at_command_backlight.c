/* Copyright Statement:
 *
 */

// For Register AT command handler
//#include "atci.h"
// System head file
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "at_command.h"
#if defined(HAL_DISPLAY_PWM_MODULE_ENABLED) || defined(HAL_ISINK_MODULE_ENABLED)
#include "mt25x3_hdk_backlight.h"
/*
 * sample code
*/

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_backlight(atci_parse_cmd_param_t *parse_cmd);

/*
AT+EBLT=<op>	            |   "OK" or "ERROR"
AT+EBLT=?                     |   "+EBLT:(0, 1)"

URC:
+EBLT: <state>

*/
// AT command handler
atci_status_t atci_cmd_hdlr_backlight(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t resonse = {{0}};
#ifdef MTK_BUILD_SMT_LOAD
    char *param = NULL;
	int param1_val = 0;
#endif
    
    resonse.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+ELCM=?
            strcpy((char *)resonse.response_buf, "+EBLT:(\"0: off\",\"1: on\")\r\nOK\r\n");
            resonse.response_len = strlen((const char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;
#ifdef MTK_BUILD_SMT_LOAD
        case ATCI_CMD_MODE_EXECUTION: // rec: AT+EBLT=<op>  the handler need to parse the parameters
            param = strtok(parse_cmd->string_ptr, ",\n\r");
	        param = strtok(parse_cmd->string_ptr, "AT+EBLT=");
            param1_val = atoi(param);

            if (param != NULL && (param1_val >=0 && param1_val <= 1)) {
                if(param1_val == 0)	// off
                    bsp_backlight_deinit();
                else
                    bsp_backlight_init();

				// valid parameter, set baclight state and return "OK"
                sprintf((char *)resonse.response_buf,"+EBLT:%d\r\n", param1_val);
                // ATCI will help append "OK" at the end of resonse buffer
                resonse.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
                resonse.response_len = strlen((const char *)resonse.response_buf);
            } else {
                // invalide parameter, return "ERROR"
                strcpy((char *)resonse.response_buf, "ERROR\r\n");
                resonse.response_len = strlen((const char *)resonse.response_buf);
            };
            atci_send_response(&resonse);
			param = NULL;
            break;
#endif
        default :
            // others are invalid command format
            strcpy((char *)resonse.response_buf, "ERROR\r\n");
            resonse.response_len = strlen((const char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;
    }
    return ATCI_STATUS_OK;
}
#endif

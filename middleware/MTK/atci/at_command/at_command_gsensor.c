/* Copyright Statement:
 *
 */

// For Register AT command handler
// System head file

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "at_command.h"
#include "bma2x2.h"
#include "syslog.h"
#include "hal_gpio.h"

#if defined(__GNUC__)

log_create_module(atci_gsensor, PRINT_LEVEL_INFO);

#define LOGE(fmt,arg...)   LOG_E(atci_gsensor, "[bma255]"fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atci_gsensor, "[bma255]"fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atci_gsensor ,"[bma255]"fmt,##arg)

#define VENDOR_ID 0xFA

/*
 * sample code
*/

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_gsensor(atci_parse_cmd_param_t *parse_cmd);


// AT command handler
atci_status_t atci_cmd_hdlr_gsensor(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response;
#ifdef MTK_BUILD_SMT_LOAD 
    char *param = NULL;
    int  param1_val = -1;
#endif
    
    LOGI("atci_cmd_hdlr_keypad \r\n");

    memset(&response, 0, sizeof(atci_response_t));    
    response.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+EKEYURC=?
            strcpy((char *)response.response_buf, "+EGSENSOR=(0,1)\r\nOK\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
        case ATCI_CMD_MODE_EXECUTION: // rec: AT+EKEYURC=<op>  the handler need to parse the parameters
            LOGI("AT Executing...\r\n");
            #ifdef MTK_BUILD_SMT_LOAD 
            param = strtok(parse_cmd->string_ptr, ",\n\r");
            param = strtok(parse_cmd->string_ptr, "AT+EGSENSOR=");
            param1_val = atoi(param);
            if (param && (param1_val == 0)) {
                uint8_t data;
                /* valid parameter, update the data and return "OK"
                                param1_val = 0 :  I2C operation.
                */
                
                /* initialize vsm */
                bma255_init();
                /*get chip id*/
                bma2x2_read_reg(BMA2x2_CHIP_ID_REG, &data, BMA2x2_GEN_READ_WRITE_LENGTH);
                if (data != VENDOR_ID) {
                    LOGI("g sensor data not consistent...\r\n");
					response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
					response.response_len   = 0;
                } else {
                    LOGI("g sensor data are consistent...\r\n");
					response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
					response.response_len   = 0;                
                }
            } 
            else {            
                /*invalide parameter, return "ERROR"*/ 
                strcpy((char *)response.response_buf, "ERROR\r\n");
                response.response_len = strlen((char *)response.response_buf);
            }
            #else
            /*invalide parameter, return "ERROR"*/ 
            strcpy((char *)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            #endif
            atci_send_response(&response);
            break;
            
        default :
            /* others are invalid command format */ 
            strcpy((char *)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
    }
    return ATCI_STATUS_OK;
}
#else
/*--- Function ---*/
atci_status_t atci_cmd_hdlr_gsensor(atci_parse_cmd_param_t *parse_cmd);


// AT command handler
atci_status_t atci_cmd_hdlr_gsensor(atci_parse_cmd_param_t *parse_cmd)
{
	return ATCI_STATUS_OK;
}

#endif

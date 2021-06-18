/* Copyright Statement:
 *
 */

// For Register AT command handler
// System head file
#include "hal_feature_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "at_command.h"

#ifdef HAL_REG_MODULE_ENABLED

log_create_module(atci_reg, PRINT_LEVEL_INFO);

#define LOGE(fmt,arg...)   LOG_E(atci_reg, "[REG]"fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atci_reg, "[REG]"fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atci_reg ,"[REG]"fmt,##arg)

/*
 * sample code
*/

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_reg(atci_parse_cmd_param_t *parse_cmd);
static int htoi(char s[]);
/*
AT+EPMUREG=<op>                |   "OK"
AT+EPMUREG=?                |   "+EPMUREG=(0,1)","OK"


*/
// AT command handler
atci_status_t atci_cmd_hdlr_reg(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}};
    uint16_t read_value = 0;
    int input_addr = 0;
    int input_value = 0;
    char* end_pos = NULL;

    LOGI("atci_cmd_hdlr_reg \r\n");

    response.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+EREG=?
            strcpy((char*)response.response_buf, "+EREG=(0,1)\r\nOK\r\n");
            response.response_len = strlen((char*)response.response_buf);
            atci_send_response(&response);
            break;
        case ATCI_CMD_MODE_EXECUTION: // rec: AT+EREG=<op>  the handler need to parse the parameters
            if (strncmp(parse_cmd->string_ptr, "AT+EREG=0,", strlen("AT+EREG=0,")) == 0)
            {
                /*command: AT+EPMUREG=0,1234*/
                end_pos = strchr(parse_cmd->string_ptr, ',');
                end_pos ++;

                input_addr = htoi(end_pos);
                end_pos = NULL;
                LOGI("read register address:0x%x\r\n", input_addr);

                /* read data of input register address */
                read_value = *((volatile unsigned int *)input_addr);

                sprintf((char*)response.response_buf,"+EREG:0x%x,0x%x\r\n", input_addr, read_value);
                /* ATCI will help append "OK" at the end of resonse buffer */
                response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
                response.response_len = strlen((char*)response.response_buf);
            }
            else if (strncmp(parse_cmd->string_ptr, "AT+EREG=1,", strlen("AT+EREG=1,")) == 0)
            {
                /*command: AT+EPMUREG=1,1234,456*/

                char* mid_pos = NULL;
                char str[20] = {0};
                mid_pos = strchr(parse_cmd->string_ptr, ',');
                mid_pos ++;
                end_pos = strchr(mid_pos, ',');
                memcpy(str, mid_pos, strlen(mid_pos) - strlen(end_pos));
                input_addr = htoi(mid_pos);
                end_pos ++;
                input_value = htoi(end_pos);

                mid_pos = NULL;
                end_pos = NULL;
                LOGI("register address:0x%x, set register value:0x%x\r\n", input_addr, input_value);

                /* write input data to input register address*/
                *((volatile unsigned int *)input_addr) = input_value;

                /* ATCI will help append "OK" at the end of resonse buffer    */
                response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
                response.response_len = strlen((char*)response.response_buf);
            }
            else
            {
                /*invalide parameter, return "ERROR"*/
                strcpy((char*)response.response_buf, "ERROR\r\n");
                response.response_len = strlen((char*)response.response_buf);
            };

            atci_send_response(&response);

            break;

        default :
            /* others are invalid command format */
            strcpy((char*)response.response_buf, "ERROR\r\n");
            response.response_len = strlen((char*)response.response_buf);
            atci_send_response(&response);
            break;
    }
    return ATCI_STATUS_OK;
}


// change the data with hex type in string to data with dec type
int htoi(char s[])
{
    int i;
    int n = 0;
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))
    {
        i = 2;
    }
    else
    {
        i = 0;
    }
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)
    {
        if (tolower((unsigned char)s[i]) > '9')
        {
            n = 16 * n + (10 + tolower((unsigned char)s[i]) - 'a');
        }
        else
        {
            n = 16 * n + (tolower((unsigned char)s[i]) - '0');
        }
    }
    return n;
}

#endif

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
#ifdef HAL_DISPLAY_LCD_MODULE_ENABLED
#include "bsp_lcd.h"
#include "mt25x3_hdk_lcd.h"
/*
 * sample code
*/

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_lcm(atci_parse_cmd_param_t *parse_cmd);

/*
AT+ELCM=<op>	            |   "OK" or "ERROR"
AT+ELCM=?                     |   "+ELCM:("red","green","blue","WB")","OK"

URC:
+ELCM: <color>

*/
// AT command handler
atci_status_t atci_cmd_hdlr_lcm(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t resonse = {{0}};
#ifdef MTK_BUILD_SMT_LOAD
    char *param = NULL;
	int param1_val = 0;
#endif
    printf("atci_cmd_hdlr_lcm \r\n");
    
    resonse.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+ELCM=?
            strcpy((char *)resonse.response_buf, "+ELCM:(\"0: red\",\"1: green\",\"2: blue\",\"3: WB\",\"10: black\",\"11: white\",\"12: WB\")\r\nOK\r\n");
            resonse.response_len = strlen((const char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;
#ifdef MTK_BUILD_SMT_LOAD
        case ATCI_CMD_MODE_EXECUTION: // rec: AT+ELCM=<op>  the handler need to parse the parameters
            param = strtok(parse_cmd->string_ptr, ",\n\r");
	        param = strtok(parse_cmd->string_ptr, "AT+ELCM=");
            param1_val = atoi(param);

            if (param != NULL && ((param1_val >=0 && param1_val <= 3) || (param1_val >= 10 && param1_val <= 12))) {
				switch (param1_val)
				{
					case 0:
						bsp_lcd_clear_screen(0xF800);
						break;
					case 1:
						bsp_lcd_clear_screen(0x7E0);
						break;
					case 2:
						bsp_lcd_clear_screen(0x1F);
						break;
					case 3:
						bsp_lcd_clear_screen_bw();
						break;
					case 10:
						bsp_lcd_clear_screen(0);
						break;
					case 11:
						bsp_lcd_clear_screen(0xFFFF);
						break;
					case 12:
						bsp_lcd_clear_screen_bw();
						break;
					default:
						break;
				}
				// valid parameter, set LCM color and return "OK"
                sprintf((char *)resonse.response_buf,"+ELCM:%d\r\n", param1_val);
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

/* Copyright Statement:
 *
 */
// For Register AT command handler
// System head file

#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "at_command.h"
#include <stdlib.h>
#include "hal_log.h"

#ifdef MTK_CTP_ENABLE
#include "ctp.h"
#include "bsp_ctp.h"


/* CTP simulate cmd: AT+ECTP=(<X1>,<Y1>):<action_index>;(<X1>,<Y1>):<action_index>, for example:
 *
 *	 AT+ECTP=(20,30):1;(100,500):1    //press point of (20,30) and (100,500)
 *	 AT+ECTP=(20,30):0                //release point of (20,30)
 * */

/*--- Function ---*/
atci_status_t  atci_cmd_hdlr_ctp_simulate(atci_parse_cmd_param_t *parse_cmd);

extern bool ctp_calibrate_coordinate(bsp_ctp_multiple_event_t *tp_event);
extern void touch_panel_multiple_touch_data_push(bsp_ctp_multiple_event_t *push_event);

/* AT command handler  */
atci_status_t atci_cmd_hdlr_ctp_simulate(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t resonse = {{0}};
    char *param1 = NULL;
    char *param2 = NULL;
    char *param3 = NULL;
    char *param4 = NULL;
    char *param5 = NULL;
    char *param6 = NULL;
    char *param_temp = NULL;
    //char *param7 = NULL;
    bsp_ctp_multiple_event_t push_event;
    int i;
    int pointer_count = 1;
    int status_flag = 0;

    resonse.response_flag = 0;      /*  Command Execute Finish.  */

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:
            strcpy((char *)resonse.response_buf, "AT+ECTP=(<X1>,<Y1>):<action_index>;(<X1>,<Y1>):<action_index>\r\n");
            resonse.response_len = strlen((char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;

        case ATCI_CMD_MODE_EXECUTION:
            if (ctp_config_info.is_external_initialized != false) {
                strcpy((char *)resonse.response_buf, "OK\r\n");
                resonse.response_len = strlen((char *)resonse.response_buf);
                atci_send_response(&resonse);

                param1 = strtok(parse_cmd->string_ptr, ";");
                param2 = strtok(NULL, ";");
                if ('(' == param2[0]) {              /* parse second point. */
                    param3 = strtok(param2, ":");
                    param4 = strtok(NULL, ":");
                    push_event.points[1].event = (bsp_ctp_event_status_t)(atoi(param4));  /* pointer 2 status */
                    param5 = strtok(param3, ",");
                    param6 = strtok(NULL, ",");

                    param_temp = ++param5;
                    push_event.points[1].x = atoi(param_temp);
                    push_event.points[1].y = atoi(strtok(param6, ")"));
                    pointer_count = 2;
                }

                param3 = strtok(param1, ":");
                param4 = strtok(NULL, ":");
                push_event.points[0].event = (bsp_ctp_event_status_t)(atoi(param4));  /* pointer 1 status. */
                param5 = strtok(param3, ",");
                param6 = strtok(NULL, ",");
                param3 = strtok(param5, "(");
                param_temp = strtok(NULL, "(");
                push_event.points[0].x = atoi(param_temp);
                push_event.points[0].y = atoi(strtok(param6, ")"));

                ctp_mask_eint_interrupt();
                push_event.time_stamp = ctp_get_time_us();
                push_event.model = pointer_count;
                push_event.padding = CTP_PATTERN;
                for (i = 0; i < pointer_count; i++) { /* check if all the pointers status is released. */
                    if (push_event.points[i].event != CTP_PEN_UP) {
                        ctp_context.state = CTP_DOWN;
                        status_flag = 1;
                        break;
                    }
                }
                if (!status_flag) { /* all the points is released. */
                    if (ctp_context.state == CTP_DOWN) {
                        ctp_context.state = CTP_UP;
                    } else {
                        strcpy((char *)resonse.response_buf, "UP to UP, BYPASS\r\n");
                        resonse.response_len = strlen((char *)resonse.response_buf);
                        atci_send_response(&resonse);
                        return ATCI_STATUS_OK;
                    }
                }
                ctp_calibrate_coordinate(&push_event);
                touch_panel_multiple_touch_data_push(&push_event);
                ctp_unmask_eint_interrupt();
            } else {
                strcpy((char *)resonse.response_buf, "Error:CTP not initialized!\r\n");
                resonse.response_len = strlen((char *)resonse.response_buf);
                atci_send_response(&resonse);
                return ATCI_STATUS_OK;
            }
            break;
        default :
            /* others are invalid command format */
            strcpy((char *)resonse.response_buf, "ERROR\r\n");
            resonse.response_len = strlen((char *)resonse.response_buf);
            atci_send_response(&resonse);
            break;
    }
    return ATCI_STATUS_OK;
}
#endif



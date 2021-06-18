/* Copyright Statement:
 *
 */

// For Register AT command handler
#include "at_command.h"
#include <string.h>
#include <stdio.h>
//#include "syslog.h"


extern void test_framework_deinit_framework(void);
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
	#pragma weak test_framework_deinit_framework = test_framework_deinit_simulator
#endif

/*--- Function ---*/
// AT command handler
atci_status_t atci_cmd_hdlr_testframework(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t resonse = {{0}};
    //LOGW("atci_cmd_hdlr_testframework \r\n");
    
   // LOGW("atci_cmd_hdlr_testframework mode = %d\r\n",parse_cmd->mode);

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+TESTFRAMEWORK=?
        	test_framework_deinit_framework();
            strcpy((char *)(resonse.response_buf), "OK\r\n");
            resonse.response_len = strlen((char *)(resonse.response_buf));
            atci_send_response(&resonse);
            break;      
        default :
            /* others are invalid command format */ 
            strcpy((char *)(resonse.response_buf), "ERROR\r\n");
            resonse.response_len = strlen((char *)(resonse.response_buf));
            atci_send_response(&resonse);
            break;
    }
    return ATCI_STATUS_OK;
}

void test_framework_deinit_simulator () {
	//LOGW("test_framework_deinit_simulator is called\r\n");

}


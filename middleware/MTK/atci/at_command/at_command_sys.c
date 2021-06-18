/* Copyright Statement:
 *
 */

#include "verno.h"
#if defined(MTK_FW_VERSION) && ((PRODUCT_VERSION == 7687) || (PRODUCT_VERSION == 7697) || (PRODUCT_VERSION == 7686) || (PRODUCT_VERSION == 7682) || (PRODUCT_VERSION == 5932))
// System head file
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// For Register AT command handler
#include "at_command.h"

#include "syslog.h"
#include "connsys_util.h"
#include "hal_wdt.h"

#define LOGE(fmt,arg...)   LOG_E(atcmd, "ATCMD: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atcmd, "ATCMD: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atcmd ,"ATCMD: "fmt,##arg)

/*--- Function ---*/
atci_status_t atci_cmd_hdlr_sys(atci_parse_cmd_param_t *parse_cmd);

// AT command handler
atci_status_t atci_cmd_hdlr_sys(atci_parse_cmd_param_t *parse_cmd)
{    
    atci_response_t response = {{0}};
    char fw_ver[32];
    char patch_ver[32];
    hal_wdt_config_t wdt_config;

    memset(fw_ver, 0, 32);
    memset(patch_ver, 0, 32);

    LOGI("atci_cmd_hdlr_sys\r\n");

    response.response_flag = 0; // Command Execute Finish.

    switch (parse_cmd->mode) {
        case ATCI_CMD_MODE_TESTING:    // rec: AT+SYS=?
            LOGI("AT SYS test OK.\n");
            strcpy((char *)response.response_buf, "+SYS:(VER)\r\nOK\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_READ:    // rec: AT+SYS?
            LOGI("AT SYS Read done.\n");
            snprintf((char *)response.response_buf, sizeof(response.response_buf), "+SYS:VER\r\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_ACTIVE:  // rec: AT+SYS
            LOGI("AT Active OK.\n");
            // assume the active mode is invalid and we will return "ERROR"
            strcpy((char *)response.response_buf, "+SYS\r\nOK\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;

        case ATCI_CMD_MODE_EXECUTION: // rec: AT+SYS=<p1>  the handler need to parse the parameters
            LOGI("AT Executing...\r\n");

            if (strstr((char *)parse_cmd->string_ptr, "AT+SYS=VER") != NULL) {
                // valid parameter, update the data and return "OK"
                connsys_util_get_n9_fw_ver(fw_ver);
                connsys_util_get_ncp_patch_ver(patch_ver);
                //snprintf((char *)response.response_buf, sizeof(response.response_buf),
                //         "+SYS=VER:CM4 Image Ver: %s\r\nN9 Image Ver: %s\r\nHW Patch Ver: %s\r\nOK\r\n",
                //        MTK_FW_VERSION, fw_ver, patch_ver);
				snprintf((char *)response.response_buf, sizeof(response.response_buf),
                         "+SYS=VER:CM4 Image Ver: %s\r\nN9 Image Ver: %s\r\nOK\r\n", MTK_FW_VERSION, fw_ver);

                response.response_len = strlen((char *)response.response_buf);
            } else if (strstr((char *)parse_cmd->string_ptr, "AT+SYS=REBOOT") != NULL) {
                // valid parameter, update the data and return "OK"
#if defined(MTK_FW_VERSION) && (PRODUCT_VERSION != 7697)
                wdt_config.mode = HAL_WDT_MODE_RESET;
#else
                // MT7697 has WDT reset issue
                wdt_config.mode = HAL_WDT_MODE_INTERRUPT;               
#endif
                wdt_config.seconds = 1;
                hal_wdt_init(&wdt_config);
                hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
                snprintf((char *)response.response_buf, sizeof(response.response_buf),
                         "+SYS=REBOOT:OK\r\n");

                response.response_len = strlen((char *)response.response_buf);
            } else {
                // invalide parameter, return "ERROR"
                response.response_len = 0;
                response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of response buffer
            };

            atci_send_response(&response);
            break;
        default :
            strcpy((char *)response.response_buf, "+SYS\r\nERROR\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_send_response(&response);
            break;
    }
    return ATCI_STATUS_OK;
}

#endif //  defined(MTK_QUERY_SDK_VERSION) && defined(MTK_FW_VERSION)

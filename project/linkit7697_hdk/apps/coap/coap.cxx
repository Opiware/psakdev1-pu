/*----------------------------------------------------------------------------*/
Z:\_shares1\github\psakdev1-pu\project\linkit7697_hdk\apps\coap\src\main.c
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "sys_init.h"
#include "wifi_api.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "ethernetif.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"
#include "portmacro.h"
#include "wifi_lwip_helper.h"
#include "task_def.h"
#include "syslog.h"

/**
  * @brief  Main program
  * @param  None
  * @retval int
  */
int main(void)
{
    /* Do system initialization, eg: hardware, nvdm, logging and random seed. */
    system_init();

    /* system log initialization.
        * This is the simplest way to initialize system log, that just inputs three NULLs
        * as input arguments. User can use advanved feature of system log along with NVDM.
        * For more details, please refer to the log dev guide under /doc folder or projects
        * under project/mtxxxx_hdk/apps/.
        */
    log_init(NULL, NULL, NULL);
    |
    Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
    void log_init(syslog_save_fn save, syslog_load_fn load, log_control_block_t  **entries);
    Z:\_shares1\github\psakdev1-pu\kernel\service\src\syslog.c
    void log_init(syslog_save_fn         save,
                  |
                  Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
                  typedef void (*syslog_save_fn)(const syslog_config_t *config);

                  syslog_load_fn         load,
                  |
                  Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
                  typedef uint32_t (*syslog_load_fn)(syslog_config_t *config);

                  log_control_block_t  **entries)

    LOG_I(coap_example, "start to create task.");
    |
    Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
    #define LOG_I(_module, _message, ...) \

    /* User initial the parameters for wifi initial process,  system will determin which wifi operation mode
        * will be started , and adopt which settings for the specific mode while wifi initial process is running
        */
    wifi_config_t config = {0};
    config.opmode = WIFI_MODE_STA_ONLY;
    strcpy((char *)config.sta_config.ssid, WIFI_SSID);
    strcpy((char *)config.sta_config.password, WIFI_PASSWORD);
    config.sta_config.ssid_length = strlen(WIFI_SSID);
    config.sta_config.password_length = strlen(WIFI_PASSWORD);

    /* Initialize wifi stack and register wifi init complete event handler,
        * notes:  the wifi initial process will be implemented and finished while system task scheduler is running.
        */
    wifi_init(&config, NULL);

    /* Tcpip stack and net interface initialization,  dhcp client, dhcp server process initialization. */
    lwip_network_init(config.opmode);
    lwip_net_start(config.opmode);


    /* Create a user task for demo when and how to use wifi config API  to change WiFI settings,
        * Most WiFi APIs must be called in task scheduler, the system will work wrong if called in main(),
        * For which API must be called in task, please refer to wifi_api.h or WiFi API reference.
        * xTaskCreate(user_wifi_app_entry,
        *       UNIFY_USR_DEMO_TASK_NAME,
        *       UNIFY_USR_DEMO_TASK_STACKSIZE / 4,
        *       NULL, UNIFY_USR_DEMO_TASK_PRIO, NULL);
        */
    if (pdPASS != xTaskCreate(user_entry,
                              USER_ENTRY_TASK_NAME,
                              USER_ENTRY_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                              NULL,
                              USER_ENTRY_TASK_PRIO,
                              NULL)) {
        LOG_E(coap_example, "create user task fail");
        |
        Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
        #define LOG_E(_module, _message,...) \

        return -1;
    }

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
        * will never be reached.  If the following line does execute, then there was
        * insufficient FreeRTOS heap memory available for the idle and/or timer tasks
        * to be created.  See the memory management section on the FreeRTOS web site
        * for more details.
        */
    for ( ;; );
}
/*----------------------------------------------------------------------------*/
coap_log();  _log

coap_get_log_level()
|
Z:\_shares1\github\psakdev1-pu\middleware\third_party\libcoap\include\coap\debug.h
coap_log_t coap_get_log_level();

log_uart_init()
|
Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
hal_uart_status_t log_uart_init(hal_uart_port_t port);

log_create_module()
|
Z:\_shares1\github\psakdev1-pu\kernel\service\inc\syslog.h
#define log_create_module(_module, _level) \

coap_set_log_level()
|
Z:\_shares1\github\psakdev1-pu\middleware\third_party\libcoap\include\coap\debug.h
void coap_set_log_level(coap_log_t level);

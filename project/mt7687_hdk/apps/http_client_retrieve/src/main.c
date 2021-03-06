/* Copyright Statement:
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "task_def.h"
#include "syslog.h"

#include "sys_init.h"
#include "wifi_api.h"
#include "wifi_lwip_helper.h"
#include "httpclient.h"

#define WIFI_SSID                ("SQA_TEST_AP")
#define WIFI_PASSWORD            ("77777777")

#define BUF_SIZE        (1024 * 1)
#define HTTP_GET_URL    "http://www.aliyun.com/"

log_create_module(http_client_retrieve_example, PRINT_LEVEL_INFO);

/**
  * @brief      Http client connect to test server and test "retrieve" function.
  * @param      None
  * @return     None
  */
void httpclient_test_retrieve(void)
{
    char *get_url = HTTP_GET_URL;
    HTTPCLIENT_RESULT ret;    
    httpclient_t client = {0};
    char *buf;
    httpclient_data_t client_data = {0};
    int count = 0;

    buf = pvPortMalloc(BUF_SIZE);
    if (buf == NULL) {            
        LOG_I(http_client_retrieve_example, "memory malloc failed.");
        return;
    }

    // Connect to server
    ret = httpclient_connect(&client, get_url);

    if (!ret) {        
        client_data.response_buf = buf;
        client_data.response_buf_len = BUF_SIZE;

        // Send request to server
        ret = httpclient_send_request(&client, get_url, HTTPCLIENT_GET, &client_data);
        if (ret < 0)            
			goto fail;
        
        do {            
            // Receive response from server
            ret = httpclient_recv_response(&client, &client_data);
            if (ret < 0)
                goto fail;
            count += strlen(client_data.response_buf);
            LOG_I(http_client_retrieve_example, "data received: %s", client_data.response_buf);
        } while (ret == HTTPCLIENT_RETRIEVE_MORE_DATA);
        
        LOG_I(http_client_retrieve_example, "total length: %d", client_data.response_content_len);
    }

fail:
    // Close http connection
    httpclient_close(&client);
    vPortFree(buf);

    // Print final log
    if (ret >= 0)    
        LOG_I(http_client_retrieve_example, "example project test success.");
    else        
        LOG_I(http_client_retrieve_example, "example project test fail, reason:%d.", ret);
}

/**
  * @brief      Create a task for http client retrieve example
  * @param[in]  void *args: Not used
  * @return     None
  */
void app_entry(void *args)
{
    lwip_net_ready();

    // Httpclient "retrieve" feature test
    httpclient_test_retrieve();

    while (1) {        
        vTaskDelay(1000 / portTICK_RATE_MS); // release CPU
    }
}

/**
  * @brief      Main program
  * @param      None
  * @return     None
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

    LOG_I(http_client_retrieve_example, "FreeRTOS Running");

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
    xTaskCreate(app_entry, APP_TASK_NAME, APP_TASK_STACKSIZE/sizeof(portSTACK_TYPE), NULL, APP_TASK_PRIO, NULL);


    /* Call this function to indicate the system initialize done. */
    SysInitStatus_Set();

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



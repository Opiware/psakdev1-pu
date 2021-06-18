/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* device.h includes */
#include "mt7687.h"
#include "system_mt7687.h"

#include "sys_init.h"
#include "task_def.h"

#include "wifi_lwip_helper.h"
#include "wifi_api.h"

#include "hal_sleep_manager.h"

/* Create the log control block as user wishes. Here we use 'sleep_manager' as module name.
 * User needs to define their own log control blocks as project needs.
 * Please refer to the log dev guide under /doc folder for more details. */
static void vTestTask( void *pvParameters );
log_create_module(sleep_manager, PRINT_LEVEL_INFO);

/**
* @brief       Task main function
* @param[in]   pvParameters: Pointer that will be used as the parameter for the task being created.
* @return      None.
*/
static void vTestTask( void *pvParameters )
{
    uint32_t sleep_time_ms = 3000;
    LOG_I(sleep_manager, "sleep manager example:\n");

    while (1) {
        LOG_I(sleep_manager, "enter sleep mode for 3 sec\n");
        hal_sleep_manager_set_sleep_time(sleep_time_ms);
        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
        is accounted for as best it can be, but using the tickless mode will
        inevitably result in some tiny drift of the time maintained by the
        kernel with respect to calendar time. */
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_SLEEP);
        /* Resume SysTick */
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        LOG_I(sleep_manager, "exit from sleep mode\n");

        LOG_I(sleep_manager, "enter legacy sleep mode for 3 sec\n");
        hal_sleep_manager_set_sleep_time(sleep_time_ms);
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_LEGACY_SLEEP);
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        LOG_I(sleep_manager, "exit from legacy sleep mode\n");
    }
    //vTaskDelete(NULL);
}

/**
* @brief       Main function
* @param[in]   None.
* @return      None.
*/
int main(void)
{
    /* Do system initialization, eg: hardware, nvdm and random seed. */
    system_init();

    /* system log initialization.
     * This is the simplest way to initialize system log, that just inputs three NULLs
     * as input arguments. User can use advanved feature of system log along with NVDM.
     * For more details, please refer to the log dev guide under /doc folder or projects
     * under project/mtxxxx_hdk/apps/.
     */
    log_init(NULL, NULL, NULL);

    LOG_I(sleep_manager, "start to create task.\n");

    /* User initial the parameters for wifi initial process,  system will determin which wifi operation mode
     * will be started , and adopt which settings for the specific mode while wifi initial process is running*/
    wifi_config_t config = {0};
    config.opmode = WIFI_MODE_STA_ONLY;
    strcpy((char *)config.sta_config.ssid, (const char *)"MTK_STA");
    strcpy((char *)config.sta_config.password, (const char *)"12345678");
    config.sta_config.ssid_length = strlen((const char *)config.sta_config.ssid);
    config.sta_config.password_length = strlen((const char *)config.sta_config.password);


    /* Initialize wifi stack and register wifi init complete event handler,
     * notes:  the wifi initial process will be implemented and finished while system task scheduler is running.*/
    wifi_init(&config, NULL);

    /* Tcpip stack and net interface initialization,  dhcp client, dhcp server process initialization*/
    lwip_network_init(config.opmode);
    lwip_net_start(config.opmode);

    /* As for generic HAL init APIs like: hal_uart_init(), hal_gpio_init() and hal_spi_master_init() etc,
     * user can call them when they need, which means user can call them here or in user task at runtime.
     */

    /* Create a user task for demo when and how to use wifi config API to change WiFI settings,
    Most WiFi APIs must be called in task scheduler, the system will work wrong if called in main(),
    For which API must be called in task, please refer to wifi_api.h or WiFi API reference.
    xTaskCreate(user_wifi_app_entry,
                UNIFY_USR_DEMO_TASK_NAME,
                UNIFY_USR_DEMO_TASK_STACKSIZE / 4,
                NULL, UNIFY_USR_DEMO_TASK_PRIO, NULL);
    user_wifi_app_entry is user's task entry function, which may be defined in another C file to do application job.
    UNIFY_USR_DEMO_TASK_NAME, UNIFY_USR_DEMO_TASK_STACKSIZE and UNIFY_USR_DEMO_TASK_PRIO should be defined
    in task_def.h. User needs to refer to example in task_def.h, then makes own task MACROs defined.
    */
    xTaskCreate(vTestTask, "sleep_manager_example", 192, NULL, TASK_PRIORITY_LOW, NULL);


    /* Call this function to indicate the system initialize done. */
    SysInitStatus_Set();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for( ;; );
}


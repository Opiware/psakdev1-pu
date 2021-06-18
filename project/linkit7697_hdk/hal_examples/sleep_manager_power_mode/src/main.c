/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes. */
#include "hal.h"

/* device.h includes */
#include "hal_pinmux_define.h"
#include "system_mt7687.h"
#include "top.h"

#include "hal_sleep_manager.h"

/* Create the log control block as user wishes. Here we use 'sleep_manager' as module name.
 * User needs to define their own log control blocks as project needs.
 * Please refer to the log dev guide under /doc folder for more details. */
static void vTestTask(void);


#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the HAL_UART_0 one at a time */
    hal_uart_put_char(HAL_UART_0, ch);
    return ch;
}

/**
*@brief Set pinmux to UART and initialize UART hardware initialization for logging.
*@param None.
*@return None.
*/
static void plain_log_uart_init(void)
{
    hal_uart_config_t uart_config;
    /* Set Pinmux to UART */
    hal_pinmux_set_function(HAL_GPIO_0, HAL_GPIO_0_UART1_RTS_CM4);
    hal_pinmux_set_function(HAL_GPIO_1, HAL_GPIO_1_UART1_CTS_CM4);
    hal_pinmux_set_function(HAL_GPIO_2, HAL_GPIO_2_UART1_RX_CM4);
    hal_pinmux_set_function(HAL_GPIO_3, HAL_GPIO_3_UART1_TX_CM4);

    /* COM port settings */
    uart_config.baudrate = HAL_UART_BAUDRATE_115200;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.parity = HAL_UART_PARITY_NONE;
    hal_uart_init(HAL_UART_0, &uart_config);
}
/**
*@brief Configure and initialize the systerm clock.
*@param None.
*@return None.
*/
static void SystemClock_Config(void)
{
    top_xtal_init();
}

/**
*@brief  Initialize the periperal driver in this function. In this example, we initialize UART drivers.
*@param None.
*@return None.
*/
static void prvSetupHardware(void)
{
    /* Peripherals initialization */
    plain_log_uart_init();
}

/**
* @brief       Task main function
* @param[in]   pvParameters: Pointer that will be used as the parameter for the task being created.
* @return      None.
*/
static void vTestTask(void)
{
    uint32_t sleep_time_ms = 3000;
    printf("sleep manager example:\r\n");

    while (1) {
        printf("enter sleep mode for 3 sec\r\n");
        hal_sleep_manager_set_sleep_time(sleep_time_ms);
        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
        is accounted for as best it can be, but using the tickless mode will
        inevitably result in some tiny drift of the time maintained by the
        kernel with respect to calendar time. */
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_SLEEP);
        /* Resume SysTick */
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        printf("exit from sleep mode\r\n");

        printf("enter legacy sleep mode for 3 sec\r\n");
        hal_sleep_manager_set_sleep_time(sleep_time_ms);
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_LEGACY_SLEEP);
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        printf("exit from legacy sleep mode\r\n");
    }
}

/**
* @brief       Main function
* @param[in]   None.
* @return      None.
*/
int main(void)
{
    /* Configure system clock */
    SystemClock_Config();

    /* Configure the hardware */
    prvSetupHardware();

    /* Enable I,F bits */
    __enable_irq();
    __enable_fault_irq();

    /* Add your application code here */
    printf("\r\n\r\n");
    /* The output UART used by printf is set by plain_log_uart_init() */
    printf("welcome to main()\r\n");
    printf("\r\n\r\n");

    vTestTask();

    for( ;; );
}


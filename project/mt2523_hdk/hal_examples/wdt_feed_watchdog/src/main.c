/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the HAL_UART_2 one at a time */
    hal_uart_put_char(HAL_UART_2, ch);
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
    hal_gpio_init(HAL_GPIO_0);
    hal_gpio_init(HAL_GPIO_1);
    hal_pinmux_set_function(HAL_GPIO_0, HAL_GPIO_0_U2RXD);
    hal_pinmux_set_function(HAL_GPIO_1, HAL_GPIO_1_U2TXD);

    /* COM port settings */
    uart_config.baudrate = HAL_UART_BAUDRATE_115200;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.parity = HAL_UART_PARITY_NONE;
    hal_uart_init(HAL_UART_2, &uart_config);
}
/**
*@brief Configure and initialize the systerm clock. In this example, we invoke hal_clock_init to initialize clock driver and clock gates.
*@param None.
*@return None.
*/
static void SystemClock_Config(void)
{
    hal_clock_init();
}
/**
*@brief  Initialize the periperal driver in this function. In this example, we initialize UART, Flash, and NVIC drivers.
*@param None.
*@return None.
*/
static void prvSetupHardware(void)
{
    /* Peripherals initialization */
    plain_log_uart_init();
    hal_flash_init();
    hal_nvic_init();
}

/**
*@brief  Example for wdt feed watchdog.
*@param None.
*@return None.
*/
static void wdt_feed_watchdog_example()
{
    hal_wdt_config_t wdt_init;
    wdt_init.mode = HAL_WDT_MODE_RESET;
    wdt_init.seconds = 4;
    hal_wdt_status_t my_ret;

    printf("WDT test begins...\r\n");

    my_ret = hal_wdt_init(&wdt_init);
    if (HAL_WDT_STATUS_OK != my_ret) {
        printf("WDT initialization error.\r\n");
        return;
    }
    my_ret = hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
    if (HAL_WDT_STATUS_OK != my_ret) {
        printf("WDT enable error.\r\n");
        return;
    }

    hal_gpt_delay_ms(1000);

    hal_wdt_feed(HAL_WDT_FEED_MAGIC);

    printf("WDT will reset in 3 seconds...\r\n");

}

int main(void)
{
    /* Configure system clock */
    SystemClock_Config();

    SystemCoreClockUpdate();

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

    wdt_feed_watchdog_example();

    for (;;);
}


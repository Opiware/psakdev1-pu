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
uint32_t count1;
uint32_t handle;
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
*@brief Configure and initialize UART hardware initialization for logging.
*@param None.
*@return None.
*/
static void log_uart_init(void)
{
    hal_uart_config_t uart_config;
    /* gpio config for uart2 */
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
*@brief  Initialize the peripheral driver in this function. In this example, we initialize UART, Flash, and NVIC drivers.
*@param None.
*@return None.
*/
static void prvSetupHardware(void)
{
    /* Peripherals initialization */
    log_uart_init();
    hal_flash_init();
    hal_nvic_init();
}
/**
*@brief User defined callback of GPT.
*@param[in] parameter: pointer to the data that user will use in this callback.
*@return None.
*/
static void gpt_callback(void *parameter)
{
    uint32_t count;
    uint32_t count2;
    uint32_t duration_time;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count2);
    hal_gpt_get_duration_count(count1, count2, &count);
    duration_time = (uint32_t)(((uint64_t)((uint64_t)count * 1000)) / 32768);
    hal_gpt_sw_free_timer(handle);
    printf("The original set of timeout time is 10 ms, and the detected duration time ms:%d ms\r\n", (int)duration_time);
}

/**
*@brief Start the software timer, which is working at oneshot mode.
*@param None.
*@return None.
*/
static void hal_gpt_sw_interrupt_oneshot_mode_example(void)
{
    hal_gpt_status_t         ret;
    if (HAL_GPT_STATUS_OK != hal_gpt_sw_get_timer(&handle)) {
        printf("hal_gpt_sw_get_timer error!");
        return;
    }
    ret = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count1);
    if (ret != HAL_GPT_STATUS_OK) {
        printf("hal_gpt_get_free_run_count return = %d error!\r\n", ret);
        return;
    }
    if (HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(handle, 10, gpt_callback, NULL)) {
        printf("hal_gpt_sw_start_timer_ms error!");
        return;
    }
}

int main(void)
{
    /* Configure system clock */
    SystemClock_Config();

    SystemCoreClockUpdate();

    /* Configure the hardware */
    prvSetupHardware();

    /* enable NVIC interrupts and fault exception*/
    __enable_irq();
    __enable_fault_irq();

    printf("\r\n\r\n");/* The output UART used by printf is set by log_uart_init() */
    printf("welcome to main()\r\n");
    printf("\r\n\r\n");

    hal_gpt_sw_interrupt_oneshot_mode_example();

    while (1);
}


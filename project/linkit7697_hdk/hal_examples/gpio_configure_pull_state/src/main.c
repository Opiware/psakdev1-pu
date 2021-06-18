/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"
#include "system_mt7687.h"
#include "top.h"

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
    /* e.g. write a character to the HAL_UART_0 one at a time */
    hal_uart_put_char(HAL_UART_0, ch);
    return ch;
}

/**
*@brief Set pinmux to UART and initialize UART hardware initialization for logging.
*@param None.
*@return None.
*/
static void log_uart_init(void)
{
    hal_uart_config_t uart_config;
    /* Set Pinmux to UART */
    hal_pinmux_set_function(HAL_GPIO_0, HAL_GPIO_0_UART1_RTS_CM4);
    hal_pinmux_set_function(HAL_GPIO_1, HAL_GPIO_1_UART1_CTS_CM4);
    hal_pinmux_set_function(HAL_GPIO_2, HAL_GPIO_2_UART1_RX_CM4);
    hal_pinmux_set_function(HAL_GPIO_3, HAL_GPIO_3_UART1_TX_CM4);

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
    log_uart_init();
}


/**
*@brief  Configure the GPIO pull state to pull-up and to pull-down. Verify the pull states by inputs.
*@param None.
*@return None.
*/
static void gpio_configure_pull_state_example()
{

    hal_gpio_data_t data_pull_up;
    hal_gpio_data_t data_pull_down;
    hal_gpio_status_t ret;
    hal_pinmux_status_t ret_pinmux_status;

    printf("\r\n ---gpio_example begin---\r\n");

    ret = hal_gpio_init(HAL_GPIO_33);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_init failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /*Step1: Set pinmux as GPIO mode, configure GPIO 33 to input and pull up it.  Afetr that we read the input data for further validation*/

    /* Set pin as GPIO mode.*/
    ret_pinmux_status = hal_pinmux_set_function(HAL_GPIO_33, HAL_GPIO_33_GPIO33);
    if (HAL_PINMUX_STATUS_OK != ret_pinmux_status) {
        printf("hal_pinmux_set_function failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /* Set GPIO as input.*/
    ret = hal_gpio_set_direction(HAL_GPIO_33, HAL_GPIO_DIRECTION_INPUT);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_set_direction failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /* Configure the pull state to pull-up. */
    ret = hal_gpio_pull_up(HAL_GPIO_33);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_pull_up failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /* Read the input data of the pin for further validation.*/
    ret = hal_gpio_get_input(HAL_GPIO_33, &data_pull_up);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_get_input failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /*Step2: Change the pull state to pull-down and read the input data.*/

    /* Configure the pull state to pull-down.*/
    ret = hal_gpio_pull_down(HAL_GPIO_33);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_pull_down failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /* Read the input data of the pin for further validation.*/
    ret = hal_gpio_get_input(HAL_GPIO_33, &data_pull_down);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_get_input failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }

    /*Step3: Verify the success of pull state.*/

    if ((data_pull_down == HAL_GPIO_DATA_LOW) && (data_pull_up == HAL_GPIO_DATA_HIGH)) {
        printf("GPIO pull state configuration is successful\r\n");
    } else {
        printf("GPIO pull state configuration failed\r\n");
    }

    ret = hal_gpio_deinit(HAL_GPIO_33);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_deinit failed\r\n");
        return;
    }

    printf("\r\n ---gpio_example finished!!!---\r\n");
}

int main(void)
{
    /* Configure system clock. */
    SystemClock_Config();

    /* Configure the hardware. */
    prvSetupHardware();

    /* Enable I,F bits */
    __enable_irq();
    __enable_fault_irq();

    /* Add your application code here */
    printf("\r\n\r\n");/* The output UART used by printf is set by log_uart_init() */
    printf("welcome to main()\r\n");

    gpio_configure_pull_state_example();

    for (;;);
}


/*-----------------------------------------------------------*/



/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"

/*hal pinmux define*/
#include "hal_pinmux_define.h"
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
*@brief  Callback of irtx.
*@param[in] arg: pointer that will be used in callback.
*@return None.
*/
static void irtx_callback(void *arg)
{
    printf("\r\n ---Pulse data sent finished---\r\n");
    printf("\r\n ---irtx_example finished!!!---\r\n");
}

/**
*@brief  Set the pulse carrier and then send the pulse data
*@param None.
*@return None.
*/
static void irtx_send_pulse_data(void)
{
    uint8_t data_number = 41;

    /*Set frequency to 40Khz*/
    uint16_t frequency = 40;
    /*Set duty cycle to 25%*/
    uint8_t duty_cycle = 25;
    /*Unit:0.5us, SWM_BP=80, PW_value saturate for NEC 9ms leading*/
    uint8_t base_period = 80;

    uint8_t data[68] = {
        225, 112, 17, 15, 34, 15, 35, 15, 17, 15, 34, 15, 17, 15, 17, 15,
        17, 15, 34, 15, 17, 15, 34, 15, 34, 15, 17, 15, 34, 15, 17, 15,
        17, 15, 17, 15, 34, 15, 34, 15, 34
    };

    hal_gpio_init(HAL_GPIO_33);
    /* Call hal_pinmux_set_function to set GPIO pinmux, if EPT tool was not used to configure the related pinmux */
    hal_pinmux_set_function(HAL_GPIO_33, HAL_GPIO_33_IR_TX);

    printf("\r\n ---irtx_example begin---\r\n");
    hal_irtx_register_pulse_data_callback((hal_irtx_pulse_data_callback_t)irtx_callback, NULL);
    hal_irtx_configure_pulse_data_carrier(frequency, duty_cycle);
    hal_irtx_send_pulse_data(base_period, data, data_number);
    hal_gpio_deinit(HAL_GPIO_33);
}


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

    irtx_send_pulse_data();
    for (;;);
}


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
*@brief  Generate a fixed frequency @200Hz, a duty cycle ratio @50% waveform by PWM.
*@param None.
*@return None.
*/
static void pwm_generate_waveform(void)
{

    uint32_t total_count = 0;
    uint32_t duty_cycle = 0;

    printf("\r\n ---pwm_example begin---\r\n");
    hal_gpio_init(HAL_GPIO_0);
    /* Call hal_pinmux_set_function to set GPIO pinmux, if EPT tool was not used to configure
    the related pinmux */
    hal_pinmux_set_function(HAL_GPIO_0, HAL_GPIO_0_PWM0);
    /*Set source clock to 32KHz*/
    hal_pwm_init(HAL_PWM_CLOCK_32KHZ);
    /*Set frequency to 200Hz*/
    hal_pwm_set_frequency(HAL_PWM_0, 200, &total_count);
    /*Calculate the duty cycle when duty ratio is 50%*/
    duty_cycle = (total_count * 50) / 100;
    hal_pwm_set_duty_cycle(HAL_PWM_0, duty_cycle);
    hal_pwm_start(HAL_PWM_0);
    hal_gpio_deinit(HAL_GPIO_0);
    printf("\r\n ---pwm_example finished!!!---\r\n");
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

    pwm_generate_waveform();

    for (;;);
}


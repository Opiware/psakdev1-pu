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
#define MAX_PWD_LENGTH (68)

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
*@brief  In this function,we Show the irrx received data.
*@param[in] data: pointer to the data that will be used to show.
*@param[in] length: indicates the length of the data to show.
*@return None.
*/
static void show_ir_data(void *data, uint32_t length)
{
    uint8_t *buffer = data;
    uint32_t index = 0;
    for (index = 0; index < length; index++) {
        printf("%02x", buffer[index]);
        if (index != length - 1) {
            printf(",");
        }
        if ((index + 1) % 16 == 0) {
            printf("\r\n");
            continue;
        }
    }
    if (0 != index && 0 != index % 16) {
        printf("\r\n");
    }
    printf("\r\n");
}

/**
*@brief  Receive PWD data and show the received data.
*@param None.
*@return None.
*/
static hal_irrx_callback_t receive_code_pwd(void)
{
    uint8_t received_length = 0;
    uint8_t data[MAX_PWD_LENGTH] = {0};
    hal_irrx_receive_pwd(&received_length, data, sizeof(data));
    printf("Received PWD data:\r\n");
    show_ir_data(data, received_length);
    printf("\r\n ---irrx_example finished!!!---\r\n");
    return (hal_irrx_callback_t)0;
}

/**
*@brief  Configure the related GPIO and PINMUX conponents and start to receive PWD data then Show the received data.
*@param None.
*@return None.
*/
static void irrx_receive_pwd_data(void)
{
    uint32_t us = 0;
    hal_gpio_init(HAL_GPIO_34);
    /* Call hal_pinmux_set_function to set GPIO pinmux, if EPT tool was not used to configure the related pinmux */
    hal_pinmux_set_function(HAL_GPIO_34, HAL_GPIO_34_IR_RX);
    printf("\r\n ---irrx_example begin---\r\n");

    hal_irrx_init();
    hal_irrx_pwd_config_t format = {0};
    format.inverse = 1;
    format.terminate_threshold = 10200;
    hal_irrx_receive_pwd_start(&format, (hal_irrx_callback_t)receive_code_pwd, &us);
    hal_gpio_deinit(HAL_GPIO_34);
    printf("IRRX receive PWD data started.\r\n");

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

    irrx_receive_pwd_data();
    for (;;);
}


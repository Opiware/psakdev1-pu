/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"

/*memory attributes*/
#include "memory_attribute.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint32_t dma_length = 64;
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t  source_data[64];
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t  destination_data[64];


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
static void plain_log_uart_init(void)
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
*@brief  Initialize the periperal driver in this function. In this example, we initialize UART, Flash, and NVIC drivers.
*@param None.
*@return None.
*/
static void prvSetupHardware(void)
{
    /* System HW initialization */

    /* Peripherals initialization */
    plain_log_uart_init();
    hal_flash_init();
    hal_nvic_init();

    /* Board HW initialization */
}
/**
*@brief Callback of GDMA.
*@param[in] user_data: the data that user will use in this callback.
*@return None.
*/
static void gdma_callback(hal_gdma_event_t event, void * user_data)
{
    /*gdma_callback will be triggered when gdma transfers finished.*/
    uint32_t count = 0;

    hal_gdma_stop(HAL_GDMA_CHANNEL_0);

    hal_gdma_deinit(HAL_GDMA_CHANNEL_0);

    for (count = 0; count < dma_length; count++) {
        if (destination_data[count] != source_data[count]) {
            printf("GDMA destination data is not match with source data.\n");
        }

    }
    printf("\r\n ---gdma_example finished!!!---\r\n");

    /* This is for hal_examples auto-test */
    printf("example project test success.\n");

}
/**
*@brief GDMA transfer data with interrupt mode.
*@param None.
*@return None.
*/
static void gdma_transfer_data_interrupt()
{
    uint32_t count = 0;

    printf("\r\n ---gdma_example begin---\r\n");

    for (count = 0; count < dma_length; count++) {
        source_data[count] = count;
    }

    for (count = 0; count < dma_length; count++) {
        destination_data[count] = 0x5A;
    }

    hal_gdma_init(HAL_GDMA_CHANNEL_0);

    hal_gdma_register_callback(HAL_GDMA_CHANNEL_0, gdma_callback, (void *)1);

    hal_gdma_start_interrupt(HAL_GDMA_CHANNEL_0, (uint32_t)destination_data, (uint32_t)source_data, dma_length);


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

    gdma_transfer_data_interrupt();

    while (1);
}


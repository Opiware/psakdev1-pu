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
    log_uart_init();
    hal_flash_init();
    hal_nvic_init();
}


/**
*@brief  Example of erasing, reading and writing data from/to the flash.
*@param None.
*@return None.
*/
static void flash_sample(void)
{
    hal_flash_status_t status;
    unsigned int read_data[8], i;
    unsigned int flashTestAddress = 0x200000 - 0x8000;
    unsigned int data[8] = {0x5a5a5a5a, 0xa5a5a5a5, 0x55663204, 0x25225858, 0xFFDDBB99, 0xEECCAA88, 0x55663204, 0x25225858 };

    printf("\r\n ---flash_example begins---\r\n");

    /*Step1: Erase flash with block size 4k. */
    status = hal_flash_erase(flashTestAddress, HAL_FLASH_BLOCK_4K);

    if (status != HAL_FLASH_STATUS_OK) {
        printf("Flash erase failed! \n\r");
        return;
    }

    /*Step2: Write data to the address.*/
    /*  The valid address is 0 ~ flash_size.
        Before the address can be written to, the address located sector or block must first be erased.
    */
    status = hal_flash_write(flashTestAddress, (uint8_t *)data, 8 * sizeof(int));
    if (status != HAL_FLASH_STATUS_OK) {
        printf("Flash write failed! \n\r");
        return;
    }

    /*Step3: Read data from the valid address.*/
    /* The valid address is 0 ~ flash_size */
    hal_flash_read(flashTestAddress, (uint8_t *)read_data, 8 * sizeof(int));

    /*Step4: Compare the source data and write data */
    for (i = 0; i < 8; i++) {
        if (read_data[i] != data[i]) {
            printf("Data comparison failed! \n\r");
            status = HAL_FLASH_STATUS_ERROR_PROG_FAIL;
            return;
        }
    }

    if (status != HAL_FLASH_STATUS_OK) {
        printf("Flash write failed! \n\r");
        return;
    } else {
        printf("Flash example is successful! \n\r");

        /* This is for hal_examples auto-test */
        printf("example project test success.\n");

    }

    printf("\r\n ---flash_example finished!!!---\r\n");

    return;
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
    printf("\r\n\r\n");/* The output UART used by printf is set by log_uart_init() */
    printf("Welcome to main()\r\n");
    printf("\r\n\r\n");

    flash_sample();

    while (1);
}


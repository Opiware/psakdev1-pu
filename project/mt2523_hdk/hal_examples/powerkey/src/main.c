/* Copyright Statement:
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"
#include "keypad_custom.h"


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
*@brief Get the powerkey events in callback.
*@param None.
*@return None.
*/
static void keypad_user_powerkey_handler(void)
{
    hal_keypad_status_t         ret;
    hal_keypad_powerkey_event_t powekey_event;
    char *string[5] = {"release", "press", "longpress", "repeat", "pmu_longpress"};

    while (1) {
        ret = hal_keypad_powerkey_get_key(&powekey_event);

        /*If an error occurs, there is no key in the buffer*/
        if (ret == HAL_KEYPAD_STATUS_ERROR) {
            printf("[keypad][test]powerkey no key in buffer\r\n\r\n");
            break;
        }

        printf("[keypad][test]powerkey data:[%d], state:[%s]\r\n", (int)powekey_event.key_data, (char *)string[powekey_event.state]);
    }
}

/**
*@brief Example of powerkey. In this function we initialize powerkey and register callback.
*@param None.
*@return None.
*/
static void hal_powerkey_example(void)
{
    bool                ret_bool;
    hal_keypad_status_t ret_state;


    /*Initialize powerkey*/
    ret_bool = keypad_custom_powerkey_init();
    if (ret_bool == false) {
        printf("[keypad][test]keypad_custom_init init failed\r\n");
        return;
    }

    ret_state = hal_keypad_powerkey_register_callback((hal_keypad_callback_t)keypad_user_powerkey_handler, NULL);
    if (ret_state != HAL_KEYPAD_STATUS_OK) {
        printf("[keypad][test]hal_keypad_powerkey_register_callback failed, state = %d\r\n", ret_state);
    }
}


int main(void)
{
    /* Configure system clock */
    SystemClock_Config();

    SystemCoreClockUpdate();

    /* Configure the hardware */
    prvSetupHardware();

    /* Enable NVIC interrupts and fault exception*/
    __enable_irq();
    __enable_fault_irq();

    printf("\r\n\r\n");/* The output UART used by printf is set by log_uart_init() */
    printf("welcome to main()\r\n");
    printf("\r\n\r\n");

    hal_powerkey_example();

    while (1);
}


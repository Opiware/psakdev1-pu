/* Copyright Statement:
 *
 */

#include <stdint.h>

/*slim version for uart logging*/

void uart_init_boot_phase(void)
{
    /*enable PDN*/
    *(volatile uint32_t*)0xA0210320 = 0x100000;

    *(volatile uint32_t *)0xA00C0058 = 0x016C;

    /* set DLM/DLL for buardrate */
    *(volatile uint32_t *)0xA00C0008 = 0x0001;

    /* set UART TX/RX threshold rx--12, tx --4*/
    *(volatile uint32_t *)0xA00C0014 = 0x901;
}

void uart_deinit_boot_phase(void)
{
    /*disable PDN*/
    *(volatile uint32_t*)0xA0210310 = 0x100000;
}

void uart_put_onechar_boot_phase(uint8_t c)
{
    while ((*(volatile uint32_t*)0xA00C0028) == 0)
        ;

    *(volatile uint32_t*)0xA00C0004 = c;

    if (c != '\n')
        return;

    while ((*(volatile uint32_t*)0xA00C0028) == 0)
        ;

    *(volatile uint32_t*)0xA00C0004 = '\r';

    while ((*(volatile uint32_t*)0xA00C0028) == 0)
        ;
}

void uart_put_char_boot_phase(uint8_t *data, uint32_t size)
{
    uint32_t index = 0;

    for (index = 0; index < size; index++)
        uart_put_onechar_boot_phase(*(data++));
}

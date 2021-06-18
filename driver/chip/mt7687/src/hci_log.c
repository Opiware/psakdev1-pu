/* Copyright Statement:
 *
 */

#include "uart.h"
#include "hal_platform.h"
#include "hal_uart.h"
#include "hci_log.h"
#include <stdio.h>
#include <string.h>


#ifdef MTK_HCI_CONSOLE_MIX_ENABLE
#include "mt7687.h"
#define HCI_MAGIC_HI    0xab
#define HCI_MAGIC_LO    0xcd
#define BT_HCILOG_PORT  HAL_UART_0
#else
#define BT_HCILOG_PORT  HAL_UART_1
#endif

static int32_t hci_log(unsigned char type, unsigned char *buf, int32_t length)
{
    unsigned char head[8] = {'\0'};
    int32_t i;
    /*
    printf("[HCI LOG]Type[%02X]Length[%d]Data:",type, (int)length);
    for (i=0;i<length;i++)
    {
        printf("%02X",buf[i]);
    }

    printf("\n");
    */
#ifdef MTK_HCI_CONSOLE_MIX_ENABLE
    __disable_irq();
    sprintf((char *)head, "%c%c", HCI_MAGIC_HI, HCI_MAGIC_LO);
    hal_uart_send_polling(BT_HCILOG_PORT, (const uint8_t *)head, 2);
#endif
    sprintf((char *)head, "%c%c%c", type, (length & 0xff00) >> 8, length & 0xff);
    hal_uart_send_polling(BT_HCILOG_PORT, (const uint8_t *)head, 3);
    for (i = 0; i < length; i++) {
        hal_uart_send_polling(BT_HCILOG_PORT, (const uint8_t *)(buf + i), 1);
    }
#ifdef MTK_HCI_CONSOLE_MIX_ENABLE
    __enable_irq();
#endif

    return i;
}

int32_t hci_log_cmd(unsigned char *buf, int32_t length)
{
    return hci_log(HCI_COMMAND, buf, length);
}

int32_t hci_log_event(unsigned char *buf, int32_t length)
{
    return hci_log(HCI_EVENT, buf, length);
}

int32_t hci_log_acl_out(unsigned char *buf, int32_t length)
{
    return hci_log(HCI_ACL_OUT, buf, length);
}
int32_t hci_log_acl_in(unsigned char *buf, int32_t length)
{
    return hci_log(HCI_ACL_IN, buf, length);
}

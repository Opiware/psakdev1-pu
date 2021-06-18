/* Copyright Statement:
 *
 */

#ifndef __BT_DRIVER_HCI_LOG_H__
#define __BT_DRIVER_HCI_LOG_H__

#include <stdint.h>
#define BT_HCI_LOG_CMD      0x01  /**< HCI log type is command. */
#define BT_HCI_LOG_EVENT    0x02  /**< HCI log type is event. */
#define BT_HCI_LOG_ACL_IN   0x04  /**< HCI log type is acl data from remote device. */
#define BT_HCI_LOG_ACL_OUT  0x08  /**< HCI log type is acl data sent to remote device. */
#define BT_HCI_LOG_SCO_IN   0x10  /**< HCI log type is sco data from remote device.. */
#define BT_HCI_LOG_SCO_OUT  0x20  /**< HCI log type is sco data sent to remote device. */
#define BT_HCI_LOG_MSG      0x40  /**< HCI log type is message. */

/**
 * @brief Log HCI packets to UART for debug.
 * @param[in] in       is packet type. 0 means out hci packet. 1 means in hci packet. 2 means message.
 * @param[in] data     is the pointer to H4 HCI packet.
 * @param[in] data_len is the length of H4 HCI packet.
 */
void bt_hci_log(const uint8_t in, const void * data, const uint32_t data_len);

#endif // __BT_DRIVER_HCI_LOG_H__


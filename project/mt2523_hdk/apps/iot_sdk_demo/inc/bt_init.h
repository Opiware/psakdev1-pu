/* Copyright Statement:
 *
 */

#ifndef __BT_INIT_H__
#define __BT_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bt_type.h"

/* max supported connection number */
#define BT_CONNECTION_MAX   10

#define BT_MAX_LINK_NUM 2

/* max timer count */
#define BT_TIMER_NUM 10

#define BT_TX_BUF_SIZE 3*1024
#define BT_RX_BUF_SIZE 14*1024

#define BT_TIMER_BUF_SIZE (BT_TIMER_NUM * BT_CONTROL_BLOCK_SIZE_OF_TIMER)
#define BT_LE_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION)
#define BT_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_EDR_CONNECTION)

#define BT_RFCOMM_TOTAL_LINK_NUM 3 /**<[IMPORTANT!]total num = N, N is the acl link num that rfcomm support*/
#define BT_RFCOMM_LINK_BUF_SIZE (BT_RFCOMM_TOTAL_LINK_NUM * BT_CONTROL_BLOCK_SIZE_OF_RFCOMM)

#define BT_HFP_TOTAL_LINK_NUM BT_MAX_LINK_NUM
#define BT_HFP_LINK_BUF_SIZE (BT_HFP_TOTAL_LINK_NUM * BT_CONTROL_BLOCK_SIZE_OF_HFP)

#define BT_AVRCP_TOTAL_LINK_NUM 2
#define BT_AVRCP_LINK_BUF_SIZE (BT_AVRCP_TOTAL_LINK_NUM * BT_CONTROL_BLOCK_SIZE_OF_AVRCP)

#define BT_A2DP_SEP_TOTAL_NUM 4
#define BT_A2DP_SEP_BUF_SIZE (BT_A2DP_SEP_TOTAL_NUM * BT_CONTROL_BLOCK_SIZE_OF_A2DP_SEP)

#define BT_A2DP_TOTAL_LINK_NUM 2
#define BT_A2DP_LINK_BUF_SIZE (BT_A2DP_TOTAL_LINK_NUM * BT_CONTROL_BLOCK_SIZE_OF_A2DP)

#define BT_SPP_TOTAL_CONNECTION_NUM  (3 + 2) /**<[IMPORTANT!]total num = N1 + N2 + ..., Nx is the really used connection num for link-x, each link may different*/
#define BT_SPP_CONNECTION_BUF_SIZE (BT_SPP_TOTAL_CONNECTION_NUM * BT_CONTROL_BLOCK_SIZE_OF_SPP)

#define BT_PBAPC_TOTAL_CONNECTION_NUM  2 /**<[IMPORTANT!]total num = N1 + N2 + ..., Nx is the really used connection num for link-x, each link may different*/
#define BT_PBAPC_CONNECTION_BUF_SIZE (BT_PBAPC_TOTAL_CONNECTION_NUM * BT_CONTROL_BLOCK_SIZE_OF_PBAPC)

typedef enum {
    BT_MODE_IDLE,
    BT_MODE_AUDIO,
    BT_MODE_PXP,
    BT_MODE_DUAL,
    BT_MODE_SPP_SENSOR,
    BT_MODE_HOGP,
    BT_MODE_DEMO_TOTAL
} bt_demo_mode_t;

void bt_demo_init(void);

bt_status_t bt_demo_power_on(bt_demo_mode_t mode);

bt_status_t bt_demo_power_off(void);

void bt_demo_hci_log_switch(bool on_off);

bt_demo_mode_t bt_demo_get_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* __BT_INIT_H__  */


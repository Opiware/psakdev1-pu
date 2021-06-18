/* Copyright Statement:
 *
 */

/* max supported connection number */
#define BT_CONNECTION_MAX   10

/* max timer count */
#define BT_TIMER_NUM 10

#define BT_TX_BUF_SIZE 256*100
#define BT_RX_BUF_SIZE 2048*10

#define BT_TIMER_BUF_SIZE (BT_TIMER_NUM * BT_CONTROL_BLOCK_SIZE_OF_TIMER)
#define BT_LE_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION)

#define BT_RFCOMM_TOTAL_LINK_NUM 2 /**<[IMPORTANT!]total num = N, N is the acl link num that rfcomm support*/
#define BT_RFCOMM_LINK_BUF_SIZE (BT_RFCOMM_TOTAL_LINK_NUM * BT_CONTROL_BLOCK_SIZE_OF_RFCOMM)

#define BT_SPP_TOTAL_CONNECTION_NUM  (3 + 2) /**<[IMPORTANT!]total num = N1 + N2 + ..., Nx is the really used connection num for link-x, each link may different*/
#define BT_SPP_CONNECTION_BUF_SIZE (BT_SPP_TOTAL_CONNECTION_NUM * BT_CONTROL_BLOCK_SIZE_OF_SPP)

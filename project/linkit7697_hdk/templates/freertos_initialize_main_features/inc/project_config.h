/* Copyright Statement:
 *
 */

/* max supported connection number */
#define BT_CONNECTION_MAX   16

/* max timer count */
#define BT_TIMER_NUM 10

#define BT_TX_BUF_SIZE 256
#define BT_RX_BUF_SIZE 1024

#define BT_TIMER_BUF_SIZE (BT_TIMER_NUM * BT_CONTROL_BLOCK_SIZE_OF_TIMER)
#define BT_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION)

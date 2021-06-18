/* Copyright Statement:
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BT_SPP_CLIENT_H__
#define __BT_SPP_CLIENT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "bt_spp.h"

/* Definition ----------------------------------------------------------------*/

#define SPP_CLIENT_SEND_DATA_BUF 1024
#define SPP_CLIENT_RECEIVED_DATA_BUF 1024

/* Typedef ----------------------------------------------------------------*/
typedef struct
{
    uint32_t spp_handle;
    bool is_connected;
    uint16_t max_packet_length;
    /*the buffer for app data that will be sent*/
    uint8_t tx_data_buf[SPP_CLIENT_SEND_DATA_BUF];
    uint32_t tx_data_length;
    /*app rx data*/
    uint8_t rx_data_buf[SPP_CLIENT_RECEIVED_DATA_BUF];
    uint32_t rx_data_length;
} app_spp_client_cntx_t;

/* Functions ----------------------------------------------------------------*/
void spp_client_send_connect_request();
void spp_client_connect_cnf(bt_status_t status, bt_spp_connect_cnf_t* conn_cnf_p);
void spp_client_disconnect_request();
void spp_client_disconnect_ind(bt_status_t status, bt_spp_disconnect_ind_t* disc_ind_p);
void spp_client_send_data();
void spp_client_ready_to_send_ind(bt_spp_ready_to_send_ind_t* send_ind_p);
bool spp_role_is_client(uint32_t handle);
void spp_client_print_received_data(void);
void spp_client_receive_data(uint8_t *data, uint16_t len);
void spp_client_event_handler(bt_msg_type_t msg, bt_status_t status, void *param);
#ifdef __cplusplus
}
#endif

#endif /* __BT_SPP_CLIENT_H__ */


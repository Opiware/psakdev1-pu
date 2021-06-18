/* Copyright Statement:
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BT_SPP_SERVER_H__
#define __BT_SPP_SERVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "bt_spp.h"
#define SPP_SERVER_SEND_DATA_BUF 1024
#define SPP_SERVER_RECEIVED_DATA_BUF 1024

typedef struct
{
    uint32_t spp_handle;
    uint16_t max_packet_length;
    bool is_connected;
    /*the buffer for app data that will be sent*/
    uint8_t tx_data_buf[SPP_SERVER_SEND_DATA_BUF];
    uint32_t tx_data_length;
    /*app rx data*/
    uint8_t rx_data_buf[SPP_SERVER_RECEIVED_DATA_BUF];
    uint32_t rx_data_length;
} app_spp_server_cntx_t;

/* Functions ----------------------------------------------------------------*/
void spp_server_connect_ind(bt_status_t status, bt_spp_connect_ind_t* conn_ind_p);
void spp_server_connect_cnf(bt_status_t status, bt_spp_connect_cnf_t* conn_cnf_p);
void spp_server_disconnect_ind(bt_status_t status, bt_spp_disconnect_ind_t *disc_ind_p);
void spp_server_disconnect_request(void);
void spp_server_ready_to_send_ind(bt_spp_ready_to_send_ind_t* send_ind_p);
void spp_server_send_data(void);
void spp_server_event_handler(bt_msg_type_t msg, bt_status_t status, void *param);
void spp_server_print_received_data(void);
void spp_server_receive_data(uint8_t *data, uint16_t len);
#endif /* __BT_SPP_SERVER_H__ */


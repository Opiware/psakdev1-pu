/* Copyright Statement:
 *
 */

#ifndef _CONNSYS_ADAPTER_H__
#define _CONNSYS_ADAPTER_H__

#include <stdint.h>
#include "net_task.h"
#include "wifi_api.h"

/***************************  RX  adapter *****************************/

typedef enum _PKT_HANDLE_RESULT_E {
    PKT_HANDLE_NON_COMPLETE = 0,
    PKT_HANDLE_COMPLETE,
} PKT_HANDLE_RESULT_T;


typedef void (*connsys_alloc_pkt_t)(uint32_t allocate_len,
                                    void **pkt_ptr,
                                    uint8_t **payload_ptr);

typedef void (*connsys_free_pkt_t)(void *);
typedef uint8_t (*connsys_enqueue_t)(int32_t port, PNETFUNC bottom_half);

typedef PKT_HANDLE_RESULT_T(*connsys_deliver_inband_t)(void *pkt, uint8_t *payload, uint32_t len);
typedef PKT_HANDLE_RESULT_T(*connsys_deliver_data_t)(void *pkt, uint8_t *payload, uint32_t len, int inf);
typedef uint8_t (*connsys_advance_pkt_t)(void *pkt, int16_t len);


typedef struct mt76x7_connsys_ops {
    connsys_alloc_pkt_t         alloc;
    connsys_free_pkt_t          free;
    connsys_advance_pkt_t       advance_pkt_hdr;
    connsys_enqueue_t           enqueue_bottom_half;
    connsys_deliver_data_t      deliver_tcpip;
    connsys_deliver_inband_t    deliver_inband;
} *connsys_ops_t;

extern connsys_ops_t connsys_ops;

extern void connsys_set_rxraw_handler(wifi_rx_handler_t handler);
#endif


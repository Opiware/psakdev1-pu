/* Copyright Statement:
 *
 */

#ifndef __PSNETIF_H
#define __PSNETIF_H

#ifdef MTK_TCPIP_FOR_EXTERNAL_MODULE_ENABLE
#include "lwip/def.h"
#include <stdint.h>

#ifndef PS_DATA_DEBUG
//#define PS_DATA_DEBUG
#endif

//#define PS_DATA_UT

typedef enum {
    MSG_ID_PS_NETIF_UART_DATA,
    MSG_ID_PS_NETIF_CMUX_DATA,
    MSG_ID_PS_NETIF_MSM_END
} ps_netif_msg_id_t;


typedef struct {
    ps_netif_msg_id_t msg_id;
    void              *msg_data;
} ps_netif_msg_t;

typedef struct _gprs_net_info_struct
{
    char       *ipaddr;
    char       *netmask;
    char       *gw;
    char       *dnsservser1;
    char       *dnsservser2;
    uint32_t   mtu;
} gprs_net_info_struct;

s8_t ps_netif_set_netinfo(u8_t context_id, gprs_net_info_struct *netinfo);

s8_t ps_netif_remove_netinfo(u8_t context_id);

void ps_netif_init(void);

void ps_netif_lock_tcpip_time();

void ps_netif_unlock_tcpip_time();


#endif

#endif /* __PSNETIF_H */


/* Copyright Statement:
 *
 */

#ifndef __PSNETIF_H
#define __PSNETIF_H

#ifdef TCPIP_FOR_MT5931_ENABLE
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include <stdint.h>

typedef enum {
    STA_IP_MODE_STATIC   = 0,
    STA_IP_MODE_DHCP     = 1
} sta_ip_mode_t;

typedef enum {
    NETIF_TYPE_LOOPBACK = 0,
    NETIF_TYPE_AP       = 1,
    NETIF_TYPE_STA      = 2
} netif_type_t;

typedef struct {
    int32_t ip_mode;

    ip4_addr_t sta_addr;
    ip4_addr_t sta_mask;
    ip4_addr_t sta_gateway;

    ip4_addr_t ap_addr;
    ip4_addr_t ap_mask;
    ip4_addr_t ap_gateway;
} lwip_tcpip_config_t;

void lwip_tcpip_init(lwip_tcpip_config_t *tcpip_config, uint8_t opmode);

void mt5931_low_level_input(struct netif *netif, struct pbuf *p);

int lwip_get_netif_name(netif_type_t netif_type, char *name);

struct netif *netif_find_by_type(netif_type_t netif_type);

#endif

#endif /* __PSNETIF_H */


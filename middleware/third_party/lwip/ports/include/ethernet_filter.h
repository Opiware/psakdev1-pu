/* Copyright Statement:
 *
 */

#ifndef __ETHERNET_FILTER_H
#define __ETHERNET_FILTER_H

#include <lwip/netif.h>

/* return: 1: handled, 0: not handled */
typedef int (*netif_cmd_rx_filter_fn)(void* pkt, unsigned char *payload, unsigned int len);
typedef int (*netif_rx_filter_fn)(unsigned char *payload, unsigned int len);


int ethernet_raw_pkt_sender(unsigned char *buf, unsigned int len, struct netif *netif);

int low_level_get_sta_mac_addr(unsigned char *mac_addr);
int low_level_get_ap_mac_addr(unsigned char *mac_addr);


#endif /* __ETHERNET_FILTER_H */


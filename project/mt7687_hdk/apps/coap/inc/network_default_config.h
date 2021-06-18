/* Copyright Statement:
 *
 */

#ifndef __NETWORK_DEFAULT_CONFIG_H__
#define __NETWORK_DEFAULT_CONFIG_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "os.h"

#include "lwip/sockets.h"
#include "lwip/ip4_addr.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "ethernetif.h"
#include "dhcpd.h"

void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config, dhcpd_settings_t *dhcpd_settings);
int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config);
int32_t dhcp_config_init(void);


#define USE_DHCP                 1

#define STA_IPADDR    ("192.168.1.101")
#define STA_NETMASK   ("255.255.255.0")
#define STA_GATEWAY   ("192.168.1.1")

#define AP_IPADDR     ("10.10.10.1")
#define AP_NETMASK    ("255.255.255.0")
#define AP_GATEWAY    ("10.10.10.1")

#define PRIMARY_DNS   ("8.8.8.8")
#define SECONDARY_DNS ("8.8.4.4")
#define IP_POOL_START ("10.10.10.2")
#define IP_POOL_END   ("10.10.10.10")

#endif  /*__WIFI_LWIP_DEFAULT_CONFIG_H__*/

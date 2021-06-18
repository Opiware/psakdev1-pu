/* Copyright Statement:
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "os.h"

#include "nvdm.h"
#include "network_default_config.h"
#include "connsys_profile.h"
#include "get_profile_string.h"

#ifdef __ICCARM__
#define STRCPY strncpy
#else
#define STRCPY strlcpy
#endif

#ifdef MTK_WIFI_PROFILE_ENABLE
int32_t dhcp_config_init(void)
{
    uint8_t buff[PROFILE_BUF_LEN] = {0};
    uint32_t sz = sizeof(buff);

    nvdm_read_data_item("network", "IpMode", buff, &sz);
    return strcmp((char *)buff, "dhcp") ? STA_IP_MODE_STATIC : STA_IP_MODE_DHCP;
}

int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config)
{
    uint8_t buff[PROFILE_BUF_LEN] = {0};
    uint32_t sz = sizeof(buff);

    tcpip_config->ip_mode = dhcp_config_init();

    nvdm_read_data_item("network", "IpAddr", buff, &sz);
    ip4addr_aton((const char *)buff, &(tcpip_config->sta_addr));
    ip4addr_aton((const char *)buff, &(tcpip_config->ap_addr));
    sz = sizeof(buff);
    nvdm_read_data_item("network", "IpNetmask", buff, &sz);
    ip4addr_aton((const char *)buff, &(tcpip_config->sta_mask));
    ip4addr_aton((const char *)buff, &(tcpip_config->ap_mask));
    sz = sizeof(buff);
    nvdm_read_data_item("network", "IpGateway", buff, &sz);
    ip4addr_aton((const char *)buff, &(tcpip_config->sta_gateway));
    ip4addr_aton((const char *)buff, &(tcpip_config->ap_gateway));
    return 0;
}

static uint32_t ip_number_to_big_endian(uint32_t ip_number)
{
    uint8_t *byte = (uint8_t *)&ip_number;
    return (uint32_t)((byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | byte[3]);
}

static void ip_number_to_string(uint32_t ip_number, char ip_string[IP4ADDR_STRLEN_MAX])
{
    snprintf(ip_string,
             IP4ADDR_STRLEN_MAX,
             "%d.%d.%d.%d",
             (uint8_t)((ip_number >> 24) & 0xFF),
             (uint8_t)((ip_number >> 16) & 0xFF),
             (uint8_t)((ip_number >> 8) & 0xFF),
             (uint8_t)((ip_number >> 0) & 0xFF));
}

static void dhcpd_set_ip_pool(const ip4_addr_t *ap_ip_addr,
                              const ip4_addr_t *ap_net_mask,
                              char ip_pool_start[IP4ADDR_STRLEN_MAX],
                              char ip_pool_end[IP4ADDR_STRLEN_MAX])
{
    uint32_t ap_ip_number = ip_number_to_big_endian(ip4_addr_get_u32(ap_ip_addr));
    uint32_t ap_mask_number = ip_number_to_big_endian(ip4_addr_get_u32(ap_net_mask));
    uint32_t ip_range_min = ap_ip_number & ap_mask_number;
    uint32_t ip_range_max = ip_range_min | (~ap_mask_number);

    if ((ip_range_max - ap_ip_number) > (ap_ip_number - ip_range_min)) {
        ip_number_to_string(ap_ip_number + 1, ip_pool_start);
        ip_number_to_string(ip_range_max - 1, ip_pool_end);
    } else {
        ip_number_to_string(ip_range_min + 1, ip_pool_start);
        ip_number_to_string(ap_ip_number - 1, ip_pool_end);
    }
}

void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config,
                         dhcpd_settings_t *dhcpd_settings)
{
    STRCPY(dhcpd_settings->dhcpd_server_address,
           ip4addr_ntoa(&tcpip_config->ap_addr),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_netmask,
           ip4addr_ntoa(&tcpip_config->ap_mask),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_gateway,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_primary_dns,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    /* secondary DNS is not defined by default */
    STRCPY(dhcpd_settings->dhcpd_secondary_dns,
           "0.0.0.0",
           IP4ADDR_STRLEN_MAX);

    dhcpd_set_ip_pool(&tcpip_config->ap_addr,
                      &tcpip_config->ap_mask,
                      dhcpd_settings->dhcpd_ip_pool_start,
                      dhcpd_settings->dhcpd_ip_pool_end);
}

#else

int32_t dhcp_config_init(void)
{
    return (USE_DHCP == 0) ? STA_IP_MODE_STATIC : STA_IP_MODE_DHCP;
}

int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config)
{
    tcpip_config->ip_mode = dhcp_config_init();

    ip4addr_aton(STA_IPADDR, &(tcpip_config->sta_addr));
    ip4addr_aton(STA_NETMASK, &tcpip_config->sta_mask);
    ip4addr_aton(STA_GATEWAY, &tcpip_config->sta_gateway);

    ip4addr_aton(AP_IPADDR, &(tcpip_config->ap_addr));
    ip4addr_aton(AP_NETMASK, &tcpip_config->ap_mask);
    ip4addr_aton(AP_GATEWAY, &tcpip_config->ap_gateway);

    return 0;
}

void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config,
                         dhcpd_settings_t *dhcpd_settings)
{
    STRCPY(dhcpd_settings->dhcpd_server_address,
           ip4addr_ntoa(&tcpip_config->ap_addr),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_netmask,
           ip4addr_ntoa(&tcpip_config->ap_mask),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_gateway,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    strcpy((char *)dhcpd_settings->dhcpd_primary_dns,    PRIMARY_DNS);
    strcpy((char *)dhcpd_settings->dhcpd_secondary_dns,  SECONDARY_DNS);
    strcpy((char *)dhcpd_settings->dhcpd_ip_pool_start,  IP_POOL_START);
    strcpy((char *)dhcpd_settings->dhcpd_ip_pool_end,    IP_POOL_END);
}
#endif

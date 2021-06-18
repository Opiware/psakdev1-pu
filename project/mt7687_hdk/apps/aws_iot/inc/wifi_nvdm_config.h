/* Copyright Statement:
 *
 */

/**
 * @file wifi_nvdm_config.h
 * */

#ifndef __WIFI_NVDM_INIT_H__
#define __WIFI_NVDM_INIT_H__


#include <stdint.h>
#include "lwip/netif.h"
#include "connsys_profile.h"
#include "ethernetif.h"
#include "dhcpd.h"
#include "wifi_api.h"
#include "wifi_scan.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t opmode;
    uint8_t country_code[4];

    uint8_t sta_ssid[32];
    uint8_t sta_ssid_len;
    uint8_t sta_wpa_psk[64];
    uint8_t sta_wpa_psk_len;
    uint8_t sta_default_key_id;
    uint8_t sta_bandwidth;
    uint8_t sta_wireless_mode;
    uint8_t sta_listen_interval;
    uint8_t sta_power_save_mode;

    uint8_t ap_ssid[32];
    uint8_t ap_ssid_len;
    uint8_t ap_channel;
    uint8_t ap_bw;
    uint8_t ap_hide_ssid;
    uint8_t ap_auth_mode;
    uint8_t ap_encryp_type;
    uint8_t ap_wpa_psk[64];
    uint8_t ap_wpa_psk_len;
    uint8_t ap_default_key_id;
    uint8_t ap_wireless_mode;
    uint8_t ap_dtim_interval;

} wifi_cfg_t;


void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config, dhcpd_settings_t *dhcpd_settings);
int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config);
int32_t wifi_config_init(wifi_cfg_t *wifi_config);
int32_t dhcp_config_init(void);
int32_t wifi_init_done_handler(wifi_event_t event, uint8_t *payload, uint32_t length);
int save_cf_credential_to_nvdm(P_IOT_CONFIG_FREE_IE cred);
int32_t save_cf_ready_to_nvdm(uint8_t config_ready);
int32_t get_cf_ready_to_nvdm(uint8_t *config_ready);

#ifdef __cplusplus
}
#endif

#endif /* __WIFI_NVDM_INIT_H__ */


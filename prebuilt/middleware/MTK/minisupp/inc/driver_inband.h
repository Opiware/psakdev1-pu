/* Copyright Statement:
 *
 */

#ifndef DRIVER_INBAND_H
#define DRIVER_INBAND_H

#include "wifi_api.h"

#define EXTRA_IE_SIZE_LIMIT 512

enum nl80211_auth_type {
    NL80211_AUTHTYPE_OPEN_SYSTEM,
    NL80211_AUTHTYPE_SHARED_KEY,
    NL80211_AUTHTYPE_FT,
    NL80211_AUTHTYPE_NETWORK_EAP,

    /* keep last */
    __NL80211_AUTHTYPE_NUM,
    NL80211_AUTHTYPE_MAX = __NL80211_AUTHTYPE_NUM - 1,
    NL80211_AUTHTYPE_AUTOMATIC
};

enum nl80211_wpa_versions {
    NL80211_WPA_VERSION_1 = 1 << 0,
    NL80211_WPA_VERSION_2 = 1 << 1,
};

extern int process_global_event(void *priv, unsigned char evt_id, unsigned char *body, int len);
//void supplicant_scan_table_age_out(void *eloop_ctx, void *timeout_ctx);
//void reregister_scan_table_age_out(void);


struct l2_packet_data *wpa_driver_inband_get_sock_recv(void *priv);
int wpa_supplicant_entry_iface_change(unsigned char op_mode);
void wpa_supplicant_entry_op_mode_get(unsigned char *op_mode);
int wpa_supplicant_entry_op_mode_set(unsigned char op_mode);
void wpa_driver_inband_handle_wow(void *priv, unsigned char b_scan);
void wpa_driver_inband_handle_beacon(void *priv, uint8_t *target_bssid);
void wpa_driver_inband_set_ps_mode(void *priv, uint8_t do_assoc);
void wpa_driver_inband_apcli_connect(void *priv);
int mtk_ctrl_get_sta_qos_bit(int32_t inf_num, char *mac_addr);
int wpa_driver_inband_set_wep_key(void *ssid_ctx, uint8_t port_mode);
int mtk_supplicant_get_bssid(uint8_t *bssid);
int mtk_supplicant_set_ssid_bssid(unsigned char *ssid, unsigned int ssidlen, uint8_t *bssid);

#ifdef MTK_WIFI_WPS_ENABLE
int mtk_supplicant_config_set_wps_auto_connection(bool on_off);
int mtk_supplicant_config_get_wps_auto_connection(bool *on_off);
int mtk_supplicant_connection_wps_pbc(uint8_t port, uint8_t *bssid);
int mtk_supplicant_connection_wps_pin(uint8_t port, uint8_t *bssid, uint8_t *pin_code);
int mtk_supplicatn_wps_get_pin(uint8_t port, uint8_t *pin_code);
int mtk_supplicant_ctrl_wps_device_info(char *cmd);
int mtk_supplicant_ctrl_wps_set_credential_handler(char *cmd);
int mtk_supplicant_ctrl_wps_auto_conneciton(char *cmd);
int mtk_supplicant_config_set_wps_device_info(wifi_wps_device_info_t *device_info);
int mtk_supplicant_config_get_wps_device_info(wifi_wps_device_info_t *device_info);
#endif

void mtk_supplicant_show_interfaces(void);
void wpa_driver_inband_password_error(void);

#endif //#ifndef DRIVER_INBAND_H


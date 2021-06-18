/* Copyright Statement:
 *
 */

#include <stdint.h>
#include <stdio.h>

int32_t wifi_get_channel_list(uint8_t band, uint8_t region, char *channel_list);


bool wifi_is_opmode_valid(uint8_t mode);

bool wifi_is_port_valid(uint8_t port);

bool wifi_is_band_valid(uint8_t band);

bool wifi_is_bandwidth_valid(uint8_t bandwidth);

bool wifi_is_auth_mode_valid(uint8_t auth_mode);

bool wifi_is_encrypt_type_valid(uint8_t encrypt_type);

bool wifi_is_ps_mode_valid(uint8_t ps_mode);

int32_t wifi_profile_set_opmode(uint8_t mode);

#ifdef MTK_WIFI_PROFILE_ENABLE
int32_t wifi_profile_get_opmode(uint8_t *mode);

int32_t wifi_profile_set_channel(uint8_t port, uint8_t channel);

int32_t wifi_profile_get_channel(uint8_t port, uint8_t *channel);

int32_t wifi_profile_set_bandwidth(uint8_t port, uint8_t bandwidth);

int32_t wifi_profile_get_bandwidth(uint8_t port, uint8_t *bandwidth);

int32_t wifi_profile_get_mac_address(uint8_t port, uint8_t *address);

int32_t wifi_profile_set_mac_address(uint8_t port, uint8_t *address);

int32_t wifi_profile_set_ssid(uint8_t port, uint8_t *ssid , uint8_t ssid_length);

int32_t wifi_profile_get_ssid(uint8_t port, uint8_t *ssid, uint8_t *ssid_length);

int32_t wifi_profile_commit_setting(char *profile_section);

int32_t wifi_profile_get_profile(uint8_t port, wifi_profile_t *profile);

int32_t wifi_profile_set_wireless_mode(uint8_t port, wifi_phy_mode_t mode);

int32_t wifi_profile_get_wireless_mode(uint8_t port, wifi_phy_mode_t *mode);

int32_t wifi_profile_set_security_mode(uint8_t port, wifi_auth_mode_t auth_mode, wifi_encrypt_type_t encrypt_type);

int32_t wifi_profile_get_security_mode(uint8_t port, wifi_auth_mode_t *auth_mode, wifi_encrypt_type_t *encrypt_type);

int32_t wifi_profile_set_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t passphrase_length);

int32_t wifi_profile_get_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t *passphrase_length);

int32_t wifi_profile_set_pmk(uint8_t port, uint8_t *pmk);

int32_t wifi_profile_get_pmk(uint8_t port, uint8_t *pmk);

int32_t wifi_profile_set_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

int32_t wifi_profile_get_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

int32_t wifi_profile_get_country_region(uint8_t band, uint8_t *region);

int32_t wifi_profile_set_country_region(uint8_t band, uint8_t region);

int32_t wifi_profile_get_dtim_interval(uint8_t *interval);

int32_t wifi_profile_set_dtim_interval(uint8_t interval);

int32_t wifi_profile_get_listen_interval(uint8_t *interval);

int32_t wifi_profile_set_listen_interval(uint8_t interval);

int32_t wifi_profile_get_power_save_mode(uint8_t *power_save_mode);

int32_t wifi_profile_set_power_save_mode(uint8_t power_save_mode);

int32_t wifi_profile_get_configfree(uint8_t *config_ready);

int32_t wifi_profile_set_configfree(uint8_t config_ready);

int32_t port_sanity_check(char *port_str);

#endif //MTK_WIFI_PROFILE_ENABLE


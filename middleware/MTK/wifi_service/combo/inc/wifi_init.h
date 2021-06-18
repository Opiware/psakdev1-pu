/* Copyright Statement:
 *
 */

#ifndef __WIFI_INIT_H__
#define __WIFI_INIT_H__

#include "wifi_api.h"
#include "connsys_profile.h"
#include "wifi_inband.h"//wifi_antenna_status_t in this head currently

/*use the wifi_init_callback,  to make the modules independence */
typedef struct __wifi_init_callback {
    int32_t (*wifi_get_pmk_info)(uint8_t *pmk,uint8_t *ssid,uint8_t ssid_len, uint8_t *psk, uint8_t psk_len);
#if 1//def MTK_ANT_DIV_ENABLE
    int32_t (*wifi_record_ant_status)(wifi_antenna_status_t * ant_status);
#endif

} wifi_init_callback;

void wifi_scan_init(wifi_config_t *config);
uint8_t wifi_get_ps_mode(void);
bool wifi_get_security_valid(void);
void wifi_set_security_valid(bool value);

uint8_t wifi_set_sleep_handle(const char *handle_name);
int32_t wifi_lock_sleep(uint8_t handle_index);
int32_t wifi_unlock_sleep(uint8_t handle_index);
int32_t wifi_unlock_sleep_all(void);
int32_t wifi_release_sleep_handle(uint8_t handle);
wifi_phy_mode_t wifi_change_wireless_mode_5g_to_2g(wifi_phy_mode_t wirelessmode);
int32_t wifi_sleep_manager_get_lock_status(void);
int32_t record_2G_5G_channel_list(uint8_t BGband_region, uint8_t Aband_region);
int32_t wifi_country_code_region_mapping(uint8_t *country_code, uint8_t *bg_band_region, uint8_t *a_band_region);
#if 0
#ifdef MTK_SINGLE_SKU_SUPPORT
void wifi_get_single_sku_from_nvdm(singleSKU2G_t * single, uint8_t group_number);
#endif
#endif

#endif /* __WIFI_INIT_H__ */


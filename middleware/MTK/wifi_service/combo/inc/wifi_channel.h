/* Copyright Statement:
 *
 */

#ifndef __WIFI_CHANNEL_H__
#define __WIFI_CHANNEL_H__
#include "wifi_private_api.h"


wifi_country_code_t *wifi_get_country_channel_list(void);
int32_t wifi_build_country_channel_list(wifi_country_code_t *country_channel);
int32_t wifi_channel_list_init(wifi_sys_cfg_t *syscfg);
uint8_t wifi_parse_bg_band_num(wifi_country_code_t *country_channel);
uint8_t wifi_parse_a_band_num(wifi_country_code_t *country_channel);
int32_t wifi_take_channel_list_mutex(void);
int32_t wifi_give_channel_list_mutex(void);


#endif /* __WIFI_CHANNEL_H__ */


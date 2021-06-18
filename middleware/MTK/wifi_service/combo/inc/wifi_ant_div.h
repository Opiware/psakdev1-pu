/* Copyright Statement:
 *
 */

#ifndef __WIFI_ANT_DIV_H__
#define __WIFI_ANT_DIV_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <wifi_inband.h>

#ifdef MTK_ANT_DIV_ENABLE
void ant_diversity_init(int ant);
void ant_div_update_pin(void);

int32_t wifi_config_set_antenna_monitor(void);

int32_t wifi_config_get_antenna_status(wifi_antenna_status_t *ant_status);

int32_t wifi_profile_record_antenna_status(wifi_antenna_status_t * ant_status);

int32_t wifi_config_set_antenna_number(uint8_t antenna_number);

#endif /* MTK_ANT_DIV_ENABLE */

#endif /* __WIFI_ANT_DIV_H__ */


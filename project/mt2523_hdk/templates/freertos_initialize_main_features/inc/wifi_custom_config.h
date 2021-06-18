/* Copyright Statement:
 *
 */


#ifndef _WIFI_CUSTOM_CONFIG_H
#define _WIFI_CUSTOM_CONFIG_H

#include "hal.h"


hal_sdio_port_t wifi_get_msdc_port(void);
void wifi_get_sdio_config(hal_sdio_config_t *config);

#endif


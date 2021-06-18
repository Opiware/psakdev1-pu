/* Copyright Statement:
 *
 */

/*!
     @header HomeKit Information Element (IE)
      This header contains function prototypes called by the WAC
      engine. These functions and defines aid in creating an Apple Device
      Information Element for embedding in an IEEE802.11 WiFi beacon. */

#ifndef __WIFI_HOMEKIT_H__
#define __WIFI_HOMEKIT_H__
#include "stdint.h"
#include "type_def.h"

int32_t wifi_create_homekit_ie(const char *name,
                               const char *model,
                               const char *manufacturer,
                               const uint8_t *macAddress,
                               char isUnconfigured,
                               char supportsAirPlay,
                               char supportsAirPrint,
                               char supportsMFiConfigurationV1,
                               char supportsWakeOnWireless,
                               char supports2_4GHzNetworks,
                               char supports5GHzNetworks,
                               uint8_t **outIEBuffer,
                               size_t *outIEBufferLen);

int32_t wifi_connection_get_scan_list(uint8_t *number, wifi_scan_list_t *scan_list);
int32_t wifi_update_airplay_ie(uint8_t *ie, size_t ie_len);
int32_t wifi_enable_airplay(uint8_t enable);
int32_t wifi_update_homekit_ie(uint8_t *ie, size_t ie_len);

#endif /*__WIFI_HOMEKIT_H__*/



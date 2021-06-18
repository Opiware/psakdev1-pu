/* Copyright Statement:
 *
 */

#ifndef __WIFI_CONFIG_FREE_H__
#define __WIFI_CONFIG_FREE_H__

//#include "type_def.h"
#include "stdint.h"
#include "wifi_api.h"
#include "connsys_profile.h"
#include "memory_attribute.h"
#include "wifi_event.h"

//
//  ConfigureFree Demo - parse AP's credential for NVRAM Setting and reboot
//
typedef struct _IOT_CONFIG_FREE_IE {
    uint8_t Nounce[4];
    uint8_t Ssid[32];
    uint8_t SsidLen;
    uint8_t Bssid[6];
    uint8_t AuthMode;
    uint8_t EncrypType;
    uint8_t WpaPsk[64];
    uint8_t WpaPskLen;
    uint8_t Channel;
} IOT_CONFIG_FREE_IE, *P_IOT_CONFIG_FREE_IE;
typedef struct __configure_free_callback
{
	int32_t (*save_credential)(P_IOT_CONFIG_FREE_IE cred);
	int32_t (*save_ready)(uint8_t config_ready);
} CONFIGURE_FREE_CALLBACK;

void register_configure_free_callback(void *save_credential_func, void *save_ready_func);

int wifi_cf_credential_handler(unsigned int inf, unsigned char *body, int len);


/**
* @brief This function get  the device is configured (configfree ready) in the Flash memory or not. \n
* @param[out] config_ready indicates the ConfigFree flow has completed and the device is configured
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | ConfigFree un-configured: default value, ConfigFree Flow will be triggered by default|
* \b 1                          | ConfigFree configured|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_configfree(uint8_t *config_ready);

/**
* @brief This function configure the configfree ready in the Flash memory. \n
* The profile is read to initialize the system at boot up.
*
* @param[in] config_ready indicates the ConfigFree flow has completed
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | ConfigFree un-configured: default enable ConfigFree Flow|
* \b 1                          | ConfigFree configured|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note Use this function will reboot the device and boot in concurrent mode (opmode=3)
*/
int32_t wifi_profile_set_configfree(uint8_t config_ready);

#endif /* __WIFI_SCAN_H */

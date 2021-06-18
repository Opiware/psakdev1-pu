/* Copyright Statement:
 *
 */

#ifndef __WIFI_WPS_H__
#define __WIFI_WPS_H__

#if defined(MTK_WIFI_WPS_ENABLE)

#include <stdint.h>
#include <stdio.h>

/**
* @brief This function is the WPS credential process.
*
* @param[in] event indicates the Wi-Fi Credential Event.
*
* Value                                                            |Definition                                                |
* ------------------------------|------------------------------------------------------------------------|
* \b  #WIFI_EVENT_IOT_WPS_COMPLETE           |Get credential event, Enrollee get credential from Registrar.|
*
* @param[in]  payload is the credential message.
*
* @param[in]  length is the credential length,
*
* @return  >=0 get the total credential, <0 can't get the total credential.
*/
int32_t wifi_wps_credential_event_handler(wifi_event_t event, uint8_t *payload, uint32_t length);

/**
* @brief This function is register WPS credential handler example.
*
* @return  >=0 means success, <0 means fail.
*/
int32_t wifi_wps_register_credential_handler(void);

/**
* @brief This function is unregister WPS credential handler example.
*
* @return  >=0 means success, <0 means fail.
*/
int32_t wifi_wps_unregister_credential_handler(void);

/**
* @brief This function gets the device information for WPS from NVRAM
*
* @param[out] device_info holds the device information after this function being called.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note This function is used by Supplicant for WPS initialization, and this function might be removed next version.
*/
int32_t wifi_wps_get_device_info(wifi_wps_device_info_t *device_info);

#endif /* MTK_WIFI_WPS_ENABLE */

#endif /* __WIFI_SCAN_H */


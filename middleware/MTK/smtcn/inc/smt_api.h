/* Copyright Statement:
 *
 */

/**
 * @file smt_api.h
 *
 * MTK Smart Connection interfaces
 * */

/**
 * @addtogroup Smart_Connection
 * @{
 * This section introduces MTK Smart Connection APIs including details on how to use the APIs, enums, structures and functions.
 *
 * @section Smart_Connection_Usage_Chapter How to use these APIs
 *
 * - Connecting to the target AP with Smart Connection\n
 *  - Step 1. Define a #wifi_smart_connection_callback_t callback function to process a Smart Connection event.
 *  - Step 2. Call #wifi_smart_connection_init() to apply for required resources.
 * Note: The predefined callback, such as, the smtcn_evt_handler(), should be passed to the #wifi_smart_connection_init().
 *  - Step 3. Call #wifi_smart_connection_start() to start the Smart Connection.
 *  - Step 4. Call #wifi_smart_connection_get_result() to get the SSID and the password, when receiving #WIFI_SMART_CONNECTION_EVENT_INFO_COLLECTED event.
 *  - Step 5. Connect to the target AP.
 *  - Step 6: Call #wifi_smart_connection_stop() to exit the Smart Connection. Or call #wifi_smart_connection_deinit() if the connection is succesffuly established.
 *  - sample code:
 *    @code
 *      void smtcn_evt_handler(wifi_smart_connection_event_t event, void *data)
 *      {
 *          uint8_t passwd[WIFI_LENGTH_PASSPHRASE + 1] = {0}; 
 *          uint8_t ssid[WIFI_MAX_LENGTH_OF_SSID + 1] = {0};
 *          uint8_t ssid_len = 0;
 *          uint8_t passwd_len = 0;
 *   
 *          switch (event)
 *          {
 *              case WIFI_SMART_CONNECTION_EVENT_CHANNEL_LOCKED:
 *                  //Report the locked channel.
 *                  break;
 *              case WIFI_SMART_CONNECTION_EVENT_TIMEOUT:
 *                  //Report the timeout to the upper layers.
 *                  break;
 *              case WIFI_SMART_CONNECTION_EVENT_INFO_COLLECTED:
 *                  //Save the received information and connect to the target AP, and then call #wifi_smart_connection_deinit() to release the resources.
 *                  wifi_smart_connection_get_result(ssid, &ssid_len, passwd, &passwd_len, NULL, NULL);
 *                 MTK_scan_connect_ap(ssid, passwd);
 *                  wifi_smart_connection_deinit();
 *                  break;
 *          }
 *      }
 *
 *      int32_t mtk_smart_connect(void)
 *      {
 *          if(wifi_smart_connection_init(NULL, 0, smtcn_evt_handler) < 0){
 *              return -1;
 *          }
 *
 *          wifi_smart_connection_start(0);
 *          return 0;
 *     }
 *
 *     int32_t mtk_smart_stop(void)
 *     {
 *         wifi_smart_connection_stop();
 *         return 0;
 *     }
 *
 *    @endcode */

#ifndef __SMTCN_API_H__
#define __SMTCN_API_H__
#include <stdint.h>
#include "wifi_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@defgroup wifi_smtcn_enum Enum
 *@{ */

/** @brief Smart Connection event. */
typedef enum {
    WIFI_SMART_CONNECTION_EVENT_CHANNEL_LOCKED,  /**< Locked channel event. */
    WIFI_SMART_CONNECTION_EVENT_INFO_COLLECTED,  /**< The Smart Connection has finished. */
    WIFI_SMART_CONNECTION_EVENT_TIMEOUT,         /**< Smart Connection timeout. */
} wifi_smart_connection_event_t ;

/** @brief Return values for the Smart Connection API. */
typedef enum {
    WIFI_SMART_CONNECTION_ERROR = -1,      /**< The operation failed. */
    WIFI_SMART_CONNECTION_OK = 0           /**< The operation is successful. */
} wifi_smart_connection_status_t;

/**
 *@} */

/**
* @brief This callback function should be registered through the #wifi_smart_connection_init(), and will be called when a Smart Connection event is received.
* @param[in] event  is the Smart Connection event.
* @param[in] data is the reserved data.
*
* @return  None
*/
typedef void (* wifi_smart_connection_callback_t) (wifi_smart_connection_event_t event, void *data);


/**
* @brief This function registers a callback function to establish the Smart Connection.
*
* @param[in]  key is the user-defined security key, to decrypt the information received through the Smart Connection.
* @param[in]  key_length is the length of the security key.
* @param[in]  callback is a user-defined callback to handle the Smart Connection events.
*
* @return #WIFI_SMART_CONNECTION_OK, if the operation completed successfully.
*/
wifi_smart_connection_status_t wifi_smart_connection_init (const uint8_t *key, const uint8_t key_length, wifi_smart_connection_callback_t  callback);

/**
* @brief This function de-initializes the Smart Connection and releases the resources.
*
* @return  None
*/
void wifi_smart_connection_deinit (void);

/**
* @brief This function starts the Smart Connection. It should be called after #wifi_smart_connection_init() for pre-allocated resources.
*
* @param[in]  timeout_seconds is a user-defined timeout value in seconds.
* It implies smart connection failed once timeout is reached.
*             if timeout_seconds == 0, will never time out
*
* @return #WIFI_SMART_CONNECTION_OK, if the operation completed successfully.
*/
wifi_smart_connection_status_t wifi_smart_connection_start (uint16_t timeout_seconds);

/**
* @brief This function gets the Smart Connection result. Call it once #WIFI_SMART_CONNECTION_EVENT_INFO_COLLECTED is finished, or it will return an error.
*
* @param[out]  ssid is a pointer to the memory where the SSID is stored.
* @param[out]  ssid_length is a pointer to the memory where the length of SSID is stored.
* @param[out]  password is a pointer to the memory where the password is stored.
* @param[out]  password_length is a pointer to the memory where the length of password length is stored.
* @param[out]  tlv_data is a pointer to the memory where the tlv data is stored.
* @param[out]  tlv_data_length is a pointer to the memory where the length of tlv data is stored.
*
* @return #WIFI_SMART_CONNECTION_OK, if the operation completed successfully.
*/
wifi_smart_connection_status_t wifi_smart_connection_get_result (uint8_t *ssid, uint8_t *ssid_length, 
                                            uint8_t *password, uint8_t *password_length, 
                                            uint8_t *tlv_data, uint8_t *tlv_data_length);


/**
* @brief This function is called to inform smart connection task of exiting flag and then the task will automatically release the resources.
*
* @return #WIFI_SMART_CONNECTION_OK, if the operation completed successfully.
*/
wifi_smart_connection_status_t wifi_smart_connection_stop(void);

#ifdef __cplusplus
}
#endif

/**
 * @} */
#endif

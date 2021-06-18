/* Copyright Statement:
 *
 */

#ifndef __MDNS_H__
#define __MDNS_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mDNS
 * @{
 * mDNS API provides interfaces to execute publish service requests.\n
 * @section mDNSResponder_Chapter mDNSResponder
 * mDNSResponder is an open source project for Apple Bonjour under Apache 2.0 license.
 * It allows users to perform DNS-like operations using Multicast DNS (mDNS) and DNS Service Discovery (DNS-SD).
 * In the current SDK, only the mDNS server feature is enabled.
 * @section mDNS_Usage_Chapter How to use this module
 * In the SDK, there are two sets of APIs, one set defined in mdns.h, the other in dns_sd.h.\n
 * - \b The \b mDNS \b APIs
 *  - Support mDNS daemon start/stop/update request on local network.
 *  - Call #mdnsd_start(), #mdnsd_stop() or #mdns_update_interface() to start, stop or update the mDNS daemon.\n
 * - \b The \b DNS_SD \b APIs
 *  - Support register/unregister/update an mDNS service.
 *  - 1. Call #mdnsd_start() to start the main loop of the mDNS daemon.
 *  - 2. Call #TXTRecordCreate() and #TXTRecordSetValue() to create a TXT record.
 *  - 3. Call #DNSServiceRegister() to register an mDNS service to the network.
 *  - 4. Call #DNSServiceUpdateRecord() to update an mDNS service.
 *  - 5. Call #DNSServiceRefDeallocate() to unregister an mDNS service from the network.
 *  - 6. Call #mdnsd_stop() to stop the mDNS daemon.
 *  - Sample code: Please refer to the example in the <sdk_root>/project/mt7687_hdk/apps/mdns_publish_service folder.
 */

/**
 * @brief       This function starts the mDNS daemon.
 * @return      None.
 * @par         Create mDNS daemon task example
 * @code
 *          // mDNS daemon task entry function.
 *          static void mdnsd_entry(void *not_used)
 *          {
 *              printf("mdnsd_entry start.\n");
 *              mdnsd_start();
 *              printf("mdnsd_entry return.\n");
 *              vTaskDelete(NULL);
 *          }
 *
 *          // Create an mDNS daemon task.
 *          if (pdPASS != xTaskCreate(mdnsd_entry,
 *                            MDNSD_TASK_NAME,
 *                            MDNSD_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
 *                            NULL,
 *                            MDNSD_ENTRY_TASK_PRIO,
 *                            NULL)) {
 *              printf("Cannot create mdnsd_task.\n");
 *          }
 * @endcode
 */
void mdnsd_start();


/**
 * @brief       This function stops the mDNS daemon task.
 *              It is a blocking call till its completion or times out after 10 seconds.
 * @return      None.
 */
void mdnsd_stop();

/**
 * @brief       This function updates the network interface after obtaining a new IP address or after resetting the IP address.
 * @return      None.
 * @par         Example of how to update the network interface.
 * @code
 *          // Must update the network interface for mDNS after obtaining a new IP address through AutoIP.
 *          struct dhcp *dhcp = sta_if->dhcp;
 *          if (dhcp->autoip_coop_state == DHCP_AUTOIP_COOP_STATE_ON) {
 *              do {
 *                  vTaskDelay(2 * 1000 / portTICK_PERIOD_MS);
 *              } while (dhcp->state != DHCP_STATE_BOUND && sta_if->autoip->state != AUTOIP_STATE_BOUND);
 *              mdns_update_interface();
 *          }
 *
 *          // Must update the network interface for mDNS after resetting the IP address through lwIP CLI.
 *          mdns_update_interface();
 * @endcode
 */
void mdns_update_interface();

/**
* @}
*/



/* The following content is used in the HomeKit Project. */
#ifdef MTK_HOMEKIT_ENABLE

/**
 *  @brief      set mDNS mode for HomeKit WAC module
 *  @param[in]  mode is #MDNS_AP_MODE or #MDNS_STA_MODE.
 *  @return     None.
 */
#define MDNS_AP_MODE    1

#define MDNS_STA_MODE   2

void mdns_set_mode(int mode);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __MDNS_H__ */

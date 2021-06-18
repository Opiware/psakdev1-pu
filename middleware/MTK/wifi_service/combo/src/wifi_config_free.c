/* Copyright Statement:
 *
 */
/****************************************************************************
    Module Name:
    WiFi  Scan

    Abstract:
    WiFi processor scan result handler for Supplicant

    Revision History:
    Who                     When                 What
    Michael Rong      2015/05/22       Initial
    --------            ----------      ------------------------------------------
***************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_def.h"
#include "wifi_scan.h"
#include "wifi_api.h"
#include "wifi.h"
#include "os.h"
#include "os_util.h"
#include "syslog.h"
#ifdef MTK_MINISUPP_ENABLE
#include "driver_inband.h"
#endif
//#include "wifi_inband.h"
//#include "wifi_private_api.h"

#include "hal_sys.h"
#include "hal_cache.h"

#ifdef MTK_WIFI_DIRECT_ENABLE
#include "wifi_inband.h"
#endif
#include "wifi_os_api.h"
#include "wifi_config_free.h"


CONFIGURE_FREE_CALLBACK g_configure_free_callback = {
	.save_credential = NULL,
	.save_ready = NULL,
};
#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE

void register_configure_free_callback(void *save_credential_func, void *save_ready_func)
{
	g_configure_free_callback.save_credential = (int32_t (*)(P_IOT_CONFIG_FREE_IE cred))save_credential_func;
	g_configure_free_callback.save_ready = (int32_t (*)(uint8_t config_ready))save_ready_func;
}

//
//  ConfigureFree - parse credential for NVRAM Setting
//
int wifi_cf_credential_handler(unsigned int inf, unsigned char *body, int len)
{
    int status = 0; // 0: SUCCESS, -1: Failure
    uint8_t config_ready = 1;
    P_IOT_CONFIG_FREE_IE cred = (P_IOT_CONFIG_FREE_IE)body;

    // Sanity Check
    if (len < sizeof(IOT_CONFIG_FREE_IE)) { // no iwreq CMD(4) needed
        LOG_E(wifi, "ERROR! [ConfigFree] Invalid wlan evt received, len(%d) < %d",
              len, sizeof(IOT_CONFIG_FREE_IE));
        return -1;
    }
#ifdef MTK_MINISUPP_ENABLE
    if (inf >= MAX_INTERFACE_NUM) {
        LOG_E(wifi, "ERROR! [ConfigFree] Wlan evt received from invalid interface(=%d)(MTK_WIFI_REPEATER_ENABLE?).", inf);
        return -1;
    }
#endif /* MTK_MINISUPP_ENABLE */

    if (!g_configure_free_callback.save_credential ||
	  !g_configure_free_callback.save_ready)
    {
        LOG_E(wifi, "ERROR! [ConfigFree] callback not registered yet");
    	return -1;
    }

    // Set nvram configuration by credential
    status = g_configure_free_callback.save_credential(cred);

    // Success - 1. Set NVRAM ConfigFree_Ready, 2. Reboot
    if (status == 0) {
        // Set NVRAM ConfigFree_Ready (0: un-configured, 1: configured)
        if (g_configure_free_callback.save_ready(config_ready) != 0) {
            LOG_E(wifi, "ERROR! [ConfigFree][COMMON] wifi_profile_set_configfree failed");
            status = -1;
        }

        LOG_I(wifi, "[ConfigFree] Successfully. System Reboot!!!");
#ifdef HAL_CACHE_MODULE_ENABLED
        hal_cache_disable();
        hal_cache_deinit();
#endif
#ifdef READY
        hal_sys_reboot(HAL_SYS_REBOOT_MAGIC, WHOLE_SYSTEM_REBOOT_COMMAND);
#endif
    }

    return status;
}
#else
void register_configure_free_callback(void *save_credential_func, void *save_ready_func)
{
    LOG_W(wifi,"Not support Config free callback");
}

int wifi_cf_credential_handler(unsigned int inf, unsigned char *body, int len)
{
    LOG_W(wifi,"Not support config free handler");
    return 0;
}

#endif

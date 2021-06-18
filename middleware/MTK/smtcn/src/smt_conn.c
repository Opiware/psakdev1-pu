/* Copyright Statement:
 *
 */
 
#include "type_def.h"
#include "wifi_api.h"
#include "smt_api.h"
#include "wifi_scan.h"
#include "string.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "task_def.h"
#include "misc.h"

bool wifi_smart_running(void);

void smtcn_evt_handler(wifi_smart_connection_event_t event, void *data)
{
    uint8_t passwd[WIFI_LENGTH_PASSPHRASE + 1] = {0};
    uint8_t ssid[WIFI_MAX_LENGTH_OF_SSID + 1] = {0};
    uint8_t ssid_len = 0;
    uint8_t passwd_len = 0;

    switch (event) {
        case WIFI_SMART_CONNECTION_EVENT_CHANNEL_LOCKED:
            break;
        case WIFI_SMART_CONNECTION_EVENT_TIMEOUT:
            wifi_smart_connection_deinit();
            break;
        case WIFI_SMART_CONNECTION_EVENT_INFO_COLLECTED:
            if(wifi_smart_connection_get_result(ssid, &ssid_len, passwd, &passwd_len, NULL, NULL) == WIFI_SMART_CONNECTION_OK)
            {
                if(wifi_config_set_ssid(WIFI_PORT_STA, ssid, ssid_len) < 0)
                {
                    printf("smt set ssid fail\n");
                    return;
                }
                if (passwd_len != 0) {

                    if((passwd_len >= 8) && (wifi_config_set_wpa_psk_key(WIFI_PORT_STA, passwd, passwd_len) < 0))
                    {
                        printf("smt set wpa psk key fail\n");
                        return;
                    }
                    if(passwd_len == 10 || passwd_len == 26 || passwd_len == 5 || passwd_len == 13) {
                        wifi_wep_key_t wep_key = {{{0}}};
                        if (passwd_len == 10 || passwd_len == 26) {
                            wep_key.wep_key_length[0] = passwd_len / 2;
                            AtoH((char *)passwd, (char *)&wep_key.wep_key[0], (int)wep_key.wep_key_length[0]);
                        } else if (passwd_len == 5 || passwd_len == 13) {
                            wep_key.wep_key_length[0] = passwd_len;
                            memcpy(wep_key.wep_key[0], passwd, passwd_len);
                        }

                        wep_key.wep_tx_key_index = 0;
                        if(wifi_config_set_wep_key(WIFI_PORT_STA, &wep_key) < 0)
                        {
                            printf("smt set wep key fail\n");
                            return;
                        }
                    }

                }

                if(wifi_config_reload_setting() < 0)
                {
                    printf(" warning smt reload fail\n");
                }

                wifi_smart_connection_deinit();
            }
            break;
    }
}

static uint8_t g_key[16];
static uint8_t g_key_len = 0;

static void smntcn_start_thread(void *pvParameters)
{
    if(wifi_smart_connection_init(g_key, g_key_len, smtcn_evt_handler) < 0) {
        printf("smntcn_start_thread fail\n");
    }

    if(wifi_smart_connection_start(0) < 0) {
        printf("wifi_smart_connection_start fail\n");
    }
    
    vTaskDelete(NULL);
}

void mtk_smart_set_key(uint8_t key[],uint8_t key_len)
{
    if(key_len == 16) {
        memset(g_key,0,key_len);
        memcpy(g_key,key,key_len);
        g_key_len = 16;
    }else {
        g_key_len = 0;
    }
}


int32_t mtk_smart_connect(uint8_t key[],uint8_t key_len)
{
    int ret = 0;
    if(!wifi_smart_running())
    {
        if ((ret = xTaskCreate(smntcn_start_thread,
                        "start smnt",
                        512,
                        NULL,
                        TASK_PRIORITY_NORMAL,
                        NULL) )!= pdPASS) {
            printf("mtk_smart_connect fail , ret %d\n",ret);
            return -1;
        }
    }
    return 0;
}


int32_t mtk_smart_stop(void)
{
    return wifi_smart_connection_stop();
}

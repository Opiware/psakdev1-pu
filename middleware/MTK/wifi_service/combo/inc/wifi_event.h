/* Copyright Statement:
 *
 */

#ifndef __WIFI_EVENT_H__
#define __WIFI_EVENT_H__

//#include "type_def.h"
#include "stdint.h"
#include "wifi_api.h"
#include "connsys_profile.h"
#include "memory_attribute.h"

extern const wifi_event_handler_t wifi_rx_event_handler[];

/*[JCB] need check if it is necessary here or move to other files */
#define MAX_INTERFACE_NUM 2

typedef struct __global_event_callback {
    void *priv;
    int (*func)(void *priv, unsigned char evt_id, unsigned char *body, int len);
    unsigned char op_mode;
    unsigned char ready;
} global_event_callback;
extern global_event_callback __process_global_event[];

/* end of copy from inband_queue.h*/
#define COMPACT_RACFG_CMD_WIRELESS_SEND_EVENT WIFI_EVENT_ID_IOT_ASSOCIATED // 0x63, just test w/ E2 ROM

/* linked list to function structure */
typedef struct wifi_event_handler_struct {
    int32_t events;
    wifi_event_handler_t func;
    struct wifi_event_handler_struct *next;
} wifi_event_handler_struct;

int wifi_wlan_evt_n9_log_handler(unsigned int inf, unsigned char *body, int len);
int wifi_wlan_evt_frame_handler(unsigned int inf, unsigned char *body, int len);
int wifi_wlan_evt_handler(unsigned int inf, unsigned char *body, int len);
int wifi_api_set_event_handler(uint8_t enabled, wifi_event_t idx, wifi_event_handler_t handler);
int wifi_wlan_evt_reason_code(unsigned int inf, unsigned char *body, int len);
int wifi_api_event_trigger(uint8_t port, wifi_event_t idx, uint8_t *address, unsigned int length);
int wifi_wlan_probe_request_handler(unsigned int inf, unsigned char *body, int len);
void unregister_preocess_global_event(void);
void register_preocess_global_event(void *priv, void *func, unsigned char op_mode);
int wifi_event_notification(unsigned char port,unsigned char evt_id, unsigned char *body, int len);
void wifi_repeater_wlan_evt_handler(unsigned char *body, int len);
void wifi_wps_wlan_evt_handler(unsigned char *body, int len);


#endif /* __WIFI_EVENT_H__ */

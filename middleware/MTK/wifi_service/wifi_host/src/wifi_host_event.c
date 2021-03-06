/* Copyright Statement:
 *
 */
/****************************************************************************
    Module Name:
    WiFi  Event

    Abstract:
    handle the wifi event from N9 or WiFi Stack

    Revision History:
    Who                     When                 What
    Jinchuan.Bao    2017/02/14           Initial
    --------            ----------      ------------------------------------------
***************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_def.h"
#include "wifi_host_event.h"
#include "wifi.h"
#include "os.h"
#include "os_util.h"
#include "syslog.h"
#include "wifi_host_os_api.h"



#define MAX_EVENT_HD_CNT 16
wifi_event_handler_struct *callback_list_head = NULL;

/* proxy function implementation */
int32_t wifi_event_proxy_handler(wifi_event_t event, uint8_t *payload, uint32_t length)
{
    wifi_event_handler_struct *h = callback_list_head;

    wifi_event_handler_t event_hd[MAX_EVENT_HD_CNT];
    int event_hd_cnt = 0;

    wifi_os_task_enter_critical();
    while (h) {
        if (h->events & (0x01 << event)) {
            //h->func(event, payload, length);
            event_hd[event_hd_cnt] = h->func;
            event_hd_cnt++;
        }
        h = h->next;
    }
    wifi_os_task_exit_critical();

    assert(event_hd_cnt <= MAX_EVENT_HD_CNT);

    while (event_hd_cnt > 0) {
        event_hd_cnt--;
        event_hd[event_hd_cnt](event, payload, length);
    }

    return 1;
}

const wifi_event_handler_t wifi_rx_event_handler[] = {
    wifi_event_proxy_handler,  /* Link Up Event */
    wifi_event_proxy_handler,  /* Scan Complete Event */
    wifi_event_proxy_handler,  /* Disconnect Event */
    wifi_event_proxy_handler,  /* Port Secure Event */
    wifi_event_proxy_handler,  /* Report Beacon/Probe Response Frames */
    wifi_event_proxy_handler,  /* Get Credential event */
    wifi_event_proxy_handler,  /* init done event */
    wifi_event_proxy_handler,  /* frame type choice */
    wifi_event_proxy_handler,  /* Connect fail event */
};

void wifi_set_notification_callback(uint8_t enabled, int32_t events, wifi_event_handler_t callback)
{
    wifi_event_handler_struct *h = callback_list_head;
    wifi_event_handler_struct *p = h;
    wifi_event_handler_struct *prev = h; /* point to previous node of p, but h == p == prev at the beginning  */

    wifi_os_task_enter_critical();

    if (enabled) { /* add */
        while (p) {
            if((p->events == events) && (p->func == callback)) {
                wifi_os_task_exit_critical();
                //LOG_W(wifi, "No need to register the same event and callback.");
                return;
            }
            prev = p;
            p = p->next;
        }

        if (p == NULL) { /* Add a node to the list head */
            wifi_event_handler_struct *n = wifi_os_malloc(sizeof(wifi_event_handler_struct));
            n->events = events;
            n->func = callback;
            n->next = callback_list_head;
            callback_list_head = n;
        }
    } else { /* remove callback */
        while (p) {
            if ((p->func == callback) && (p->events == events)) {
                break;
            }
            prev = p;
            p = p->next;
        }
        if (p) {
            prev->next = p->next;
            if (p == callback_list_head) {
                if (p->next == NULL) {
                    callback_list_head = NULL;
                } else {
                    callback_list_head = p->next;
                }
            }
            wifi_os_free(p);
        } else {
            wifi_os_task_exit_critical();
            //LOG_E(wifi, "No match found.");
            return;
        }
    }

    wifi_os_task_exit_critical();
}


int  wifi_api_set_event_handler(uint8_t enabled, wifi_event_t idx, wifi_event_handler_t handler)
{
    if (idx >= WIFI_EVENT_MAX_NUMBER) {
        return -1;
    }

    wifi_set_notification_callback(enabled, (int)(0x1 << idx), handler);
    return 0;
}


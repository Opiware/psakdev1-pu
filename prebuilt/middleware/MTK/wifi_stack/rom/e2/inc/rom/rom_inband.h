/* Copyright Statement:
 *
 */


#ifndef __ROM_INBAND_H__
#define __ROM_INBAND_H__

#define MAX_WEP_KEY_SIZE_CM4 32
typedef struct _wep_key_cm4 {
    uint8_t ucdefault_key_id;
    uint8_t auckey_0[MAX_WEP_KEY_SIZE_CM4];
    uint8_t uckey_0_len;
    uint8_t auckey_1[MAX_WEP_KEY_SIZE_CM4];
    uint8_t uckey_1_len;
    uint8_t auckey_2[MAX_WEP_KEY_SIZE_CM4];
    uint8_t uckey_2_len;
    uint8_t auckey_3[MAX_WEP_KEY_SIZE_CM4];
    uint8_t uckey_3_len;
} wep_key_cm4_t;

typedef enum _extra_ie_type {
    WIFI_EXTRA_WPS_BEACON_IE = 0,
    WIFI_EXTRA_WPS_PROBE_REQ_IE = 1,
    WIFI_EXTRA_WPS_PROBE_RSP_IE = 2,
    WIFI_EXTRA_WPS_ASSOC_REQ_IE = 3,
    WIFI_EXTRA_WPS_ASSOC_RSP_IE = 4,
#ifdef MTK_WIFI_DIRECT_ENABLE
    WIFI_EXTRA_P2P_BEACON_IE = 5,
    WIFI_EXTRA_P2P_PROBE_REQ_IE = 6,
    WIFI_EXTRA_P2P_PROBE_RSP_IE = 7,
    WIFI_EXTRA_P2P_ASSOC_REQ_IE = 8,
    WIFI_EXTRA_P2P_ASSOC_RSP_IE = 9,
#endif /*MTK_WIFI_DIRECT_ENABLE*/
/* CONFIG_FREE_SUPPORT */
	WIFI_EXTRA_CF_PROBE_REQ_IE = 10,
	WIFI_EXTRA_CF_PROBE_RSP_IE = 11, 

} extra_ie_type_t;

typedef struct _extra_ie {
    uint8_t port;
    uint8_t type; /* extra_ie_type */
    uint8_t rsv[2];
    uint32_t extra_ie_len;
#ifndef __CC_ARM
    uint8_t extra_ie[0];
#else
    uint8_t extra_ie[];
#endif
} extra_ie_t;

#endif

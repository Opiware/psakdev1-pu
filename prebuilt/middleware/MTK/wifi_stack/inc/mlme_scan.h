/* Copyright Statement:
 *
 */
#ifndef __MLME_SCAN_H__

#define __MLME_SCAN_H__

typedef struct
{
    unsigned char ssid[32];
    unsigned char ssid_len;
    unsigned char bssid[6];
    unsigned char channel;
    char     auth_mode;
    char     enc_type;
    char     rssi;
}SCAN_ITEM_T;

#endif

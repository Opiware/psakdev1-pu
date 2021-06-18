/* Copyright Statement:
 *
 */

#ifndef __CONNSYS_PROFILE_H__
#define __CONNSYS_PROFILE_H__
#include "cm4_type.h"

#pragma pack(push, 1)

#define WIFI_PROFILE_PDA_HEADER_LEN     (12)

//#define MAX_LEN_OF_SSID                 (32)

// copy from N9 wifi_uni_mac_7636/rom/include/iot/rt_bora.h

typedef struct _CIPHER_KEY {
    uint8_t   Key[16];            // right now we implement 4 keys, 128 bits max
    uint8_t   RxMic[8];           // make alignment
    uint8_t   TxMic[8];
    uint8_t   TxTsc[6];           // 48bit TSC value
    uint8_t   RxTsc[6];           // 48bit TSC value
    uint8_t   CipherAlg;          // 0-none, 1:WEP64, 2:WEP128, 3:TKIP, 4:AES, 5:CKIP64, 6:CKIP128
    uint8_t   KeyLen;
    uint8_t   BssId[6];
    uint8_t   Type;               // Indicate Pairwise/Group when reporting MIC error
} CIPHER_KEY,*PCIPHER_KEY;

typedef struct {
    unsigned char first_channel;
    unsigned char num_of_ch;
    unsigned char channel_prop; //0: Active, 1: Passive
    unsigned char tx_power; // 4-align and could be used to extend channel_prop
} ch_desc_t;

typedef struct {
    unsigned char num_bg_band_triplet;
    unsigned char num_a_band_triplet;
    ch_desc_t triplet[]; // BGBand Triplet followed by Aband Triplet
} ch_list_t;

typedef struct {
    uint8_t opmode;
    uint8_t country_region;
    uint8_t country_region_a_band;
    uint8_t country_code[4];
    uint8_t radio_off;
    uint8_t dbg_level;
    uint16_t rts_threshold;
    uint16_t frag_threshold;

    uint8_t sta_local_admin_mac;
    uint8_t sta_ip_addr[4];
    uint8_t sta_mac_addr[6];
    uint8_t sta_ssid[32];
    uint8_t sta_ssid_len;
    uint8_t sta_bss_type;
    uint8_t sta_channel;
    uint8_t sta_bw;
    uint8_t sta_wireless_mode;
    uint8_t sta_ba_decline;
    uint8_t sta_auto_ba;
    uint8_t sta_ht_mcs;
    uint8_t sta_ht_ba_win_size;
    uint8_t sta_ht_gi;
    uint8_t sta_ht_protect;
    uint8_t sta_ht_ext_ch;
    uint8_t sta_wmm_capable;
    uint8_t sta_listen_interval;
    uint8_t sta_auth_mode;
    uint8_t sta_encryp_type;
    uint8_t sta_wpa_psk[64];
    uint8_t sta_wpa_psk_len;
    uint8_t sta_pmk[32];
    uint8_t sta_pair_cipher;
    uint8_t sta_group_cipher;
    uint8_t sta_default_key_id;
    uint8_t sta_ps_mode;
    uint8_t sta_keep_alive_period;

    uint8_t ap_local_admin_mac;
    uint8_t ap_ip_addr[4];
    uint8_t ap_mac_addr[6];
    uint8_t ap_ssid[32];
    uint8_t ap_ssid_len;
    uint8_t ap_channel;
    uint8_t ap_bw;
    uint8_t ap_wireless_mode;
    uint8_t ap_auto_ba;
    uint8_t ap_ht_mcs;
    uint8_t ap_ht_ba_win_size;
    uint8_t ap_ht_gi;
    uint8_t ap_ht_protect;
    uint8_t ap_ht_ext_ch;
    uint8_t ap_wmm_capable;
    uint8_t ap_dtim_period;
    uint8_t ap_hide_ssid;
    uint8_t ap_auto_channel_select;
    uint8_t ap_auth_mode;
    uint8_t ap_encryp_type;
    uint8_t ap_wpa_psk[64];
    uint8_t ap_wpa_psk_len;
    uint8_t ap_pmk[32];
    uint8_t ap_pair_cipher;
    uint8_t ap_group_cipher;
    uint8_t ap_default_key_id;

    // "scan channel table" and "regulatory table"
    unsigned char bg_band_entry_num;
    ch_desc_t bg_band_triple[10];
    unsigned char a_band_entry_num;
    ch_desc_t a_band_triple[10];
    uint8_t ap_beacon_disable;
    uint8_t forwarding_zero_copy;

    /* These are for MBSS support, but not exist trunk (it's customer feature), however,
            we have to add them here due to N9 FW has them (only one version of N9 FW)
         */
    // TODO: How to solve it in the future...Michael
    uint8_t mbss_enable;
    uint8_t mbss_ssid1[32];
    uint8_t mbss_ssid_len1;
    uint8_t mbss_ssid2[32];
    uint8_t mbss_ssid_len2;

    uint8_t config_free_ready;
    uint8_t config_free_enable;
    uint8_t sta_fast_link;
    uint8_t beacon_lost_time;
    uint8_t apcli_40mhz_auto_upbelow;
    uint8_t wifi_privilege_enable;
    uint8_t sta_keep_alive_packet;
} sys_cfg_t;

#pragma pack(pop)

#endif // #ifndef __CONNSYS_PROFILE_H__


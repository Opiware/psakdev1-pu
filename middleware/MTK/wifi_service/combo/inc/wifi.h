/* Copyright Statement:
 *
 */

#ifndef __WIFI_H__
#define __WIFI_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IF_NAME_SIZE    16

#define IW_WPAS_APCLI_RELOAD_FLAG           0x0102 //align N9

typedef struct {
    int32_t       value;
    uint8_t       fixed;
    uint8_t       disabled;
    uint16_t      flags;
} iw_param_t;

typedef struct {
    int32_t       m;
    int16_t       e;
    uint8_t       i;
    uint8_t       flags;
} iw_freq_t;

typedef struct {
    void *pointer;
    uint16_t length;
    uint16_t flags;
} iw_point_t;

typedef struct {
    uint8_t     sa_family;
    int8_t      sa_data[14];
} sockaddr;

#if defined(__ICCARM__)
__packed struct iw_quality {
#else
struct  __attribute__((packed))    iw_quality {
#endif
    uint8_t     qual;
    uint8_t     level;
    uint8_t     noise;
    uint8_t     updated;
};

typedef union {
    char        name[IF_NAME_SIZE];
    iw_point_t  essid;
    iw_param_t  nwid;
    iw_freq_t   freq;
    iw_param_t  sens;
    iw_param_t  bitrate;
    iw_param_t  txpower;
    iw_param_t  rts;
    iw_param_t  frag;
    uint32_t    mode;
    iw_param_t  retry;
    iw_point_t  encoding;
    iw_param_t  power;
    struct iw_quality  qual;
    sockaddr    ap_addr;
    sockaddr    addr;
    iw_point_t  data;
    iw_param_t  param;
} iwreq_data_t;

#ifdef __cplusplus
}
#endif


#endif  /* __WIFI_H__ */

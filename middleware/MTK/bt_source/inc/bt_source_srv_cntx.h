/* Copyright Statement:
 *
 */

#ifndef __BT_SOURCE_SRV_CNTX_H__
#define __BT_SOURCE_SRV_CNTX_H__

#include "stdint.h"
#include "bt_type.h"
#include "FreeRTOS.h"
#include "bt_codec.h"
#include "bt_a2dp.h"
#include "bt_avrcp.h"
#include "bt_source_srv_a2dp.h"
#include "bt_source_srv_avrcp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SOURCE_SRV_MAX_DEVICE_NUMBER          (1)
#define BT_SOURCE_SRV_A2DP_CONN_BIT              (1 << 0)
#define BT_SOURCE_SRV_AVRCP_CONN_BIT             (1 << 1)
#define BT_SOURCE_SRV_INVALID_HD                 (0x00)


typedef enum {
    BT_SOURCE_SRV_DEVICE_A2DP, /* 0 */
    BT_SOURCE_SRV_DEVICE_AVRCP, /* 1 */
    BT_SOURCE_SRV_DEVICE_ADDR, /* 2 */
    BT_SOURCE_SRV_DEVICE_UNUSED, /* 3 */
    BT_SOURCE_SRV_DEVICE_USED, /* 4 */

    BT_SOURCE_SRV_DEVICE_TOTAL
} bt_source_srv_device_type_t;


typedef struct {
    uint32_t timestamp;
    bt_source_srv_a2dp_state_t state;
    bt_media_handle_t *med_handle;
} bt_source_srv_profile_t;

typedef struct {
    bt_source_srv_profile_t profile;
    bt_a2dp_codec_capability_t codec;
} SourceProfileA2dp;

typedef struct {
    bt_bd_addr_t dev_addr;
    uint16_t conn_bit;

    SourceProfileA2dp a2dp;
    uint32_t a2dp_hd;
    bt_a2dp_role_t a2dp_role;
    
    bt_source_srv_avrcp_state_t avrcp_state;
    uint32_t avrcp_hd;
    bt_avrcp_role avrcp_role;
    
    bt_avrcp_media_play_status_event_t avrcp_play_status;
} bt_source_srv_device_t;

typedef struct {  
    bt_source_srv_device_t source_dev[BT_SOURCE_SRV_MAX_DEVICE_NUMBER];
} bt_source_srv_context_t;


void bt_source_srv_cntx_init(void);
bt_source_srv_context_t *bt_source_srv_get_context(void);
bt_source_srv_device_t *bt_source_srv_get_device(bt_source_srv_device_type_t type, const void *param);
void bt_source_srv_reset_device(bt_source_srv_device_t *dev);
void bt_source_srv_reset_a2dp_info(bt_source_srv_device_t *dev);
void bt_source_srv_reset_avrcp_info(bt_source_srv_device_t *dev);


#ifdef __cplusplus
}
#endif

#endif /*__BT_SOURCE_SRV_CNTX_H__*/


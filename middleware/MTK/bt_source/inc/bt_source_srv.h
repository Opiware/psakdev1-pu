/* Copyright Statement:
 *
 */

#ifndef __BT_SOURCE_SRV_H__
#define __BT_SOURCE_SRV_H__
#include <stdint.h>
#include <stdbool.h>
#ifndef WIN32
#include <syslog.h>
#else
#include "osapi.h"
#endif
#include "FreeRTOSConfig.h"
#include "bt_type.h"
#include "bt_avrcp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SOURCE_SRV_CB_MAX_NUM                 (5)
#define BT_SOURCE_SRV_SBC_SHARE_SIZE             (40*1024)
#define BT_SOURCE_SRV_A2DP_PAYLOAD_SIZE          (1*1024)

typedef struct {
    uint32_t handle;
    bt_status_t  result;
    bt_bd_addr_t address;
} bt_source_srv_a2dp_connect_t;

typedef struct {
    uint32_t handle;
    bt_status_t result;
} bt_source_srv_a2dp_start_cnf_t;

typedef struct {
    uint32_t handle;
} bt_source_srv_a2dp_start_ind_t;

typedef struct {
    uint32_t handle;
    bt_avrcp_operation_id_t op_id;
} bt_source_srv_avrcp_operation_ind_t;

typedef struct{
    uint32_t handle;      /**< The connection handle of the AVRCP. */
    uint8_t  volume;      /**< The absolute volume. Values is a percentage from 0% to 100%. Other values are invalid. */
}bt_source_srv_avrcp_change_volume_cnf_t;

typedef struct{
    uint32_t handle;     /**< The connection handle of the AVRCP. */   
    bt_status_t  result;
    bt_bd_addr_t address;
}bt_source_srv_avrcp_connect_t;

typedef enum {
    BT_SOURCE_SRV_EVENT_A2DP_CONNECT = 0,     /* CNF of bt_source_srv_a2dp_connect. */
    BT_SOURCE_SRV_EVENT_A2DP_DISCONNECT = 1,  /* CNF of bt_source_srv_a2dp_disconnect. */
    BT_SOURCE_SRV_EVENT_A2DP_START_CNF = 2,   /* CNF of bt_source_srv_a2dp_start. */
    BT_SOURCE_SRV_EVENT_A2DP_STOP_CNF = 3,    /* CNF of bt_source_srv_a2dp_stop. */
    BT_SOURCE_SRV_EVENT_AVRCP_CONNECT = 4,    /* CNF of bt_source_srv_avrcp_connect. */
    BT_SOURCE_SRV_EVENT_AVRCP_DISCONNECT = 5, /* CNF of bt_source_srv_avrcp_disconnect. */
    BT_SOURCE_SRV_EVENT_AVRCP_OPERATION_IND = 6,    /* like play pause pre next. */
    BT_SOURCE_SRV_EVENT_AVRCP_CHANGE_VOLUME_CNF = 7,/* CNF of @bt_source_srv_avrcp_change_volume. */
    BT_SOURCE_SRV_EVENT_AVRCP_REMOTE_VOLUME_IND = 8,/* IND of volume setting comes from remote device. */
    BT_SOURCE_SRV_EVENT_A2DP_START_IND = 9,   /* IND of A2DP Start comes from remote device. */
    BT_SOURCE_SRV_EVENT_A2DP_STOP_IND = 10,   /* IND of A2DP Stop comes from remote device. */
    /* add before this event. */
    BT_SOURCE_SRV_EVENT_ALL
} bt_source_srv_event_t;

typedef bt_source_srv_a2dp_connect_t bt_source_srv_a2dp_disconnect_t;
typedef bt_source_srv_a2dp_start_cnf_t bt_source_srv_a2dp_stop_cnf_t;
typedef bt_source_srv_a2dp_start_ind_t bt_source_srv_a2dp_stop_ind_t;
typedef bt_source_srv_avrcp_connect_t bt_source_srv_avrcp_disconnect_t;
typedef bt_source_srv_avrcp_change_volume_cnf_t bt_source_srv_avrcp_remote_volume_ind_t;

typedef void(* bt_source_srv_notify_callback)(bt_source_srv_event_t event_id, void *param);

void bt_source_srv_init(void);
bt_status_t bt_source_srv_register_callback(bt_source_srv_notify_callback callback);
bt_status_t bt_source_srv_deregister_callback(bt_source_srv_notify_callback callback);
bt_status_t bt_source_srv_event_callback(bt_source_srv_event_t event_id, void *param);
bt_status_t bt_source_srv_avrcp_change_volume(uint32_t handle, uint8_t volume);

bt_status_t bt_source_srv_a2dp_start(uint32_t handle);
bt_status_t bt_source_srv_a2dp_stop(uint32_t handle);
bt_status_t bt_source_srv_a2dp_connect(bt_bd_addr_t *address);
bt_status_t bt_source_srv_a2dp_disconnect(uint32_t handle);

bt_status_t bt_source_srv_avrcp_connect(bt_bd_addr_t *device_addr);
bt_status_t bt_source_srv_avrcp_disconnect(uint32_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SOURCE_SRV_H__ */


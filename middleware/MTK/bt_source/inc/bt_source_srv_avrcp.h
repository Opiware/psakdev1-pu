/* Copyright Statement:
 *
 */

#ifndef __BT_SOURCE_SRV_AVRCP_H__
#define __BT_SOURCE_SRV_AVRCP_H__

#include <stdint.h>
#include "bt_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BT_SOURCE_SRV_AVRCP_DISCONNECTED = 0,
    BT_SOURCE_SRV_AVRCP_CONNECTED,
    BT_SOURCE_SRV_AVRCP_PLAY,
    BT_SOURCE_SRV_AVRCP_STOP,

    BT_SOURCE_SRV_AVRCP_TOTAL
} bt_source_srv_avrcp_state_t;


bt_status_t bt_source_srv_avrcp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);




#ifdef __cplusplus
}
#endif

#endif

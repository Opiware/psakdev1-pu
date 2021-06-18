/* Copyright Statement:
 *
 */

#ifndef BT_SINK_SRV_AWS_SYSTEM_H
#define BT_SINK_SRV_AWS_SYSTEM_H
#include "bt_sink_srv.h"

#ifdef __BT_AWS_SUPPORT__
//bt_sink_srv_status_t bt_sink_srv_aws_system_send_key(bt_sink_srv_key_information_t* key);
bt_sink_srv_status_t bt_sink_srv_aws_system_send_power_off(void);
bt_sink_srv_status_t bt_sink_srv_aws_system_send_sink_action(bt_sink_srv_action_t action);
bt_sink_srv_status_t bt_sink_srv_aws_system_send_sink_state(bt_sink_srv_state_t state);
#endif /*__BT_AWS_SUPPORT__*/

#endif /* BT_SINK_SRV_AWS_SYSTEM_H */


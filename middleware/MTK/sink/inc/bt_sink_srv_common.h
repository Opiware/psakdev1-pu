/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_COMMON_H__
#define __BT_SINK_SRV_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bt_sink_srv.h"

#ifdef __cplusplus
extern "C" {
#endif

extern bt_sink_srv_features_config_t bt_sink_srv_features_config;

void bt_sink_srv_config_features(bt_sink_srv_features_config_t *features);

const bt_sink_srv_features_config_t *bt_sink_srv_get_features_config(void);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_COMMON_H__ */

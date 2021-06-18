/* Copyright Statement:
 *
 */

#ifndef __BT_INIT_H__
#define __BT_INIT_H__


#ifdef __cplusplus
extern "C" {
#endif
#include "bt_gap.h"
extern void bt_task(void * arg);

void bt_create_task(void);

extern bt_gap_config_t gnss_bt_custom_config;

#ifdef __cplusplus
}
#endif

#endif //__BT_INIT_H__


/* Copyright Statement:
 *
 */

#ifndef __COMMON_DISPATCH_H__
#define __COMMON_DISPATCH_H__

#include "bt_gap.h"
#include "bt_hfp.h"
#include "bt_a2dp.h"
#include "bt_avrcp.h"
#include "bt_gap_le.h"
#include "stdint.h"
#include "stdbool.h"

typedef uint8_t bt_common_callback_mode_t;
#define BQB (0)
#define TF (1)
#define CLM (2)
#define SINK (3)

bool bt_common_callback_set_mode(bt_common_callback_mode_t mode);

bt_common_callback_mode_t bt_common_callback_get_mode();


#endif /*__COMMON_DISPATCH_H__*/





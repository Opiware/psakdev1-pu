/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_RESOURCE_H__
#define __BT_SINK_SRV_RESOURCE_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MTK_DEBUG_LEVEL_INFO)
#define __BT_SINK_SRV_DEBUG_INFO__
#define __BT_SINK_SRV_TRACE__
#endif

#ifndef WIN32
#define __BT_SINK_SRV_AM_SUPPORT__
#define __BT_SINK_SRV_NVDM_SUPPORT__
#endif /* WIN32 */
#ifdef MTK_BT_AWS_ENABLE
#define __BT_SINK_SRV_AWS_SUPPORT__
#endif

/*
  * Timer ID
  */
#define BT_SINK_SRV_TIMER_BASE          0x01000000
#define BT_SINK_SRV_TIMER_CM_DISCOVERABLE (BT_SINK_SRV_TIMER_BASE + 1)
#define BT_SINK_SRV_TIMER_CM_REQUEST_DELAY (BT_SINK_SRV_TIMER_BASE + 2)
#define BT_SINK_SRV_TIMER_CM_PROFILE_NOTIFY (BT_SINK_SRV_TIMER_BASE + 3)
#define BT_SINK_SRV_TIMER_HF_AUDIO_DISC   (BT_SINK_SRV_TIMER_BASE + 11)
#define BT_SINK_SRV_TIMER_HF_AUDIO_CONN   (BT_SINK_SRV_TIMER_BASE + 12)
#define BT_SINK_SRV_TIMER_DUT_MODE   (BT_SINK_SRV_TIMER_BASE + 21)

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_RESOURCE_H__ */

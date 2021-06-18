/* Copyright Statement:
 *
 */

#ifndef __HAL_WEAK_H__
#define __HAL_WEAK_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAL_RTC_MODULE_ENABLED
extern void hal_rtc_deinit(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HAL_WEAK_H__ */

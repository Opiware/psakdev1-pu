/* Copyright Statement:
 *
 */

#ifndef __AM_MAIN_H__
#define __AM_MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "queue.h"

#define AM_RING_BUFFER_LEN   (16*1024)
#define AM_RING_BUFFER_SIZE  (AM_RING_BUFFER_LEN)


#define AM_ERR_SUCCESS_7TH            (7)
#define AM_ERR_SUCCESS_6TH            (6)
#define AM_ERR_SUCCESS_5TH            (5)
#define AM_ERR_SUCCESS_4TH            (4)
#define AM_ERR_SUCCESS_3RD            (3)
#define AM_ERR_SUCCESS_2ND            (2)
#define AM_ERR_SUCCESS_1ST            (1)
#define AM_ERR_SUCCESS_OK             (0)
#define AM_ERR_FAIL_1ST               (-1)
#define AM_ERR_FAIL_2ND               (-2)
#define AM_ERR_FAIL_3RD               (-3)
#define AM_ERR_FAIL_4TH               (-4)
#define AM_ERR_FAIL_5TH               (-5)
#define AM_ERR_FAIL_6TH               (-6)
#define AM_ERR_FAIL_7TH               (-7)


#ifndef WIN32_UT
#define AM_TASK_STACK_SIZE   (512)
#define AM_TASK_PRIORITY     (6)
#define AM_EXPIRE_TIMER_MAX  (10)
#define AM_TIMER_PERIOD      (500)
#define AM_TIMER_ID          (1)
extern QueueHandle_t g_xQueue_am;
#endif

#ifndef WIN32_UT
void am_task_create(void);
void am_task_main(void *pvParameters);
#else
void am_task_main(void);
#endif

#ifdef RTOS_TIMER
void aud_timer_callback(TimerHandle_t pxTimer);
#endif

#ifdef __cplusplus
}
#endif

#endif /*__AM_MAIN_H__*/


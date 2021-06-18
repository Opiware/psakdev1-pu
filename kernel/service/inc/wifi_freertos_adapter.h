/* Copyright Statement:
 *
 */
 
#ifndef __WIFI_OS_ADAPTER_H__
#define __WIFI_OS_ADAPTER_H__
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"
#include "timers.h"
#include "portmacro.h"

typedef QueueHandle_t       os_queue_t;
typedef SemaphoreHandle_t   os_semaphore_t;
typedef TimerHandle_t       os_tmr_t;
typedef TaskHandle_t        os_task_t;

#define os_queue_full       errQUEUE_FULL
#define os_queue_empty      errQUEUE_EMPTY

#define os_false            pdFALSE
#define os_true             pdTRUE
#define os_pass             os_true
#define os_fail             os_false
#define os_port_base_type   portBASE_TYPE


#endif


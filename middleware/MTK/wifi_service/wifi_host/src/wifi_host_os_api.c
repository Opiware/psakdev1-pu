/* Copyright Statement:
 *
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "portmacro.h"
#include "queue.h"
#include <timers.h>
#include <string.h>
#include "wifi_host_os_api.h"

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
os_queue_t wifi_os_queue_create( uint32_t queue_len, uint32_t item_size)
{
    return (os_queue_t) xQueueCreate(queue_len, item_size);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_queue_delete(os_queue_t queue)
{
    vQueueDelete(queue);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
uint32_t wifi_os_queue_get_space( const os_queue_t queue )
{
    assert(queue);

    return (uint32_t)uxQueueSpacesAvailable(queue);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_queue_receive(os_queue_t queue, void *buf, struct timeval *wait_time)
{
    assert(queue);

    TickType_t ticks;

    if(wait_time == NULL){
        ticks = portMAX_DELAY;
    }else{
        ticks = (wait_time->tv_sec * 1000 + wait_time->tv_usec / 1000) / portTICK_PERIOD_MS;
    }

    if(pdTRUE == xQueueReceive(queue, buf, ticks))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_queue_send(os_queue_t queue, void *item, struct timeval *wait_time)
{
    assert(queue);

    TickType_t ticks;

    if(wait_time == NULL){
        ticks = portMAX_DELAY;
    }else{
        ticks = (wait_time->tv_sec * 1000 + wait_time->tv_usec / 1000) / portTICK_PERIOD_MS;
    }

    if(pdTRUE == xQueueSend(queue, item, ticks))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_queue_send_front(os_queue_t queue, void *item, struct timeval *wait_time)
{
    assert(queue);

    TickType_t ticks;

    if(wait_time == NULL){
        ticks = portMAX_DELAY;
    }else{
        ticks = (wait_time->tv_sec * 1000 + wait_time->tv_usec / 1000) / portTICK_PERIOD_MS;
    }

    if(pdTRUE == xQueueSendToFront(queue, item, ticks))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_queue_send_from_isr(os_queue_t queue, void *item)
{
    assert(queue);

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(pdPASS == xQueueSendToBackFromISR(queue, item, &xHigherPriorityTaskWoken))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_queue_send_front_from_isr(os_queue_t queue, void *item)
{
    assert(queue);

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(pdPASS == xQueueSendToFrontFromISR(queue, item, &xHigherPriorityTaskWoken))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_receive_from_isr(os_queue_t queue, void *buf)
{
    assert(queue);

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(pdPASS == xQueueReceiveFromISR( queue, buf, &xHigherPriorityTaskWoken))
        return 0;

    return -1;
}

#if 0

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
os_semaphore_t wifi_os_semphr_create_mutex(void)
{
    return (os_semaphore_t) xSemaphoreCreateMutex();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
os_semaphore_t wifi_os_semphr_create_binary(void)
{
    return (os_semaphore_t) xSemaphoreCreateBinary();
}


/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_semphr_take(os_semaphore_t semphr, struct timeval *wait_time)
{
    assert(semphr);

    TickType_t ticks;

    if(wait_time == NULL){
        ticks = portMAX_DELAY;
    }else{
        ticks = (wait_time->tv_sec * 1000 + wait_time->tv_usec / 1000) / portTICK_PERIOD_MS;
    }

    if(pdTRUE == xSemaphoreTake((SemaphoreHandle_t)semphr, ticks))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_semphr_give(os_semaphore_t semphr)
{
    assert(semphr);

    if(pdTRUE == xSemaphoreGive((SemaphoreHandle_t)semphr))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_semphr_take_from_isr(os_semaphore_t semphr)
{
    assert(semphr);

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(pdTRUE == xSemaphoreTakeFromISR((SemaphoreHandle_t)semphr, &xHigherPriorityTaskWoken))
        return 0;

    return -1;    
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_semphr_give_from_isr(os_semaphore_t semphr)
{
    assert(semphr);
    
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(pdTRUE == xSemaphoreGiveFromISR((SemaphoreHandle_t)semphr, &xHigherPriorityTaskWoken))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_semphr_delete(os_semaphore_t semphr)
{
    assert(semphr);
    vSemaphoreDelete((SemaphoreHandle_t)semphr);
}
#endif
/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
os_tmr_t wifi_os_timer_init(char *name, 
                               struct timeval *expires,
                               UBaseType_t auto_reload,
                               timer_handle_t handler
                               )
{
    TickType_t ticks;

    if(expires == NULL){
        return NULL;
    }else{
        ticks = (expires->tv_sec * 1000 + expires->tv_usec / 1000) / portTICK_PERIOD_MS;
    }

    return xTimerCreate(name, ticks, auto_reload, NULL, handler);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_timer_deinit(os_tmr_t timer)
{
    assert(timer);

    if(pdPASS == xTimerDelete(timer, (TickType_t)0))
        return -1;

    return 0;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_timer_start(os_tmr_t timer)
{
    assert(timer);

    if(pdPASS == xTimerStart(timer, (TickType_t)0))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_timer_stop(os_tmr_t timer)
{
    assert(timer);

    if(pdPASS == xTimerStop(timer, (TickType_t)0))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void switch_context(void)
{
    taskYIELD();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
int32_t wifi_os_task_create(task_func_t handler,
                        char *name,
                        uint16_t stack_size,
                        void *params,
                        UBaseType_t prio,
                        os_task_t *task_handle
                        )
{
    if(pdPASS == xTaskCreate(handler,name,stack_size/4,params,prio,task_handle))
        return 0;

    return -1;
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_task_delete(os_task_t task)
{
    vTaskDelete(task);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_task_sleep(uint32_t ms)
{
    vTaskDelay((TickType_t) (ms/portTICK_PERIOD_MS));
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_task_enter_critical(void)
{
    taskENTER_CRITICAL();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_task_exit_critical(void)
{
    taskEXIT_CRITICAL();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
os_task_t wifi_os_task_get_handle(void)
{
    return xTaskGetCurrentTaskHandle();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
char * wifi_os_task_get_name(os_task_t task_handle)
{
    return pcTaskGetTaskName(task_handle);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
BaseType_t wifi_os_task_get_scheduler_state(void)
{
    return xTaskGetSchedulerState();
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void* wifi_os_malloc(size_t size)
{
    return pvPortMalloc(size);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void* wifi_os_zalloc(size_t size)
{
    return pvPortCalloc(1, size);
}

/**
* @brief WiFi OS Adapter Layer API for internal usage, not open for other module or user
* @param
* @return
*/
void wifi_os_free(void *mem)
{
    vPortFree(mem);
}

size_t wifi_os_get_free_heap_size(void)
{
    return xPortGetFreeHeapSize();
}

#if 0
void* wifi_os_memcpy(void* dest, const void* src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int wifi_os_memcmp(const void* buf1, const void* buf2, uint32_t size)
{
    return memcmp(buf1, buf2, size);
}

void* wifi_os_memset(void* buf, uint8_t ch, uint32_t size)
{
    return memset(buf, ch, size);
}

void* wifi_os_memmove(void* dest, const void* src, uint32_t size)
{
    return memmove(dest, src, size);
}
#endif

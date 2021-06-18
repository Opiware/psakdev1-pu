/* Copyright Statement:
 *
 */

#ifndef __WIFI_OS_API_H__
#define __WIFI_OS_API_H__

/**
 * This header file describes the apis which might have different implementation if use differnt platform.
 * Once change the platform, these api need to be implemented by user. */

#include <stdbool.h>
#include <stdint.h>
#include "wifi_freertos_adapter.h"

#if defined(__GNUC__)
#include <sys/time.h>
#elif defined(__ICCARM__) || defined(__CC_ARM)
#if !LWIP_TIMEVAL_PRIVATE
struct timeval {
  long      tv_sec;
  long      tv_usec;
};
#endif
#endif

typedef void (*timer_handle_t)(os_tmr_t);
typedef void (*task_func_t)(void *);

os_queue_t wifi_os_queue_create( uint32_t queue_len, uint32_t item_size);
void wifi_os_queue_delete(os_queue_t queue);
int32_t wifi_os_queue_receive(os_queue_t queue, void *buf, struct timeval *wait_time);
int32_t wifi_os_queue_send(os_queue_t queue, void *item, struct timeval *wait_time);
int32_t wifi_os_queue_send_front(os_queue_t queue, void *item, struct timeval *wait_time);
int32_t wifi_os_queue_send_from_isr(os_queue_t queue, void *item);
int32_t wifi_os_queue_send_front_from_isr(os_queue_t queue, void *item);
int32_t wifi_os_receive_from_isr(os_queue_t queue, void *buf);
uint32_t wifi_os_queue_get_space( const os_queue_t queue );

os_semaphore_t wifi_os_semphr_create_mutex(void);
os_semaphore_t wifi_os_semphr_create_binary(void);
int32_t wifi_os_semphr_take(os_semaphore_t semphr, struct timeval *wait_time);
int32_t wifi_os_semphr_give(os_semaphore_t semphr);
int32_t wifi_os_semphr_take_from_isr(os_semaphore_t semphr);
int32_t wifi_os_semphr_give_from_isr(os_semaphore_t semphr);
void wifi_os_semphr_delete(os_semaphore_t semphr);

os_tmr_t wifi_os_timer_init(char *name, struct timeval *expires, UBaseType_t auto_reload, timer_handle_t handler);
int32_t wifi_os_timer_deinit(os_tmr_t timer);
int32_t wifi_os_timer_start(os_tmr_t timer);
int32_t wifi_os_timer_stop(os_tmr_t timer);

int32_t wifi_os_task_create(task_func_t handler,
                        char *name,
                        uint16_t stack_size,
                        void *params,
                        UBaseType_t prio,
                        os_task_t *task_handle
                        );
void wifi_os_task_delete(os_task_t task);
void wifi_os_task_sleep(uint32_t ms);
void wifi_os_task_enter_critical(void);
void wifi_os_task_exit_critical(void);
os_task_t wifi_os_task_get_handle(void);
char * wifi_os_task_get_name(os_task_t task_handle);
BaseType_t wifi_os_task_get_scheduler_state(void);


void* wifi_os_malloc(size_t size);
void* wifi_os_zalloc(size_t size);
void wifi_os_free(void *mem);
size_t wifi_os_get_free_heap_size(void);

void switch_context(void);

#endif /* __WIFI_OS_API_H__ */


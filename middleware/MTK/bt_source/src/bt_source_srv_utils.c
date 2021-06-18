/* Copyright Statement:
 *
 */

#ifdef WIN32
#include <osapi.h>
#else
#include "FreeRTOS.h"
#include "timers.h"
#endif /* WIN32 */
#include <string.h>
#include <stdarg.h>
#include "bt_source_srv_utils.h"
#include "bt_a2dp.h"

log_create_module(source_srv, PRINT_LEVEL_INFO);


#ifndef WIN32
SemaphoreHandle_t bt_source_srv_mutex = NULL;

void bt_source_srv_create_mutex(void)
{
    bt_source_srv_mutex = xSemaphoreCreateRecursiveMutex();    
    bt_source_srv_report("[source][Mutex] sempphonre mutex: 0x%x ", bt_source_srv_mutex);
    return;
}

void bt_source_srv_take_mutex(void)
{
    SemaphoreHandle_t mutex = bt_source_srv_mutex;

    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return;
    }
    
    if (mutex!= NULL) {
        xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
    }
}

void bt_source_srv_give_mutex(void)
{
    SemaphoreHandle_t mutex = bt_source_srv_mutex;

    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return; 
    }
    
    if (mutex!= NULL) {
        xSemaphoreGiveRecursive(mutex);
    }
}

void  bt_source_srv_delete_mutex(void)
{
    vSemaphoreDelete(bt_source_srv_mutex);
}
#endif

void *bt_source_srv_memory_alloc(uint16_t size)
{
#ifdef WIN32
    void *memory = (void *)malloc(size);
#else
    void *memory = (void *)pvPortMalloc(size);
#endif /* WIN32 */
    bt_source_srv_memset(memory, 0, size);
    return memory;
}

void bt_source_srv_memory_free(void *point)
{
    if (point) {
#ifdef WIN32
        free(point);
#else
        vPortFree(point);
#endif /* WIN32 */
    }
}

void *bt_source_srv_memset(void *ptr, int32_t value, uint32_t num)
{
    return memset(ptr, value, num);
}

void *bt_source_srv_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int32_t bt_source_srv_memcmp(const void *dest, const void *src, uint32_t count)
{
    return memcmp(dest, src, count);
}

char *bt_source_srv_strfind(char *str, const char *sub)
{
    return strstr(str, sub);
}

char *bt_source_srv_strcat(char *dest, const char *src)
{
    return strcat(dest, src);
}

char *bt_source_srv_strcpy(char *dest, const char *src)
{
    return strcpy(dest, src);
}

char *bt_source_srv_strncpy(char *dest, const char *src, uint32_t size)
{
    return strncpy(dest, src, size);
}

uint32_t bt_source_srv_strlen(char *string)
{
    return strlen(string);
}

int32_t bt_source_srv_strnmp(const char *dest, const char *src, uint32_t size)
{
    return strncmp(dest, src, size);
}




/* Copyright Statement:
 *
 */

#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "os.h" // FIXME: in libutil

#include "os_util.h"


static TickType_t gSysBootTick = 0;


void os_sleep(os_time_t sec, os_time_t usec)
{
    TickType_t xDelay;

    xDelay = sec * 1000 * portTICK_PERIOD_MS + usec * portTICK_PERIOD_MS / 1000;

    vTaskDelay(xDelay);
}


int os_get_time(struct os_time *t)
{
    TickType_t  cur;

    if (!gSysBootTick) {
        gSysBootTick = xTaskGetTickCount();
    }

    cur = xTaskGetTickCount();

    t->sec = (cur - gSysBootTick) / 1000 / portTICK_PERIOD_MS;
    t->usec = ((cur - gSysBootTick) % 1000) / portTICK_PERIOD_MS * 1000;

    return (cur - gSysBootTick);
}


unsigned long os_random(void)
{
    TickType_t  cur;

    cur = xTaskGetTickCount();

    cur = cur * 1103515245 + 12345 ;

    /* for return type "unsigned long" */
    return (unsigned long)(cur / 131072);

    //return (unsigned long)(cur/131072) % 65536 ;
}


int os_get_random(unsigned char *buf, size_t len)
{
    int            idx = 0;
    unsigned long  rd = 0;
    unsigned char *pc = (unsigned char *)&rd;

    while (len) {
        rd = os_random();
        os_memcpy(buf + idx, pc, (len > sizeof(unsigned long)) ? sizeof(unsigned long) : len);
        idx += (len > sizeof(unsigned long)) ? sizeof(unsigned long) : len;
        len = (len > sizeof(unsigned long)) ? len - sizeof(unsigned long) : 0;
    }

    return 0;
}


void *os_zalloc(size_t size)
{
    return pvPortCalloc(1, size);
}


void *os_malloc(size_t size)
{
    return pvPortMalloc(size);
}


void *os_realloc(void *ptr, size_t size)
{
    return pvPortRealloc(ptr, size);
}


void os_free(void *ptr)
{
    vPortFree(ptr);
}


/**
* os_strdup dulicates the incoming string and return the cloned string to
* caller.
*
* @param s incoming source string.
* @return NULL if memory allocation failed. The duplicated memory buffer
*         if succeeded.
* @note The caller is responsible to call free() to return the buffer.
*/
char *os_strdup(const char *s)
{
    int  l;
    char *r;

    if (s == NULL) {
        return NULL;
    }

    l = strlen(s);
    r = os_malloc(l + 1);

    if (r != NULL) {
        os_memcpy(r, s, l);
        r[l] = '\0';
    }

    return r;
}


int os_mktime(int year, int month, int day, int hour, int min, int sec,
              os_time_t *t)
{
    return -1;
}


int os_gmtime(os_time_t t, struct os_tm *tm)
{
    return -1;
}



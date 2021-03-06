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
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_db.h"

static uint8_t bt_sink_srv_timer_comparator(const uint8_t *record, const void *key);

static bt_sink_srv_timer_record_t g_bt_sink_srv_timer_records[BT_SINK_SRV_MAX_TIMER];
static bt_sink_srv_db_t g_bt_sink_srv_timer_db = {
    .name_p = BT_SINK_SRV_DB_TIMER,
    .dirty = false,
    .size = sizeof(bt_sink_srv_timer_record_t),
    .count = BT_SINK_SRV_MAX_TIMER,
    .used = 0,
    .comparator_function_p = bt_sink_srv_timer_comparator,
    .buffer_p = (uint8_t *)g_bt_sink_srv_timer_records
};

log_create_module(sink_srv, PRINT_LEVEL_INFO);


log_create_module(sink_music, PRINT_LEVEL_INFO);

void *bt_sink_srv_memory_alloc(uint16_t size)
{
#ifdef WIN32
    void *memory = (void *)malloc(size);
#else
    void *memory = (void *)pvPortMalloc(size);
#endif /* WIN32 */
    bt_sink_srv_memset(memory, 0, size);
    return memory;
}

void bt_sink_srv_memory_free(void *point)
{
    if (point) {
#ifdef WIN32
        free(point);
#else
        vPortFree(point);
#endif /* WIN32 */
    }
}


void *bt_sink_srv_memset(void *ptr, int32_t value, uint32_t num)
{
    return memset(ptr, value, num);
}

void *bt_sink_srv_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int32_t bt_sink_srv_memcmp(const void *dest, const void *src, uint32_t count)
{
    return memcmp(dest, src, count);
}

uint8_t bt_sink_srv_timer_comparator(const uint8_t *record, const void *key)
{
    bt_sink_srv_timer_record_t *timer_record = (bt_sink_srv_timer_record_t *)record;

    if (timer_record && timer_record->user_id != 0 && timer_record->user_id == (*((uint32_t *)key))) {
        return true;
    } else {
        return false;
    }
}

void bt_sink_srv_timer_init(void)
{
    bt_sink_srv_db_open(&g_bt_sink_srv_timer_db);
}

#ifdef WIN32
void CALLBACK bt_sink_srv_timer_proc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    bt_sink_srv_timer_record_t record;
    uint32_t user_id = (uint32_t)dwUser;

    if (BT_SINK_SRV_STATUS_SUCCESS == bt_sink_srv_db_find_record(&g_bt_sink_srv_timer_db, (uint32_t *)&user_id, (uint8_t *)&record)) {

        bt_sink_srv_db_delete_record(&g_bt_sink_srv_timer_db, &user_id);

        if (record.callback) {
            record.callback(record.parmaters);
        }
    }
}
#else
void bt_sink_srv_timer_callback(TimerHandle_t xTimer)
{
    bt_sink_srv_timer_record_t record;
    uint32_t user_id = (uint32_t)pvTimerGetTimerID(xTimer);

    bt_sink_srv_report("[Sink][Timer] bt_sink_srv_timer_callback, timer_id:%x user_id:%x", xTimer, user_id);

    if (BT_SINK_SRV_STATUS_SUCCESS == bt_sink_srv_db_find_record(&g_bt_sink_srv_timer_db, (uint32_t *)&user_id, (uint8_t *)&record)) {

        bt_sink_srv_db_delete_record(&g_bt_sink_srv_timer_db, &user_id);

        if (record.callback) {
            record.callback(record.parmaters);
        }
    }
}

#endif /* WIN32 */

void bt_sink_srv_timer_start(uint32_t user_id, uint32_t delay, bt_sink_srv_timer_callback_t function_p, void *parmaters)
{
    bt_sink_srv_timer_record_t timer_record;

    bt_sink_srv_timer_stop(user_id);

    timer_record.user_id = user_id;
    timer_record.callback = function_p;
    timer_record.parmaters = parmaters;

#ifdef WIN32
    // TIME_ONESHOT
    // TIME_PERIODIC
    if (0 == (timer_record.timer_id = timeSetEvent(delay, 10,
                                      (LPTIMECALLBACK)bt_sink_srv_timer_proc, (DWORD_PTR)user_id, TIME_ONESHOT))) {
        // TRACE
    }
#else
    timer_record.timer_id = (uint32_t)xTimerCreate("BT_SINK_SRV_TIMER",                /* Just a text name, not used by the kernel. */
                            (delay / portTICK_PERIOD_MS),  /* The timer period in ticks. */
                            pdFALSE,
                            (void *) user_id,
                            bt_sink_srv_timer_callback);

    xTimerStart((TimerHandle_t)timer_record.timer_id, 0);
    bt_sink_srv_report("[Sink][Timer] bt_sink_srv_timer_start, timer_id:%x, user_id:%x", timer_record.timer_id, user_id);
#endif /* WIN32 */
    bt_sink_srv_db_add_record(&g_bt_sink_srv_timer_db, (uint8_t *)&timer_record, &user_id);
}

void bt_sink_srv_timer_stop(uint32_t user_id)
{
    bt_sink_srv_timer_record_t record;

    bt_sink_srv_report("[Sink][Timer] bt_sink_srv_timer_stop, user_id:%x", user_id);

    if (BT_SINK_SRV_STATUS_SUCCESS == bt_sink_srv_db_find_record(&g_bt_sink_srv_timer_db, &user_id, (uint8_t *)&record)) {
#ifdef WIN32
        timeKillEvent(record.timer_id);
#else
        xTimerStop((TimerHandle_t)record.timer_id, 0);
        xTimerDelete((TimerHandle_t)record.timer_id, 0);
#endif /* WIN32 */
        bt_sink_srv_db_delete_record(&g_bt_sink_srv_timer_db, (void *)&user_id);
    }
}

bool bt_sink_srv_timer_is_exist(uint32_t user_id)
{
    bool result;
    bt_sink_srv_timer_record_t record;

    if (BT_SINK_SRV_STATUS_SUCCESS == bt_sink_srv_db_find_record(&g_bt_sink_srv_timer_db, &user_id, (uint8_t *)&record)) {
#ifndef WIN32
        if (xTimerIsTimerActive((TimerHandle_t) record.timer_id))
#endif /* WIN32 */
        {
            result = true;
        } else {
            result = false;
        }
    } else {
        result = false;
    }
    return result;
}

char *bt_sink_srv_strfind(char *str, const char *sub)
{
    return strstr(str, sub);
}

char *bt_sink_srv_strcat(char *dest, const char *src)
{
    return strcat(dest, src);
}

char *bt_sink_srv_strcpy(char *dest, const char *src)
{
    return strcpy(dest, src);
}

char *bt_sink_srv_strncpy(char *dest, const char *src, uint32_t size)
{
    return strncpy(dest, src, size);
}

uint32_t bt_sink_srv_strlen(char *string)
{
    return strlen(string);
}

int32_t bt_sink_srv_strnmp(const char *dest, const char *src, uint32_t size)
{
    return strncmp(dest, src, size);
}


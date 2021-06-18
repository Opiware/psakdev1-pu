/* Copyright Statement:
 *
 */

#ifndef __BT_SINK_SRV_UTILS_H__
#define __BT_SINK_SRV_UTILS_H__
#include <stdint.h>
#include <stdbool.h>
#ifndef WIN32
#include <syslog.h>
#else
#include "osapi.h"
#endif
#include "FreeRTOSConfig.h"
#include "bt_sink_srv_resource.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_SINK_SRV_DB_TIMER "BT_SINK_SRV_TIMER_DB"
#define BT_SINK_SRV_MAX_TIMER 5

typedef void (*bt_sink_srv_timer_callback_t)(void *parameter);

typedef struct {
    uint32_t timer_id;
    uint32_t user_id;
    bt_sink_srv_timer_callback_t callback;
    void *parmaters;
} bt_sink_srv_timer_record_t;

#define bt_sink_srv_assert configASSERT

#ifndef WIN32
#ifdef __BT_SINK_SRV_TRACE__
#define bt_sink_srv_report(_message,...) LOG_I(sink_srv, (_message), ##__VA_ARGS__)
#define bt_sink_srv_music_report(_message,...) LOG_I(sink_music, (_message), ##__VA_ARGS__)
#else
#define bt_sink_srv_report(_message,...);
#define bt_sink_srv_music_report(_message,...);
#endif
#else
#define bt_sink_srv_report(_message,...) OS_Report((_message), ##__VA_ARGS__)
#define bt_sink_srv_music_report(_message,...) OS_Report((_message), ##__VA_ARGS__)
#endif /* WIN32 */
void *bt_sink_srv_memory_alloc(uint16_t size);

void bt_sink_srv_memory_free(void *point);

void *bt_sink_srv_memset(void *ptr, int32_t value, uint32_t num);

void *bt_sink_srv_memcpy(void *dest, const void *src, uint32_t size);

int32_t bt_sink_srv_memcmp(const void *dest, const void *src, uint32_t count);

void bt_sink_srv_timer_init(void);

void bt_sink_srv_timer_start(uint32_t user_id, uint32_t delay, bt_sink_srv_timer_callback_t function_p, void *parmaters);

void bt_sink_srv_timer_stop(uint32_t user_id);

bool bt_sink_srv_timer_is_exist(uint32_t user_id);

char *bt_sink_srv_strfind(char *str, const char *sub);

char *bt_sink_srv_strcat(char *dest, const char *src);

char *bt_sink_srv_strcpy(char *dest, const char *src);

uint32_t bt_sink_srv_strlen(char *string);

char *bt_sink_srv_strncpy(char *dest, const char *src, uint32_t size);

int32_t bt_sink_srv_strnmp(const char *dest, const char *src, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __BT_SINK_SRV_UTILS_H__ */

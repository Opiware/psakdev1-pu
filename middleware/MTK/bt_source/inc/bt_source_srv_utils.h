/* Copyright Statement:
 *
 */

#ifndef __BT_SOURCE_SRV_UTILS_H__
#define __BT_SOURCE_SRV_UTILS_H__

#include <stdint.h>
#include <stdbool.h>
#ifndef WIN32
#include <syslog.h>
#else
#include "osapi.h"
#endif
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MTK_DEBUG_LEVEL_INFO)
#define __BT_SOURCE_SRV_DEBUG_INFO__
#define __BT_SOURCE_SRV_TRACE__
#endif

#define bt_source_srv_assert configASSERT


#ifndef WIN32
#ifdef __BT_SOURCE_SRV_TRACE__
#define bt_source_srv_report(_message,...) LOG_I(source_srv, (_message), ##__VA_ARGS__)
#else
#define bt_source_srv_report(_message,...);
#endif
#else
#define bt_source_srv_report(_message,...) OS_Report((_message), ##__VA_ARGS__)
#endif /* WIN32 */

void *bt_source_srv_memory_alloc(uint16_t size);

void bt_source_srv_memory_free(void *point);

void *bt_source_srv_memset(void *ptr, int32_t value, uint32_t num);

void *bt_source_srv_memcpy(void *dest, const void *src, uint32_t size);

int32_t bt_source_srv_memcmp(const void *dest, const void *src, uint32_t count);

char *bt_source_srv_strfind(char *str, const char *sub);

char *bt_source_srv_strcat(char *dest, const char *src);

char *bt_source_srv_strcpy(char *dest, const char *src);

uint32_t bt_source_srv_strlen(char *string);

char *bt_source_srv_strncpy(char *dest, const char *src, uint32_t size);

int32_t bt_source_srv_strnmp(const char *dest, const char *src, uint32_t size);

#ifdef WIN32
#define bt_source_srv_create_mutex()   { }
#define bt_source_srv_take_mutex() { }
#define bt_source_srv_give_mutex() { }
#else
void  bt_source_srv_create_mutex(void);
void  bt_source_srv_take_mutex(void);
void  bt_source_srv_give_mutex(void);
void  bt_source_srv_delete_mutex(void);
#endif



#ifdef __cplusplus
}
#endif

#endif /* __BT_SOURCE_SRV_UTILS_H__ */

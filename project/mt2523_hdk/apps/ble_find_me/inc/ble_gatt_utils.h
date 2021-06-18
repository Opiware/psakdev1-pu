/* Copyright Statement:
 *
 */

#ifndef __BLE_GATT_UTILS_H__
#define __BLE_GATT_UTILS_H__

#include "stdint.h"
#include "bt_type.h"
#include "syslog.h"
#include "FreeRTOSConfig.h"

#define __BLE_GATT_SERVICE_TRACE__

#ifdef __BLE_GATT_SERVICE_TRACE__
#define ble_gatt_report(_message,...) LOG_I(BLE_GATT_SERVICE, (_message), ##__VA_ARGS__)
#else
#define ble_gatt_report (void)0;
#endif

#define ble_gatt_assert configASSERT

void *ble_gatt_memory_alloc(uint32_t size);

void ble_gatt_memory_free(void *ptr);

void *ble_gatt_memset(void *ptr, int32_t value, uint32_t num);

void *ble_gatt_memcpy(void *dest, const void *src, uint32_t size);

int32_t ble_gatt_memcmp(const void *dest, const void *src, uint32_t count);

const char *ble_debug_bd_addr2str(const bt_bd_addr_t addr);

#endif /* __BLE_GATT_UTILS_H__ */


/* Copyright Statement:
 *
 */

#include "string.h"
#include "ble_gatt_utils.h"
#include "FreeRTOS.h"

log_create_module(BLE_GATT_SERVICE, PRINT_LEVEL_INFO);


#define BLE_DEBUG_BUFF_SIZE  128
static char ble_debug_buff[BLE_DEBUG_BUFF_SIZE];

void *ble_gatt_memory_alloc(uint32_t size)
{
    void *ptr = (void *)pvPortMalloc(size);

    ble_gatt_memset(ptr, 0x00, size);

    return ptr;
}


void ble_gatt_memory_free(void *ptr)
{
    if (ptr) {
        vPortFree(ptr);
    }
}


void *ble_gatt_memset(void *ptr, int32_t value, uint32_t num)
{
    return memset(ptr, value, num);
}


void *ble_gatt_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}


int32_t ble_gatt_memcmp(const void *dest, const void *src, uint32_t count)
{
    return memcmp(dest, src, count);
}


const char *ble_debug_bd_addr2str(const bt_bd_addr_t addr)
{
    snprintf(ble_debug_buff, BLE_DEBUG_BUFF_SIZE, "%02x-%02x-%02x-%02x-%02x-%02x",
            addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
    return ble_debug_buff;
}


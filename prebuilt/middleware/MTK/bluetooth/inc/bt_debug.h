/* Copyright Statement:
 *
 */

#ifndef __BT_DEBUG_H__
#define __BT_DEBUG_H__

/**
 * This header file describes the debug apis used by Bluetooth stack.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "bt_type.h"
#include "bt_os_layer_api.h"

BT_EXTERN_C_BEGIN

/**
 * Assert function.
 */
#define BT_ASSERT(...) assert(__VA_ARGS__)
#define BT_FW_ASSERT(...) assert(__VA_ARGS__)

/**
 * Log function. Example usage: BT_LOGD("HCI", "test%d", 123);
 */
void bt_debug_log(const char *format, ...);
#define BT_LOGI(module_name, format, ...)   \
    bt_debug_log("[I][" module_name "] " format, ## __VA_ARGS__)

#define BT_LOGD(module_name, format, ...)   \
    bt_debug_log("[D][" module_name "] " format, ## __VA_ARGS__)

#define BT_LOGW(module_name, format, ...)   \
    bt_debug_log("[W][" module_name "] " format, ## __VA_ARGS__)

#define BT_LOGE(module_name, format, ...)   \
    bt_debug_log("[E][" module_name "] " format, ## __VA_ARGS__)

/**
 * Data print function.
 */
#define BT_PRINT_16_BYTE_BIG_ENDIAN(p) {register int i; for(i=0;i<16;i++) fprintf(stderr, "%02x ", (p)[i]); fprintf(stderr, "\n");}
#define BT_PRINT_8_BYTE_BIG_ENDIAN(p) {register int i; for(i=0;i<8;i++) fprintf(stderr, "%02x ", (p)[i]); fprintf(stderr, "\n");}

/**
 * For address debug printing.
 */

/**
 * @brief     Convert address to string.
 * @param[in] addr is address using bt_bd_addr_t.
 * @return    An addrss string with format: 11-22-33-44-55-66.
 */
const char *bt_debug_bd_addr2str(const bt_bd_addr_t addr);

/**
 * @brief     Convert address to string.
 * @param[in] addr is address using bt_bd_addr_t.
 * @return    An addrss string with format: LAP: 11-22-33, UAP: 44, NAP: 55-66.
 */
const char *bt_debug_bd_addr2str2(const bt_bd_addr_t addr);

/**
 * @brief     Convert address to string.
 * @param[in] addr is address using bt_bd_addr_t.
 * @return    An addrss string with format: [PUBLIC]11-22-33-44-55-66.
 */
const char *bt_debug_addr2str(const bt_addr_t *p);

/**
 * @brief     Convert address to string.
 * @param[in] addr is address using bt_bd_addr_t.
 * @return    An addrss string with format: [PUBLIC]LAP: 11-22-33, UAP: 44, NAP: 55-66.
 */
const char *bt_debug_addr2str2(const bt_addr_t *p);

BT_EXTERN_C_END

#endif /* __BT_DEBUG_H__ */

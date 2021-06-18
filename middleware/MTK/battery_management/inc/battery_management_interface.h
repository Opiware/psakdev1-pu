/* Copyright Statement:
 *
 */

#ifndef __BATTERY_MANAGEMENT_INTERFACE_H__
#define __BATTERY_MANAGEMENT_INTERFACE_H__

#include "syslog.h"
#include "battery_management.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BMT_DEBUG_ENABLE
#define BMT_DBG(fmt,args...)    LOG_I(bmt ,fmt,##args)
#else
#define BMT_DBG(fmt, args...)
#endif

#define BMT_INFO(fmt, args...)  LOG_I(bmt ,fmt,##args)
#define BMT_WARN(fmt, args...)  LOG_W(bmt ,fmt,##args)
#define BMT_ERR(fmt, args...)   LOG_E(bmt ,fmt,##args)

typedef struct {
    battery_management_status_t (*battery_management_init)(void);
    int32_t (*battery_management_get_battery_property)(battery_property_t property);
    battery_management_status_t (*battery_management_register_callback)(battery_management_callback_t callback);
    battery_management_status_t (*battery_management_deinit)(void);
} bmt_function_t;

typedef struct {
    int32_t capacity;
    int32_t charging_current;
    int32_t charger_exist;
    int32_t charger_type;
    int32_t temperature;
    int32_t voltage;
    int32_t capacity_level;
} bmt_battery_t;

typedef struct {
    bool initialized;
    bool callback_init;
    battery_management_callback_t callback_func;
} bmt_context_t;

#ifdef __cplusplus
}
#endif

#endif /*__BATTERY_MANAGEMENT_INTERFACE_H__*/


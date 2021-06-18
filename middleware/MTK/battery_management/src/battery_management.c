/* Copyright Statement:
 *
 */

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "syslog.h"
#include "battery_management.h"
#include "battery_management_interface.h"

#include "task_def.h"

#ifdef BMT_DEBUG_ENABLE
log_create_module(bmt, PRINT_LEVEL_INFO);
#else
log_create_module(bmt, PRINT_LEVEL_WARNING);
#endif


extern bmt_function_t battery_func;

battery_management_status_t  battery_management_register_callback(battery_management_callback_t callback)
{

    return battery_func.battery_management_register_callback(callback);
}

battery_management_status_t battery_management_init(void)
{

    BMT_DBG("battery_management_init");
    return battery_func.battery_management_init();
}

battery_management_status_t battery_management_deinit(void)
{
    BMT_DBG("battery_management_deinit");

    return battery_func.battery_management_deinit();
}

int32_t battery_management_get_battery_property(battery_property_t property)
{

    return battery_func.battery_management_get_battery_property(property);
}



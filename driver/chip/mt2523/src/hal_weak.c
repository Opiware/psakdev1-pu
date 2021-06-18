/* Copyright Statement:
 *
 */

#include "hal.h"
#include "memory_attribute.h"

/* This file for HAL core lib release, void build error when disable some module*/
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
extern void mpu_status_save(void);
extern void mpu_status_restore(void);

ATTR_TEXT_IN_TCM void  default_cache_status_save(void)
{
}
#pragma weak cache_status_save = default_cache_status_save

ATTR_TEXT_IN_TCM void  default_cache_status_restore(void)
{
}
#pragma weak cache_status_restore = default_cache_status_restore


ATTR_TEXT_IN_TCM void  default_uart_backup_all_registers(void)
{
}
#pragma weak uart_backup_all_registers = default_uart_backup_all_registers

ATTR_TEXT_IN_TCM void  default_uart_restore_all_registers(void)
{
}
#pragma weak uart_restore_all_registers = default_uart_restore_all_registers


ATTR_TEXT_IN_TCM void  default_mpu_status_save(void)
{
}
#pragma weak mpu_status_save = default_mpu_status_save

ATTR_TEXT_IN_TCM void  default_mpu_status_restore(void)
{
}
#pragma weak mpu_status_restore = default_mpu_status_restore



ATTR_TEXT_IN_TCM void  default_nvic_sleep_backup_register(void)
{
}
#pragma weak nvic_sleep_backup_register = default_nvic_sleep_backup_register

ATTR_TEXT_IN_TCM void  default_nvic_sleep_restore_register(void)
{
}
#pragma weak nvic_sleep_restore_register = default_nvic_sleep_restore_register

ATTR_TEXT_IN_TCM void default_hal_module_sleep_register_callback(void)
{
}
#pragma weak hal_module_sleep_register_callback = default_hal_module_sleep_register_callback

#ifndef HAL_RTC_MODULE_ENABLED
ATTR_TEXT_IN_TCM void default_hal_rtc_deinit(void)
{
}
#pragma weak hal_rtc_deinit = default_hal_rtc_deinit
#endif

#else
#error "Unsupported Platform"
#endif


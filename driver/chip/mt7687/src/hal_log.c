/* Copyright Statement:
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "hal_platform.h"
#include "hal_log.h"
#include "hal.h"


#if defined(MTK_HAL_NO_LOG_ENABLE) || defined(MTK_DEBUG_LEVEL_NONE)
void log_hal_fatal_internal(const char *func, int line, const char *message, ...)
{
}
void log_hal_error_internal(const char *func, int line, const char *message, ...)
{
}
void log_hal_warning_internal(const char *func, int line, const char *message, ...)
{
}
void log_hal_info_internal(const char *func, int line, const char *message, ...)
{
}

void log_hal_dump_internal(const char *func, int line, const char *message, const void *data, int length, ...)
{

}

#elif defined(MTK_HAL_PLAIN_LOG_ENABLE)
void log_hal_fatal_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
#ifdef HAL_NVIC_MODULE_ENABLED
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
#endif
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);
#ifdef HAL_NVIC_MODULE_ENABLED
    hal_nvic_restore_interrupt_mask(mask);
#endif
}
void log_hal_error_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
#ifdef HAL_NVIC_MODULE_ENABLED
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
#endif
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);
#ifdef HAL_NVIC_MODULE_ENABLED
    hal_nvic_restore_interrupt_mask(mask);
#endif
}
void log_hal_warning_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
#ifdef HAL_NVIC_MODULE_ENABLED
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
#endif
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);
#ifdef HAL_NVIC_MODULE_ENABLED
    hal_nvic_restore_interrupt_mask(mask);
#endif
}
void log_hal_info_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
#ifdef HAL_NVIC_MODULE_ENABLED
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
#endif
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);
#ifdef HAL_NVIC_MODULE_ENABLED
    hal_nvic_restore_interrupt_mask(mask);
#endif
}

void log_hal_dump_internal(const char *func, int line, const char *message, const void *data, int length, ...)
{
}

#else  /* !defined(MTK_HAL_PLAIN_LOG_ENABLE) */

log_hal_create(PRINT_LEVEL_INFO);

void log_hal_fatal_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprint_module_log(&log_control_block_hal, func, line, PRINT_LEVEL_ERROR, message, ap);
    va_end(ap);
}


void log_hal_error_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprint_module_log(&log_control_block_hal, func, line, PRINT_LEVEL_ERROR, message, ap);
    va_end(ap);
}

void log_hal_warning_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprint_module_log(&log_control_block_hal, func, line, PRINT_LEVEL_WARNING, message, ap);
    va_end(ap);
}

void log_hal_info_internal(const char *func, int line, const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprint_module_log(&log_control_block_hal, func, line, PRINT_LEVEL_INFO, message, ap);
    va_end(ap);
}

void log_hal_dump_internal(const char *func, int line, const char *message, const void *data, int length, ...)
{
    va_list ap;
    va_start(ap, length);
    vdump_module_buffer(&log_control_block_hal, func, line, PRINT_LEVEL_INFO, data, length, message, ap);
    va_end(ap);
}

#endif /* !defined(MTK_HAL_NO_LOG_ENABLE) */


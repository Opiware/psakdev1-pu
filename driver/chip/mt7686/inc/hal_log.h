/* Copyright Statement:
 *
 */

#ifndef __HAL_LOG_H__
#define __HAL_LOG_H__

/**
 * @filel_log.h.
 *
 * The debug printing macros that were used by HAL module is defined in this
 * header file.
 *
 * Feature option: MTK_HAL_PLAIN_LOG_ENABLE
 *
 * This feature option turns the LOG system integration off in HAL module.
 * It was added to allow bootloader, which has no operating system in it, to
 * be able to use HAL layer code. */

#include "hal_feature_config.h"

#if !defined(MTK_HAL_PLAIN_LOG_ENABLE) && !defined(MTK_HAL_NO_LOG_ENABLE)
#include "syslog.h"
#else
#include "stdio.h"
#endif /* !defined(MTK_HAL_PLAIN_LOG_ENABLE) */

#ifdef __cplusplus
extern "C" {
#endif

extern void log_hal_error_internal(const char *func, int line, const char *message, ...);
extern void log_hal_warning_internal(const char *func, int line, const char *message, ...);
extern void log_hal_info_internal(const char *func, int line, const char *message, ...);
extern void log_hal_dump_internal(const char *func, int line, const char *message, const void *data, int length, ...);



#define log_hal_error(_message,...)                log_hal_error_internal(__FUNCTION__, __LINE__, (_message),##__VA_ARGS__)
#define log_hal_warning(_message,...)              log_hal_warning_internal(__FUNCTION__, __LINE__, (_message),##__VA_ARGS__)
#define log_hal_info(_message,...)                 log_hal_info_internal(__FUNCTION__, __LINE__, (_message),##__VA_ARGS__)
#define log_hal_dump(_message, _data, _len, ...)   log_hal_dump_internal(__FUNCTION__, __LINE__, (_message), (_data), (_len),##__VA_ARGS__)



#if !defined(MTK_HAL_PLAIN_LOG_ENABLE) && !defined(MTK_HAL_NO_LOG_ENABLE)
#define log_hal_create(_level)                     log_create_module(hal, (_level))

/*
#define log_hal_config_print_switch(_switch)        log_config_print_switch(hal, (_switch))
#define log_hal_config_print_level(_level)          log_config_print_level(hal, (_level))
#define log_hal_config_print_func(_print_func)      log_config_print_func(hal, (_print_func))
#define log_hal_config_dump_func(_dump_func)        log_config_dump_func(hal, (_dump_func))
*/

#endif /* defined(MTK_HAL_PLAIN_LOG_ENABLE) */

#ifdef __cplusplus
}
#endif

#endif /* __HAL_LOG_H__ */


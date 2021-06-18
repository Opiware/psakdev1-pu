/* Copyright Statement:
 *
 */

#ifndef __HAL_SYS_H__
#define __HAL_SYS_H__

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file hal_sys.h
 *
 * @brief see hal_WDT.c in DVT tree. */
#define WHOLE_SYSTEM_REBOOT_COMMAND 0

#define HAL_SYS_REBOOT_MAGIC (538314278)


typedef enum {
    HAL_SYS_OK,
    HAL_SYS_INVALID_COMMAND,
    HAL_SYS_INVALID_MAGIC
} hal_sys_status_t;


typedef void (*hal_sys_reboot_callback_t)(uint32_t command);


/**
 * When a reboot (hal_sys_reboot) is requested, the callback is called.
 *
 * A reboot callback callback can be used to provide dying gasp function.
 *
 * @return Original callback; */
hal_sys_reboot_callback_t hal_sys_reboot_register_callback(
    hal_sys_reboot_callback_t    callback);


/**
 * Reboots the system.
 *
 * @param magic must be HAL_SYS_REBOOT_MAGIC to trigger reboot, this avoids
 *        any accidential calls to hal_sys_reboot().
 *
 * @param command 0 to reboot the whole system. Other comamnds may be used to
 *        reboot a part of the system on other chipsets. If the command is 0,
 *        this API will not return.
 *
 * @retval HAL_SYS_OK if the command executes okay. */
hal_sys_status_t hal_sys_reboot(uint32_t magic, uint32_t command);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_SYS_H__ */


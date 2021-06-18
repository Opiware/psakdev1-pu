/* Copyright Statement:
 *
 */

/**
 * @author  MTK
 * @version 1.0
 * @date    2015.10.29
 * */

#ifndef __HAL_SLEEP_DRIVER_H__
#define __HAL_SLEEP_DRIVER_H__

#include "hal_platform.h"
#ifdef HAL_SLEEP_MANAGER_ENABLED

//PSI master
/*Global SleepDrv data structure*/
typedef struct {
    bool                handleInit; // the handleCount is initalized or not
    uint8_t             handleCount;
    uint32_t            sleepDisable;
    hal_sleep_mode_t    sleepMode;
} sleep_driver_struct;

typedef void (*sleepdrv_cb)(void *data);

typedef struct sleepdrv_cb_t {
    sleepdrv_cb func;
    void        *para;
    uint32_t    mode;
} sleepdrv_cb_t;

#define MAX_SLEEP_HANDLE                32
#define INVALID_SLEEP_HANDLE            0xFF

void sleep_driver_init(void);
uint8_t sleepdrv_get_handle(const char *handle_name, uint8_t size);
void sleepdrv_release_handle(uint8_t handle);
bool sleepdrv_is_handle_valid(uint8_t handle_index);
bool sleepdrv_get_handle_status(uint8_t handle);
bool sleepdrv_check_sleep_locks(void);
uint32_t sleepdrv_get_lock_index(void);
uint32_t sleepdrv_get_lock_module(void);
bool sleepdrv_hold_sleep_lock(uint8_t handle_index);
bool sleepdrv_release_sleep_lock(uint8_t handle_index);
bool sleepdrv_register_suspend_cb(sleepdrv_cb func, void *data, uint32_t mode);
void sleepdrv_run_suspend_cbs(uint32_t mode);
bool sleepdrv_register_resume_cb(sleepdrv_cb func, void *data, uint32_t mode);
void sleepdrv_run_resume_cbs(uint32_t mode);
void sleepdrv_register_callback(void);
void sleepdrv_set_sleep_mode(hal_sleep_mode_t mode);
hal_sleep_mode_t sleepdrv_get_sleep_mode(void);

#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif /* __HAL_SLEEP_DRIVER_H__ */

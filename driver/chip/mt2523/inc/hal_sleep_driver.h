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

#include "hal_sys_topsm.h"
#include "hal_sleep_manager_platform.h"


//PSI Register

//#define PSI_MST_BASE                       (0xA20C0000)  /*PSI_MST_BASE register base*/
#define PSI_MST_CON0                  ((volatile uint32_t*)(PSI_MST_BASE+0x00))  /*free switch HP or LP ; 0: follow previous(before sleep) state */
#define PSI_MST_CON1                  ((volatile uint32_t*)(PSI_MST_BASE+0x04)) /*[24:16]:s0_lp_settle  ,[8:0]:s0_hp_settle*/
#define PSI_MST_CON2                  ((volatile uint32_t*)(PSI_MST_BASE+0x08)) /*[24:16]:s1_lp_settle  ,[8:0]:s1_hp_settle*/
#define PSI_MST_CON3                  ((volatile uint32_t*)(PSI_MST_BASE+0x0C)) /*[24:16]:s0_lp_settle  ,[24:16]:to_s1_settle*/
#define PSI_MST_CON4                  ((volatile uint32_t*)(PSI_MST_BASE+0x10))
#define PSI_MST_S0                    ((volatile uint32_t*)(PSI_MST_BASE+0x20))  /*SW*/
#define PSI_MST_S1                    ((volatile uint32_t*)(PSI_MST_BASE+0x24))  /*CM4*/
#define PSI_MST_S2                    ((volatile uint32_t*)(PSI_MST_BASE+0x28))  /*BT4*/
#define PSI_MST_S3                    ((volatile uint32_t*)(PSI_MST_BASE+0x2C))  /*N/A*/
#define PSI_MST_S4                    ((volatile uint32_t*)(PSI_MST_BASE+0x30))  /*DSP*/
#define PSI_MST_STATE                 ((volatile uint32_t*)(PSI_MST_BASE+0x34))  /*PSI BUS STATE*/

#define PSI_S0_LP_SETTLE_TIME 0x80
#define PSI_S0_HP_SETTLE_TIME 0x80
#define PSI_S1_LP_SETTLE_TIME 0x80
#define PSI_S1_HP_SETTLE_TIME 0x80
#define PSI_HP_LP_SETTLE_TIME 0x80
#define PSI_LP_HP_SETTLE_TIME 0x80
#define PSI_T0_S0_SETTLE_TIME 0x80
#define PSI_T0_S1_SETTLE_TIME 0x80
//PSI master
/*Global SleepDrv data structure*/
typedef struct {
    bool       handleInit; // the handleCount is initalized or not
    uint8_t    handleCount;
    uint32_t   sleep_lock_index;
    uint32_t   sleep_set_handle_index;
    //uint32_t   sleepDisable_ext;
} sleep_driver_struct;

#define MAX_SLEEP_HANDLE                32
#define INVALID_SLEEP_HANDLE            0xFF

void sleep_driver_init(void);
uint8_t sleepdrv_get_handle(const char *handle_name, uint8_t size);
void sleepdrv_release_handle(uint8_t handle);
bool sleepdrv_get_handle_status(uint8_t handle);
bool sleepdrv_check_sleep_locks(void);
uint32_t sleepdrv_get_lock_index(void);
uint32_t sleepdrv_get_lock_module(void);
void sleep_driver_mtcmos_control(hal_sys_topsm_mtcmos_enum_t mtcmos, bool config);
void PSI_HP_RUN_AT_LP(const uint32_t master_id);
void PSI_LP_RUN_AT_HP(const uint32_t master_id);
void sleepdrv_hold_sleep_lock(uint8_t handle_index);
void sleepdrv_release_sleep_lock(uint8_t handle_index);
void PSI_S0_RUN_AT_HP(const uint32_t master_id);

void PSI_S1_RUN_AT_LP(const uint32_t master_id);
void PSI_S1_RUN_AT_HP(const uint32_t master_id);
void PSI_S0_Run_AT_LP(const uint32_t master_id);
void PSI_SLEEP_AT_S0(const uint32_t master_id);
void PSI_SLEEP_AT_S1(const uint32_t master_id);
void sleep_driver_fast_wakeup_eint_setting(hal_gpio_pin_t gpio_index, hal_eint_number_t eint_index);
void PSI_debug_info(void);
//debug API
void sleep_driver_debug_dump_lock_sleep_time(void);
void sleep_driver_debug_lock_sleep_timelog(bool lock, uint8_t handle_index);
#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif /* __HAL_SLEEP_DRIVER_H__ */

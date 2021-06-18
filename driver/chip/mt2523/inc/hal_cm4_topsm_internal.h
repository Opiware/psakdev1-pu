/* Copyright Statement:
 *
 */

#ifndef HAL_CM4_TOPSM_INTERNAL_H_
#define HAL_CM4_TOPSM_INTERNAL_H_

#include "hal_platform.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED

#include <stdint.h>

uint32_t nvic_sleep_backup_register(void);
uint32_t nvic_sleep_restore_register(void);

void deepsleep_backup_CM4_sys_ctrl_reg(void);
void deepsleep_restore_CM4_sys_ctrl_reg(void);

void cmsys_cfg_status_save(void);
void cmsys_cfg_status_restore(void);
void fpu_status_save(void);
void fpu_status_restore(void);

#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif /* HAL_CM4_TOPSM_INTERNAL_H_ */

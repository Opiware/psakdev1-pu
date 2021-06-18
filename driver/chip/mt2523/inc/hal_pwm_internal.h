/* Copyright Statement:
 *
 */

#ifndef __HAL_PWM_INTERNAL_H__
#define __HAL_PWM_INTERNAL_H__


#include "hal_platform.h"
#include "hal_nvic_internal.h"

#ifdef HAL_PWM_MODULE_ENABLED

#define PWM_NUMBER       6

#define PWM_CLOCK_SEL1  32768

#define PWM_CLOCK_SEL2  13000000

#define PWM_MAX_COUNT   0x1fff

#define PWM_INIT  1

#define PWM_DEINIT  0

#define PWM_CHECK_AND_SET_BUSY(pwm_port,busy_status)  \
do{ \
    uint32_t saved_mask; \
    saved_mask = save_and_set_interrupt_mask(); \
    if(pwm_init_status[pwm_port] == PWM_INIT){ \
        busy_status = HAL_PWM_STATUS_ERROR; \
    } else { \
        pwm_init_status[pwm_port] = PWM_INIT;  \
        busy_status = HAL_PWM_STATUS_OK; \
    } \
     restore_interrupt_mask(saved_mask); \
}while(0)

#define PWM_SET_IDLE(pwm_port)   \
do{  \
       pwm_init_status[pwm_port] = PWM_DEINIT;  \
}while(0)

#endif /*HAL_PWM_MODULE_ENABLED*/
#endif


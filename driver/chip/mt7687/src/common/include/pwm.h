/* Copyright Statement:
 *
 */

/**
 * @file pwm.h
 *
 *  Pulse Width Modulation.
 * */


#ifndef __PWM_H__
#define __PWM_H__



#include "hal_platform.h"
#ifdef HAL_PWM_MODULE_ENABLED
#include "pinmux.h"


#ifdef __cplusplus
extern "C" {
#endif

#define PWM_CLK_SRC_32K     (0)
#define PWM_CLK_SRC_2M      (1)
#define PWM_CLK_SRC_XTAL    (2)
#define PWM_CLK_SRC_NUM     (3)


/**
 * @brief  Configure clock source of all PWM module.
 *
 * @param  clock_source [IN] 0:32KHz, 1:2MHz, 2:XTAL(depending on XTAL, ex. 40MHz) are supported.
 *
 * @return >=0 means success, <0 means fail.
 *
 * @note Clock source should be selected based on PWM frequency. */
int32_t pwm_init(uint8_t clock_source);


/**
 * @brief  Configure specific PWM with indicated frequency and duty cycle.
 *
 * @param  index [IN] Indicate specific PWM module.
 * @param  frequency [IN] In unit of Hz.
 * @param  duty_cycle [IN] In 256 steps.
 * @param  enable [IN]
 *          1: PWM is enabled and will be active after pwm_set done.
 *          0: PWM is disabled, frequency and duty cycle setting are cleared as 0.
 *
 * @return >=0 means success, <0 means fail.
 * */
int32_t pwm_set(uint8_t index, uint32_t frequency, uint16_t duty_cycle, uint8_t enable);


/**
 * @brief  Get frequency, duty cycle and on/off status of specific PWM.
 *
 * @param  index [IN] Indicate specific PWM module.
 * @param  frequency [IN] In unit of Hz.
 * @param  duty_cycle [IN] In 256 steps.
 * @param  enable [IN]
 *          1: PWM is enabled.
 *          0: PWM is disabled.
 *
 * @return >=0 means success, <0 means fail.
 * */
int32_t pwm_get(uint8_t index, uint32_t *frequency, uint16_t *duty_cycle, uint8_t *status);


/** @brief Get PWM module index from GPIO number.
 *
 *  @param  index [IN] Indicate specific GOIP number.
 *  @param  frequency [IN] In unit of Hz.
 *
 *  @return >=0 means success and PWM module index, <0 means fail.
 * */



#ifdef __cplusplus
}
#endif

#endif
#endif /* __PWM_H__ */


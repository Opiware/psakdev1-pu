/* Copyright Statement:
 *
 */

/**
 * @file timer.h
 *
 *  Timer Control Function
 * */

#ifndef __TIMER_H__
#define __TIMER_H__

#include "hal_gpt.h"

#ifdef HAL_GPT_MODULE_ENABLED
#include "stdint.h"
#include "stdbool.h"


#ifdef __cplusplus
extern "C" {
#endif

#define TMR_IDX0            0
#define TMR_IDX1            1
#define GPT_IDX2            2
#define GPT_IDX4            4

#define OneShot_mode    0
#define AutoRepeat_mode 1



typedef struct {
    void (*TMR0_func)(void);
    void (*TMR1_func)(void);
} TMR_func;


typedef struct {
    TMR_func       TMR_FUNC;
} TMRStruct;


/**
 * @brief Get currenct system time
 *
 * @param None
 *
 * @return current GPT2 time in unit of 32k clock */
uint32_t get_current_count(void);
/**
 * Get currenct system time
 *
 * @param None
 *
 * @return current GPT4 time in unit of bus clock */
uint32_t get_current_gpt4_count(void);

/**
 * @brief System delay time 1ms function
 *
 * @param ms [IN] Delay time 1ms, unit is 32k clock unit.
 *
 * @return None */
void delay_ms(uint32_t ms);

/**
 * @brief System delay time 1us function
 *
 * @param ms [IN] Delay time 1us, clock source is bus clock.
 *
 * @return None */
void delay_us(uint32_t us);

/**
 * @brief TMR0/1 init function
 *
 * @param timerNum [IN]  TMR0 or TMR1
 * @param countValue [IN] Initial count value
 * @param autoRepeat  [IN] OneShot_mode or AutoRepeat_mode
 * @param TMR_Callback [IN] type void (*TMR_Callback)(void)
 *
 * @return None */
void drvTMR_init(uint32_t timerNum, uint32_t countValue, bool  autoRepeat, void (*TMR_Callback)(void));
/**
 * @brief Timer0/1 and GPT2/4start function
 *
 * @param timerNum [IN] TMR0 or TMR1
 *
 * @return None */
void TMR_Start(uint32_t timerNum);
/**
 * @brief Timer0/1 and GPT2/4 stop function
 *
 * @param timerNum [IN] TMR0 or TMR1
 *
 * @return None */
void TMR_Stop(uint32_t timerNum);
/**
 * @brief GPT2 init function
 *
 * @return None */
void drvGPT2Init(void);
/**
* @brief GPT4 init function
*
* @return None
*/
void drvGPT4Init(void);
/**
 * @brief Clean TMR0/1 Interrupt status bit
 *
 * @param timerNum [IN] TMR0 or TMR1
 *
 * @return None */
void clear_TMR_INT_status_bit(uint32_t timerNum);


#ifdef __cplusplus
}
#endif

#endif

#endif

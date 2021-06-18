/* Copyright Statement:
 *
 */

#include "hal_gpt.h"

#ifdef HAL_GPT_MODULE_ENABLED

#include "type_def.h"
#include "gpt.h"
#include "timer.h"

#define SPEED_1K        0
#define SPEED_32K       1

#define time_after(a,b)  ((long)(b) - (long)(a) < 0)
#define time_before(a,b) time_after(b,a)

/**
 * Get currenct system time
 *
 * @param None
 *
 * @return current GPT2 time in unit of 32k clock */
uint32_t get_current_count(void)
{
    return GPT_return_current_count(GPT2);
}


void delay_time(kal_uint32 count)
{
    kal_uint32 end_count, current;

    end_count = get_current_count() + count + 1;
    current = get_current_count();
    while (time_before(current, end_count)) {
        current = get_current_count();
    }

}


void delay_time_for_gpt4(kal_uint32 count)
{
    kal_uint32 end_count, current;

    end_count = get_current_gpt4_count() + count + 1;
    current = get_current_gpt4_count();
    while (time_before(current, end_count)) {
        current = get_current_gpt4_count();
    }

}


/**
 * Get currenct system time
 *
 * @param None
 *
 * @return current GPT4 time in unit of bus clock */
uint32_t get_current_gpt4_count(void)
{
    return (GPT_return_current_count(GPT4));
}
/**
 * System delay time function
 *
 * @param count     delay time unit is 32k clock unit
 *
 * @return None */

void delay_ms(uint32_t ms)
{
    uint32_t count;

    count  = 32 * ms;
    count += (7 * ms) / 10;
    count += (6 * ms) / 100;
    count += (8 * ms) / 1000;
    delay_time(count);
}



void delay_us(uint32_t us)
{
    uint32_t count;
    uint32_t ticks_per_us;

    ticks_per_us = top_mcu_freq_get() / 1000000;
    count = ticks_per_us * us;

    delay_time_for_gpt4(count);
}



void drvTMR_init(uint32_t timerNum, uint32_t countValue, bool  autoRepeat, void (*TMR_Callback)(void))
{

    GPT_Stop(timerNum);

    if (timerNum == TMR0) {
        DRV_Reg32(GPT0_CTRL) = 0;
        GPT_init(timerNum, SPEED_32K, TMR_Callback);
    } else {
        DRV_Reg32(GPT1_CTRL) = 0;
        GPT_init(timerNum, SPEED_32K, TMR_Callback);
    }

    GPT_ResetTimer(timerNum, countValue, autoRepeat);
}

void TMR_Start(uint32_t timerNum)
{
    GPT_Start(timerNum);
}

void TMR_Stop(uint32_t timerNum)
{
    GPT_Stop(timerNum);
}


void drvGPT2Init(void)
{
    CM4_GPT2Init();
}

void drvGPT4Init(void)
{
    CM4_GPT4Init();
}

void clear_TMR_INT_status_bit(uint32_t timerNum)
{
    if (timerNum == TMR0) {
        DRV_Reg32(GPT_ISR) = GPT0_INT;
    }
    if (timerNum == TMR1) {
        DRV_Reg32(GPT_ISR) = GPT1_INT;
    }
}

#endif



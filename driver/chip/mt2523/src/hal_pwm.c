/* Copyright Statement:
 *
 */

#include "hal_pwm.h"

#ifdef HAL_PWM_MODULE_ENABLED

#include "hal_pwm_internal.h"
#include "hal_clock.h"

/*peripheral dma base address array */
PWM_REGISTER_T  *pwm[PWM_NUMBER] = {PWM0, PWM1, PWM2, PWM3, PWM4, PWM5};

static bool pwm_run_status[PWM_NUMBER] = {false, false, false, false, false, false};

const hal_clock_cg_id pwm_pdn[PWM_NUMBER] = {HAL_CLOCK_CG_PWM0, HAL_CLOCK_CG_PWM1, HAL_CLOCK_CG_PWM2, HAL_CLOCK_CG_PWM3, HAL_CLOCK_CG_PWM4, HAL_CLOCK_CG_PWM5};

volatile static uint8_t pwm_init_status[PWM_NUMBER] = {0};
#ifdef HAL_SLEEP_MANAGER_ENABLED

static uint32_t pwm_control_reg[PWM_NUMBER] = {0};
static uint32_t pwm_count_reg[PWM_NUMBER] = {0};
static uint32_t pwm_threshold_reg[PWM_NUMBER] = {0};
static bool pwm_backup_status[PWM_NUMBER] = {false, false, false, false, false, false};


void pwm_backup_register_call_back(void)
{
    uint32_t channel_num = 0;
    for (channel_num = HAL_PWM_2; channel_num <= HAL_PWM_5; channel_num++) {
        if (pwm_init_status[channel_num] == PWM_INIT) {
            pwm_control_reg[channel_num] = pwm[channel_num]->PWM_CTRL;
            pwm_count_reg[channel_num] = pwm[channel_num]->PWM_COUNT;
            pwm_threshold_reg[channel_num] = pwm[channel_num]->PWM_THRESH;
            pwm_backup_status[channel_num] = true;

        }
    }

}

void pwm_restore_register_call_back(void)
{
    uint32_t channel_num = 0;
    for (channel_num = HAL_PWM_2; channel_num <= HAL_PWM_5; channel_num++) {
        if (pwm_backup_status[channel_num] == true) {
            pwm[channel_num]->PWM_CTRL = pwm_control_reg[channel_num];
            pwm[channel_num]->PWM_COUNT = pwm_count_reg[channel_num];
            pwm[channel_num]->PWM_THRESH = pwm_threshold_reg[channel_num];
            pwm_backup_status[channel_num] = false;

        }
    }

}

#endif
hal_pwm_status_t hal_pwm_init(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t source_clock)


{
    hal_pwm_status_t busy_status;
    /*check parameters*/

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    if (source_clock > HAL_PWM_CLOCK_32KHZ) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    PWM_CHECK_AND_SET_BUSY(pwm_channel, busy_status);
    if (HAL_PWM_STATUS_ERROR == busy_status) {
        return HAL_PWM_STATUS_ERROR;
    }

    /* initialize driver default setting */
    pwm[pwm_channel]->PWM_CTRL = 0;
    pwm[pwm_channel]->PWM_COUNT = 0;
    pwm[pwm_channel]->PWM_THRESH = 0;

    /*set clock setting */
    pwm[pwm_channel]->PWM_CTRL &= ~PWM_CLK_SEL_MASK;
    pwm[pwm_channel]->PWM_CTRL |= source_clock << PWM_CLK_SEL_OFFSET;

    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_deinit(hal_pwm_channel_t pwm_channel)

{

    /*check parameters*/

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    PWM_SET_IDLE(pwm_channel);

    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_set_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count)
{

    uint32_t clock = 0;
    uint16_t clock_div = 0;
    volatile uint16_t  control = 0;
    uint16_t tmp = 0;
    uint32_t smallest_frequency = 0;

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    /*read current control value*/
    control = pwm[pwm_channel]->PWM_CTRL;
    clock_div = (1 << (control & PWM_CLK_DIV_MASK));
    if (control & PWM_CLK_SEL_MASK) {
        clock = PWM_CLOCK_SEL1;
    } else {
        clock = PWM_CLOCK_SEL2;
    }
    clock = clock / clock_div;
    smallest_frequency = clock / 0X1FFF;
    if (0 == frequency) {
        tmp = clock;
    } else if (frequency < smallest_frequency) {
        return HAL_PWM_STATUS_INVALID_FREQUENCY;
    } else {
        tmp = clock / frequency;
    }


    tmp--;
    if (tmp > PWM_MAX_COUNT) {
        tmp = PWM_MAX_COUNT;
    }
    pwm[pwm_channel]->PWM_COUNT = tmp;

    *total_count = tmp ;
    return HAL_PWM_STATUS_OK;

}

hal_pwm_status_t hal_pwm_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle)
{

    volatile uint16_t tmp = 0;
    uint16_t threshold = 0;

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    tmp = pwm[pwm_channel]->PWM_COUNT;

    if (duty_cycle > tmp)

    {
        threshold =  tmp;
    } else {
        threshold = duty_cycle;
    }

    pwm[pwm_channel]->PWM_THRESH = threshold;

    return HAL_PWM_STATUS_OK;

}


hal_pwm_status_t hal_pwm_start(hal_pwm_channel_t pwm_channel)
{
    uint32_t saved_mask;

    hal_clock_status_t clock_status;
    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    saved_mask = save_and_set_interrupt_mask();

    if (pwm_run_status[pwm_channel] == false) {
        pwm_run_status[pwm_channel] = true;
        clock_status = hal_clock_enable(pwm_pdn[pwm_channel]);
        if (HAL_CLOCK_STATUS_ERROR == clock_status) {
            return HAL_PWM_STATUS_ERROR;
        }
    } else {
        restore_interrupt_mask(saved_mask);
        return  HAL_PWM_STATUS_ERROR;

    }
    restore_interrupt_mask(saved_mask);


    return  HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_stop(hal_pwm_channel_t pwm_channel)
{

    uint32_t saved_mask;
    hal_clock_status_t clock_status;

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    saved_mask = save_and_set_interrupt_mask();

    if (pwm_run_status[pwm_channel] == true) {
        pwm_run_status[pwm_channel] = false;

        /*disable pwm clock */
        clock_status = hal_clock_disable(pwm_pdn[pwm_channel]);
        if (HAL_CLOCK_STATUS_ERROR == clock_status) {
            return HAL_PWM_STATUS_ERROR;
        }
    } else {
        restore_interrupt_mask(saved_mask);
        return  HAL_PWM_STATUS_ERROR;

    }
    restore_interrupt_mask(saved_mask);

    return  HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency)
{
    uint32_t clock = 0;
    uint16_t clock_div = 0;
    volatile uint16_t  control = 0;
    volatile uint16_t tmp = 0;

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    /*read current control value*/
    control = pwm[pwm_channel]->PWM_CTRL;
    clock_div = (1 << (control & PWM_CLK_DIV_MASK));
    if (control & PWM_CLK_SEL_MASK) {
        clock = PWM_CLOCK_SEL1;
    } else {
        clock = PWM_CLOCK_SEL2;
    }

    tmp = pwm[pwm_channel]->PWM_COUNT;
    tmp = (tmp + 1) * clock_div;

    *frequency = clock / tmp;

    return HAL_PWM_STATUS_OK;


}

hal_pwm_status_t hal_pwm_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle)
{

    volatile uint16_t tmp = 0;

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    tmp = pwm[pwm_channel]->PWM_THRESH;


    *duty_cycle = tmp ;

    return HAL_PWM_STATUS_OK;

}

hal_pwm_status_t hal_pwm_get_running_status(hal_pwm_channel_t pwm_channel, hal_pwm_running_status_t *running_status)
{

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    if (true == pwm_run_status[pwm_channel]) {
        /*if pwm 's clock is enable ,so which is running*/
        *running_status = HAL_PWM_BUSY;
    } else {
        /*if pwm 's clock is disabled ,so which is stopped*/
        *running_status = HAL_PWM_IDLE;
    }

    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_set_advanced_config(hal_pwm_channel_t pwm_channel, hal_pwm_advanced_config_t advanced_config)

{

    if (pwm_channel >= HAL_PWM_MAX_CHANNEL) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    if (advanced_config < HAL_PWM_CLOCK_DIVISION_2 || advanced_config > HAL_PWM_CLOCK_DIVISION_8) {
        return HAL_PWM_STATUS_INVALID_PARAMETER;
    }

    pwm[pwm_channel]->PWM_CTRL |= advanced_config;

    return HAL_PWM_STATUS_OK;

}

#endif /*HAL_PWM_MODULE_ENABLED*/


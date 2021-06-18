/* Copyright Statement:
 *
 */

/****************************************************************************
    Module Name:
    PWM

    Abstract:
    Pulse Width Modulation.

    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
***************************************************************************/



#include "hal_platform.h"

#ifdef HAL_PWM_MODULE_ENABLED
#include <string.h>
#include "type_def.h"
#include "mt7687.h"
#include "pwm.h"
#include "low_hal_pwm.h"
#include "low_hal_gpio.h"



int32_t pwm_init(uint8_t clock_source)
{
    INT32 ret = 0;

    if (PWM_CLK_SRC_NUM <= clock_source) {
        return -1;
    }

    halPWMResetAll();
    if (halPWMClockSelect((ENUM_PWM_CLK_T)clock_source)) {
        return -1;
    }

    return ret;
}

int32_t pwm_set(uint8_t index, uint32_t frequency, uint16_t duty_cycle, uint8_t enable)
{
    INT32 ret = 0;
    ENUM_PWM_STATE_T eState = PWM_S0;
    UINT16 u2DutyStep = 0;
    UINT16 u2S0StayCycle = 1;
    UINT16 u2S1StayCycle = 0;
    UINT8 ucReplayMode = 0;

    if (0 == enable) {
        // Set duty_cycle to make sure PWM to be idle.
        if (halPWMConfig(index, eState, 0, frequency)) {
            return -1;
        }

        if (halPWMKick(index)) {
            return -1;
        }

        // Disable PWM clock
        if (halPWMDisable(index)) {
            return -1;
        }
    } else {
        u2DutyStep = duty_cycle;

        if (halPWMEnable(index, 0, 0, 0)) {
            return -1;
        }

        if (halPWMConfig(index, eState, u2DutyStep, frequency)) {
            return -1;
        }

        if (halPWMStateConfig(index, u2S0StayCycle, u2S1StayCycle, ucReplayMode)) {
            return -1;
        }

        if (halPWMKick(index)) {
            return -1;
        }
    }

    return ret;
}

int32_t pwm_get(uint8_t index, uint32_t *frequency, uint16_t *duty_cycle, uint8_t *status)
{
    INT32               ret = 0;
    ENUM_PWM_STATE_T    eState = PWM_S0;

    halPWMQuery(index, eState, duty_cycle, (UINT32 *)frequency, (UINT8 *)status);

    return ret;
}


#endif


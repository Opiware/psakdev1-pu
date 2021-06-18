/* Copyright Statement:
 *
 */

#ifndef __COS_API_H__
#define __COS_API_H__


#include "type_def.h"

typedef enum {
    COS_MODULE_ON_OFF_STATE_N9_WIFI,
    COS_MODULE_ON_OFF_STATE_CM4_ADC,
    COS_MODULE_ON_OFF_STATE_CM4_AUDIO,
} cos_module_on_off_state;

kal_uint32 cos_get_systime(void);
void cos_delay_time(kal_uint32 count);
void cos_delay_ms(kal_uint32 ms);
void cos_delay_100us(kal_uint32 unit);
unsigned long SYSrand_Get_Rand(void);

#define cos_100us_to_secs(i) ((i) * 10 * 1000)
void cos_control_force_pwm_mode(cos_module_on_off_state module);
void cos_control_force_pwm_mode_exit(cos_module_on_off_state module);

#endif

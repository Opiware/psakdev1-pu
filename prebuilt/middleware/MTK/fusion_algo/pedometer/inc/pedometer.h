/* Copyright Statement:
 *
 */

#ifndef __PEDOMETER_H__
#define __PEDOMETER_H__
#include <stdint.h>

enum PEDOMETER_OPERATE_PARAMETER_T {
    PEDOMETER_STEP_LENGTH = 1,
    PEDOMETER_INFO_RESET = 2
};

#define PEDOMETER_INPUT_POLLING_INTERVAL  400

#define PEDOMETER_INPUT_SAMPLE_INTERVAL  16

void pedometer_algorithm_init();
void set_pedometer_t_s(uint32_t);
void pedometer_detector(int32_t, int32_t, int32_t);
uint16_t get_pedometer_final_step_count();
uint8_t get_pedomter_step_type();

#endif
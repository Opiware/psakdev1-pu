/* Copyright Statement:
 *
 */
#include "algo_adaptor/algo_adaptor.h"
#include <stdio.h>

void sensor_subsys_algorithm_resampling_type(resampling_t *resample)
{
    uint32_t scale_up_factor = 15;//10%
    uint32_t scale_prd = scale_up_factor * resample->input_sample_delay / 100;

    if (((resample->current_time_stamp - resample->last_time_stamp) >= (resample->input_sample_delay - scale_prd)) &&
            ((resample->current_time_stamp - resample->last_time_stamp) <= (resample->input_sample_delay + scale_prd))) {
        resample->input_count = 1;
    } else {
        resample->input_count = (resample->current_time_stamp - resample->last_time_stamp) / resample->input_sample_delay;
        if (resample->input_count > 10) {
            resample->input_count = 1;
        }
        if (resample->input_count < 1) {
            resample->input_count = 0;
        }
    }
}


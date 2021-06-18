/* Copyright Statement:
 *
 */

#ifndef __ALGO_ADAPTOR_H__
#define __ALGO_ADAPTOR_H__

#include <stdint.h>

int pedometer_init(void);
int pedometer_deinit(void);
int pedometer_register(void);

int heart_rate_monitor_init(void);
int heart_rate_monitor_register(void);

int sleep_register(void);
int sleep_init(void);

int sleep_staging_register(void);
int sleep_staging_init(void);

int32_t heart_rate_variability_monitor_register(void);
int32_t heart_rate_variability_monitor_init(void);

int blood_pressure_monitor_register(void);
int blood_pressure_monitor_init(void);

int motion_detect_register(void);
int motion_detect_init(void);

/** @brief The required imte information for fusion algorihm, used in fusion algorithm resampling. */
typedef struct resampling {
    uint32_t current_time_stamp; /* time stamp of the current sample*/
    uint32_t last_time_stamp; /* time stamp of the last sample*/
    uint32_t input_sample_delay; /* time interval between adjacent samples*/
    uint32_t init_flag; // 0: not init, 1: init
    uint32_t input_count;
} resampling_t;

void sensor_subsys_algorithm_resampling_type(resampling_t *resample);
void heart_rate_monitor_enable_watch_off_detection(uint8_t is_enable); //1: watch off enable (default), 0: watch off disable 

#endif

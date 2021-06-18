/* Copyright Statement:
 *
 */

 #ifndef __SENSOR_DEMO_H__
#define __SENSOR_DEMO_H__

#include "main_screen.h"

/* sensor data update */
void update_hr_data(int32_t bpm);
void update_hrv_data(int32_t sddn,int32_t lf,int32_t hf,int32_t lfhf);
void update_bp_data(int32_t sbp, int32_t dbp);

//#define SENSOR_DEMO /* defined in project Makefile */

void show_sensor_ready_to_connect_screen(void);
void sensor_event_handler(message_id_enum event_id, int32_t param1, void* param2);

void enable_bt_spp_server(void);
void disable_bt_spp_server(void);
void enable_all_sensors(void);
void disable_all_sensors(void);

#ifdef FUSION_HEART_RATE_VARIABILITY_USE
void enable_hrv(void);
#endif

#ifdef FUSION_BLOOD_PRESSURE_USE
void enable_bp(void);
#endif

#endif


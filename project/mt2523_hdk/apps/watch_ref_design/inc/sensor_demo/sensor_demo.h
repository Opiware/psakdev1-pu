/* Copyright Statement:
 *
 */

 #ifndef __SENSOR_DEMO_H__
#define __SENSOR_DEMO_H__

//#include "main_screen.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* syslog */
#define SENSOR_DEMO_LOGI(fmt,...) LOG_I(sensor,  (fmt), ##__VA_ARGS__)
/* printf*/
//#define SENSOR_DEMO_LOGI(fmt,arg...)   printf("SENSOR_DEMO:INFO: "fmt,##arg)


/* sensor data update */
void update_hr_data(int32_t bpm);
void update_hrv_data(int32_t sddn,int32_t lf,int32_t hf,int32_t lfhf);
void update_bp_data(int32_t sbp, int32_t dbp);

//#define SENSOR_DEMO /* defined in project Makefile */
#ifdef SENSOR_DEMO
//#define SENSOR_BTSPP /* HDK demo project removed!*/
#endif

void show_sensor_ready_to_connect_screen(void);
#ifdef SENSOR_BTSPP
void show_sensor_connected_screen(void);
#endif /*SENSOR_BTSPP*/
//void sensor_event_handler(message_id_enum event_id, int32_t param1, void* param2);

void enable_bt_spp_server(void);
void disable_bt_spp_server(void);
void enable_all_sensors(void);
void disable_all_sensors(void);

void enable_hrv(void);
void enable_bp(void);
#ifdef __cplusplus
}
#endif

#endif


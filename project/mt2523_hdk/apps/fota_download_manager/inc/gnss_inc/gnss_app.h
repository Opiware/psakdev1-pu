/* Copyright Statement:
 *
 */
 
#ifndef __GNSS_DEMO_H__
#define __GNSS_DEMO_H__

#include "FreeRTOS.h"
#include "task.h"
#include "gnss_log.h"

#define GNSS_TASK_NAME "gnss_t"
#define GNSS_TASK_STACK_SIZE 2500 //should be fine tune
#define GNSS_TASK_PRIORITY 3 //should be arrange by scenario

//Feature Config Begin

//#define GNSS_SAMPLE_APP // Without EPO / Low power / AT command / Tool bridge demo
#define GNSS_SUPPORT_EPO
#define GNSS_SUPPORT_EPO_DOWNLOAD_BY_BT
#define GNSS_SUPPORT_TOOL_BRIDGE
#define GNSS_NEED_DEBUG_INFO
#define GNSS_SLEEP_HANDLER

//Feature Config End

#define GNSS_MAX_GPGGA_SENTENCE_LENGTH 100
#define GNSS_MAX_GPGSA_SENTENCE_LENGTH 80
#define GNSS_MAX_GPRMC_SENTENCE_LENGTH 100
#define GNSS_MAX_GPVTG_SENTENCE_LENGTH 80
#define GNSS_MAX_GPGSV_SENTENCE_LENGTH 400
#define GNSS_MAX_GLGSV_SENTENCE_LENGTH 400
#define GNSS_MAX_BDGSV_SENTENCE_LENGTH 400
#define GNSS_MAX_BDGSA_SENTENCE_LENGTH 80
#define GNSS_MAX_GLGSA_SENTENCE_LENGTH 80
#define GNSS_MAX_GPACC_SENTENCE_LENGHT 80

#define GNSS_MAX_COMMAND_LENGTH 400

typedef enum gnss_message_id {
    GNSS_ENUM_POWER_ON_REQ,
    GNSS_ENUM_POWER_OFF_REQ,
    GNSS_ENUM_CONFIG_REQ,

    GNSS_ENUM_POWER_ON_CNF,
    GNSS_ENUM_POWER_OFF_CNF,
    GNSS_ENUM_READY_TO_READ,
    GNSS_ENUM_READY_TO_WRITE,

    GNSS_ENUM_SEND_COMMAND,

    GNSS_ENUM_EPO_DOWNLOAD,
    GNSS_ENUM_HOST_WAKEUP,

    GNSS_ENUM_TIME_EXPIRY
} gnss_message_id_enum;

typedef struct gnss_message_struct {
    int message_id;
    int param1;
    void *param2;
} gnss_message_struct_t;

typedef struct gnss_sentence_info {
    uint8_t  GPGGA[GNSS_MAX_GPGGA_SENTENCE_LENGTH + 1];   /* GGA data */
    uint8_t  GPGSA[GNSS_MAX_GPGSA_SENTENCE_LENGTH + 1];   /* GSA data */
    uint8_t  GPRMC[GNSS_MAX_GPRMC_SENTENCE_LENGTH + 1];   /* RMC data */
    uint8_t  GPVTG[GNSS_MAX_GPVTG_SENTENCE_LENGTH + 1];   /* VTG data */
    uint8_t  GPGSV[GNSS_MAX_GPGSV_SENTENCE_LENGTH + 1];   /* GSV data */
    uint8_t  GLGSV[GNSS_MAX_GLGSV_SENTENCE_LENGTH + 1];   /* GLONASS GSV data */
    uint8_t  GLGSA[GNSS_MAX_GLGSA_SENTENCE_LENGTH + 1];   /* GLONASS GSA data */
    uint8_t  BDGSV[GNSS_MAX_BDGSV_SENTENCE_LENGTH + 1];   /* BD GSV data */
    uint8_t  BDGSA[GNSS_MAX_BDGSA_SENTENCE_LENGTH + 1];   /* BD GSA data */
    uint8_t  GPACC[GNSS_MAX_GPACC_SENTENCE_LENGHT + 1];
} gnss_sentence_info_t;

typedef struct gnss_location_struct {
    int8_t latitude[15];
    int8_t longitude[15];
    int32_t accuracy;
    gnss_sentence_info_t nmea_sentence;
} gnss_location_struct_t;

typedef enum {
    GNSS_LOCATION_ERROR_TYPE_POWER_ON_FAIL,
    GNSS_LOCATION_ERROR_TYPE_POWER_OFF_FAIL,
    GNSS_LOCATION_ERROR_TYPE_ERROR
} gnss_location_error_type_t;

typedef enum {
    GNSS_LOCATION_HANDLE_TYPE_ERROR, // param is gnss_location_error_type_t
    GNSS_LOCATION_HANDLE_TYPE_DATA, // param is gnss_location_struct_t
} gnss_location_handle_type_t;

typedef void (*gnss_location_handle) (gnss_location_handle_type_t type, void *param);

extern void gnss_demo_app_send_cmd(int8_t *buf, int32_t buf_len);

extern void gnss_demo_app_config(int32_t periodic, gnss_location_handle handle);

extern TaskHandle_t gnss_demo_app_create();

extern void gnss_demo_app_start();

extern void gnss_demo_app_stop();

extern void epo_download_init();
#endif


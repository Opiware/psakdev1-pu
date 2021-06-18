/* Copyright Statement:
 *
 */

#include "sensor_alg_interface.h"
#include "stdio.h"
#include "algo_adaptor/algo_adaptor.h"
#include "FreeRTOS.h"

#include "icm30630.h" // get step count

/* syslog */
#define LOGI(fmt,arg...)   LOG_I(sensor, "[Pedometer]: "fmt,##arg)
#define LOGE(fmt,arg...)   LOG_E(sensor, "[Pedometer]: "fmt,##arg)
/* printf*/
//#define LOGE(fmt, args...)    printf("[Pedometer] ERR: "fmt, ##args)
//#define LOGD(fmt, args...)    printf("[Pedometer] DBG: "fmt, ##args)

static uint32_t icm_step_count;

static int32_t get_pedometer_result(sensor_data_t *const output)
{
    //calculate output;
    sensor_data_unit_t *pedometer_data = output->data;
    pedometer_data->sensor_type = SENSOR_TYPE_PEDOMETER;
    pedometer_data->time_stamp = 0;
    icm_step_count = icm_30630_get_step_count();
    pedometer_data->pedometer_t.accumulated_step_count = icm_step_count;
    pedometer_data->pedometer_t.step_type = 1;
    return 1;
}

static int32_t pedometer_process_data(const sensor_data_t *input_list, void *reserve)
{
    sensor_fusion_algorithm_notify(SENSOR_TYPE_PEDOMETER);
    return 1;
}

static int32_t pedometer_operate(int32_t command, void *buffer_out, int32_t size_out, \
                                 void *buffer_in, int32_t size_in)
{
    int32_t err = 0;

    return err;
}

const sensor_descriptor_t pedometer_desp = {
    SENSOR_TYPE_PEDOMETER, //output_type
    1, /* version */
    SENSOR_REPORT_MODE_ON_CHANGE, /* report_mode */
    NULL, /* sensor_input_list_t, smart sensr not requiring input sensor*/
    pedometer_operate,
    get_pedometer_result,
    pedometer_process_data,
    250 /* accumulate */
};

int pedometer_register(void)
{
    int ret; /*return: fail=-1, pass>=0, which means the count of current register algorithm */

    ret = sensor_fusion_algorithm_register_type(&pedometer_desp);
    if (ret < 0) {
        LOGE("fail to register Pedometer \r\n");
    }
    ret = sensor_fusion_algorithm_register_data_buffer(SENSOR_TYPE_PEDOMETER, 1);
    if (ret < 0) {
        LOGE("fail to register buffer \r\n");
    }
    return ret;
}

int pedometer_init(void)
{
    icm_step_count = 0;
    icm_30630_enable_step_count(1);
    return 1;
}

int pedometer_deinit(void)
{
    icm_30630_enable_step_count(0);
    return 1;
}



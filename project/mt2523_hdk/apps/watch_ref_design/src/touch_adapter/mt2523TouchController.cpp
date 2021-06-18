/* Copyright Statement:
 *
 */
 
#include "mt2523TouchController.hpp"
#include "hal_log.h"
#include "bsp_ctp.h"
#include "ctp.h"

using namespace touchgfx;

#define TOUCH_ADAPTER_EVENT_UP          false
#define TOUCH_ADAPTER_EVENT_DOWN        true

typedef struct {
    int32_t x;
    int32_t y;
    bool state;
} touch_adapter_point_t;

touch_adapter_point_t touch_adapter_point;

void touch_adapter_callback(void) 
{

}
void touch_adapter_init(void)
{
    bsp_ctp_gpt_sample_period_t config;
    
    bsp_ctp_init();
    
    touch_adapter_point.state       = TOUCH_ADAPTER_EVENT_UP;

    /*set to 20ms polling hardware*/
    config.high_sample_period       = 20;
    config.low_sample_period        = 20;
    config.is_used_hardware_polling = true;
    bsp_ctp_set_sample_period(&config);
    
    
    bsp_ctp_register_callback((bsp_ctp_callback_t)touch_adapter_callback, NULL);

    log_hal_info("[CTP][adapter] touch_adapter_init \r\n");
}

bool touch_adapter_get_data(int32_t *point_x, int32_t* point_y)
{
    bsp_ctp_multiple_event_t touch_event;   
    bsp_ctp_status_t         ret;
    bool                     update_flag = false;
    static bool is_power_on = false;

    /*once the touchGFX to get data, it will get all of point data out*/

    if (ctp_context.is_power_on == false) {
        *point_x = touch_adapter_point.x;
        *point_y = touch_adapter_point.y;
        if (is_power_on == false) {
            bsp_ctp_flush_buffer();
            is_power_on = true;
        }
        return touch_adapter_point.state;
    }
    else {
        is_power_on = false;
    }

    
    while(1) {
        ret = bsp_ctp_get_event_data(&touch_event);
        if (ret == BSP_CTP_OK) { 

            /*if have get up or down, do not update point, waiting to all point to be get out*/
            if (update_flag == false) {
                touch_adapter_point.x = (int32_t)touch_event.points[0].x;
                touch_adapter_point.y = (int32_t)touch_event.points[0].y;
            }
            
            /*if there is up or abort, release event*/
            if (touch_event.points[0].event == CTP_PEN_DOWN ){
                /*if there is down, press event*/
                touch_adapter_point.state = TOUCH_ADAPTER_EVENT_DOWN;
                update_flag = true;
                break;
            }
            else if ((touch_event.points[0].event == CTP_PEN_UP)) {
                touch_adapter_point.state = TOUCH_ADAPTER_EVENT_UP;
                update_flag = true;
                break;
            }
            else if (touch_event.points[0].event == CTP_PEN_ABORT) {
                bsp_ctp_flush_buffer();
                break;
            }
            else {
                /*others, while loop to get point until the all points are get out. */
            }
        }
        else { /* no point in buffer, keep last point data and unchange state*/
            break;
        }
    }

    *point_x = touch_adapter_point.x;
    *point_y = touch_adapter_point.y;

    /*log_hal_info("[CTP][adapter]get point.x = %x, point.y = %x, state = %d\r\n", \
        touch_adapter_point.x, \
        touch_adapter_point.y, \
        touch_adapter_point.state);*/
    
    return touch_adapter_point.state;
    
}

void mt2523TouchController::init()
{
    touch_adapter_init();
}

bool mt2523TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    bool    ret = false;
    int32_t ret_x = 0;
    int32_t ret_y = 0;

    ret = touch_adapter_get_data(&ret_x, &ret_y);

    x = ret_x;
    y = ret_y;
    
    return ret;
}


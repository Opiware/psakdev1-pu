/* Copyright Statement:
 *
 */

/**
 * @file pinmux.h
 *
 *  Configure pinmux settings.
 * */

#include "hal_gpio.h"
#ifdef HAL_GPIO_MODULE_ENABLED

#ifndef __PINMUX_H__
#define __PINMUX_H__

#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    eIOT_GPIO_IDX_0 = 0,
    eIOT_GPIO_IDX_1 = 1,
    eIOT_GPIO_IDX_2 = 2,
    eIOT_GPIO_IDX_3 = 3,
    eIOT_GPIO_IDX_4 = 4,
    eIOT_GPIO_IDX_5 = 5,
    eIOT_GPIO_IDX_6 = 6,
    eIOT_GPIO_IDX_7 = 7,

    eIOT_GPIO_IDX_24 = 24,
    eIOT_GPIO_IDX_25 = 25,
    eIOT_GPIO_IDX_26 = 26,
    eIOT_GPIO_IDX_27 = 27,
    eIOT_GPIO_IDX_28 = 28,
    eIOT_GPIO_IDX_29 = 29,
    eIOT_GPIO_IDX_30 = 30,
    eIOT_GPIO_IDX_31 = 31,
    eIOT_GPIO_IDX_32 = 32,
    eIOT_GPIO_IDX_33 = 33,
    eIOT_GPIO_IDX_34 = 34,
    eIOT_GPIO_IDX_35 = 35,
    eIOT_GPIO_IDX_36 = 36,
    eIOT_GPIO_IDX_37 = 37,
    eIOT_GPIO_IDX_38 = 38,
    eIOT_GPIO_IDX_39 = 39,

    eIOT_GPIO_IDX_57 = 57,
    eIOT_GPIO_IDX_58 = 58,
    eIOT_GPIO_IDX_59 = 59,
    eIOT_GPIO_IDX_60 = 60,

} ENUM_IOT_GPIO_NAME_T;


/**
 * @brief  Configure pinmux settings of GPIO pin for selected function.
 *
 * @param  gpio_index [IN] Index of GPIO pin.
 * @param  function [IN] Selected function of GPIO pin.
 *
 * @return >=0 means success, <0 means fail.
 * */
int32_t pinmux_config(ENUM_IOT_GPIO_NAME_T gpio_index, uint32_t function);


#ifdef __cplusplus
}
#endif

#endif /* __PINMUX_H__ */
#endif


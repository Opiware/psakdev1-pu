/* Copyright Statement:
 *
 */

#ifndef _EINT_KEY_H_
#define _EINT_KEY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hal_gpio.h"
#include "hal_eint.h"



typedef struct {
    hal_gpio_pin_t    gpio_port;    /*GPIO port*/
    uint8_t           eint_mode;    /*GPIO eint mode*/
    hal_eint_number_t eint_number;  /*eint number*/
    uint8_t           key_data;     /*keydata define by user*/
} bsp_eint_key_mapping_t;

typedef struct {
    uint32_t    longpress_time;     /*longpress time setting*/
    uint32_t    repeat_time;        /*repeat time setting*/
} bsp_eint_key_config_t;

/** This enum defines keypad event status */
typedef enum {
    BSP_EINT_KEY_RELEASE        = 0,        /**< A key is released. */
    BSP_EINT_KEY_PRESS          = 1,        /**< A key is pressed. */
    BSP_EINT_KEY_LONG_PRESS     = 2,        /**< A key is long pressed. */
    BSP_EINT_KEY_REPEAT         = 3,        /**< A key is repeat pressed. */
} bsp_eint_key_event_t;

typedef void (*bsp_eint_key_callback_t)(bsp_eint_key_event_t event, uint8_t key_data, void *user_data);


bool bsp_eint_key_init(bsp_eint_key_config_t *config);
bool bsp_eint_key_register_callback(bsp_eint_key_callback_t callback, void *user_data);
bool bsp_eint_key_set_event_time(bsp_eint_key_config_t *config);
bool bsp_eint_key_set_debounce_time(uint32_t debounce_time);
bool bsp_eint_key_enable(void);


#ifdef __cplusplus
}
#endif

#endif /* _EINT_KEY_CUSTOM_H_ */


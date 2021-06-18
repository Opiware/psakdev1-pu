/* Copyright Statement:
 *
 */

#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#ifdef MTK_LED_ENABLE

#include "bsp_led_internal.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @brief This enum define API status of LED */
typedef enum {
    BSP_LED_ERROR             = -2,         /**< This value means a led function EEROR */
    BSP_LED_INVALID_PARAMETER = -1,         /**< This value means an invalid parameter */
    BSP_LED_OK                = 0           /**< This value meeas no error happen during the function call*/
} bsp_led_status_t;


/** @brief This enum defines state of LED */
typedef enum {
    BSP_LED_OFF  = 0,               /**< define led state of off */
    BSP_LED_ON = 1                  /**< define led state of on */
} bsp_led_state_t;

/** initialzie selected LED**/
bsp_led_status_t bsp_led_init(uint32_t led_number);


/** turn on the selected LED **/
bsp_led_status_t bsp_led_on(uint32_t led_number);


/** turn off the selected LED **/
bsp_led_status_t bsp_led_off(uint32_t led_number);


/** toggle the selected LED **/
bsp_led_status_t bsp_led_toggle(uint32_t led_number);


/* Return the current state of a selected LED */
bsp_led_status_t bsp_led_get_state(uint32_t led_number, bsp_led_state_t *led_state);


#ifdef __cplusplus
}
#endif

#endif /*MTK_LED_ENABLE*/
#endif /* __BSP_LED_H__ */



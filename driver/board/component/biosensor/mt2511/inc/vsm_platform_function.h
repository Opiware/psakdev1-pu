/* Copyright Statement:
 *
 */

#ifndef __VSM_PLATFORM_FUNCTION_H_
#define __VSM_PLATFORM_FUNCTION_H_
#include <stdint.h>
#include "hal_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

//extern gpio var by name
extern const char BSP_BIO_SENSOR_PPG_VDRV_EN;
extern const char BSP_BIO_SENSOR_32K;
extern const char BSP_BIO_SENSOR_AFE_PWD_PIN;
extern const char BSP_BIO_SENSOR_RST_PORT_PIN;
#define GPIO_MT2511_PPG_VDRV_EN     (hal_gpio_pin_t)BSP_BIO_SENSOR_PPG_VDRV_EN
#define GPIO_MT2511_32K             (hal_gpio_pin_t)BSP_BIO_SENSOR_32K
#define GPIO_MT2511_AFE_PWD_PIN     (hal_gpio_pin_t)BSP_BIO_SENSOR_AFE_PWD_PIN
#define GPIO_MT2511_RST_PORT_PIN    (hal_gpio_pin_t)BSP_BIO_SENSOR_RST_PORT_PIN

void vsm_platform_gpio_get_output(int32_t gpio_pin, int32_t *gpio_data);

void vsm_platform_gpio_set_output(int32_t gpio_pin, int32_t gpio_data);

void vsm_platform_gpio_get_direction(int32_t gpio_pin, int32_t *gpio_direction);

void vsm_platform_gpio_set_direction(int32_t gpio_pin, int32_t gpio_direction);

void vsm_platform_gpio_set_pinmux(int32_t gpio_pin, uint8_t function_index);

void vsm_platform_gpio_init(int32_t gpio_pin);

void vsm_platform_gpio_deinit(int32_t gpio_pin);

void ms_delay(uint32_t ms);

uint32_t vsm_platform_get_ms_tick(void);

#ifdef __cplusplus
extern }
#endif

#endif /* __VSM_PLATFORM_FUNCTION_H_ */



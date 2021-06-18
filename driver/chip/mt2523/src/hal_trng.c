/* Copyright Statement:
 *
 */

#include "hal_trng.h"

#ifdef HAL_TRNG_MODULE_ENABLED

#include "hal_trng_internal.h"

volatile static uint8_t trng_init_status = 0;


hal_trng_status_t hal_trng_init(void)
{
	hal_trng_status_t busy_status;
	TRNG_CHECK_AND_SET_BUSY(busy_status);
    if (HAL_TRNG_STATUS_ERROR == busy_status) {
        return HAL_TRNG_STATUS_ERROR;
    }

    trng_init();
    return HAL_TRNG_STATUS_OK;
}

hal_trng_status_t hal_trng_deinit(void)
{
    trng_deinit();
    TRNG_SET_IDLE();
    return HAL_TRNG_STATUS_OK;
}

hal_trng_status_t hal_trng_get_generated_random_number(uint32_t *random_number)
{
    uint32_t generate_data = 0;
    trng_config_timeout_limit(0xFFF);
    trng_enable_mode(true, true, true);
    trng_start();
    generate_data = trng_get_random_data();
    trng_stop();
    if (generate_data == 0) {
        return  HAL_TRNG_STATUS_ERROR;
    } else {
        *random_number = generate_data;
    }

    return HAL_TRNG_STATUS_OK;
}

#endif /*HAL_TRNG_MODULE_ENABLED*/



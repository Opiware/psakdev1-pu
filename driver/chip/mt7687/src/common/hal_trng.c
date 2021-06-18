/* Copyright Statement:
 *
 */

/****************************************************************************
    Module Name:
    Truely Random Number Generator

***************************************************************************/

#include "hal_trng.h"

#ifdef HAL_TRNG_MODULE_ENABLED
#include <stdio.h>
#include <string.h>
#include "type_def.h"
#include "mt7687_cm4_hw_memmap.h"
#include "timer.h"

extern void delay_time(kal_uint32 count);
/**
 * @brief    This function is mainly used to initialize TRUE RANDOM NUMBER GENERATOR hardware .
 * @return    To indicate whether this function call success or not.
 *            If the return value is #HAL_TRNG_OK,it means success;
 * @sa  #hal_trng_deinit
 * @ Example     hal_trng_init(); */

hal_trng_status_t hal_trng_init(void)
{
    return HAL_TRNG_STATUS_OK;
}

/**
 * @brief   This function is mainly used to de-initialize TRUE RANDOM NUMBER GENERATOR hardware.
 * @return    To indicate whether this function call success or not.
 *            If the return value is #HAL_TRNG_OK,it means success;
 * @sa  #hal_trng_init
 * @Example  hal_trng_deinit(); */
hal_trng_status_t hal_trng_deinit(void)
{
    return HAL_TRNG_STATUS_OK;
}

/**
 * @brief  This function is mainly used to get  random number which trng generated
 * @param[out]   *random_number is  get random number and which puts the value in *random_number.
 * @return    To indicate whether this function call success or not.
 *               If the return value is #HAL_TRNG_OK,it means success;
 * @ Example   hal_trng_get_generated_random_number(&random_number);
 */

hal_trng_status_t hal_trng_get_generated_random_number(uint32_t *random_number)
{
    UINT16 cnt = 0;

    mSetHWEntry(IOT_CRYPTO_TRNG_CTRL_ENABLE, 1);

    while (cnt < 100) {
        if (mGetHWEntry(IOT_CRYPTO_TRNG_INT_SET) == 1) {
            break;
        }
        delay_time(32);
        cnt++;
    }

    *random_number = mGetHWEntry(IOT_CRYPTO_TRNG_DATA);
    mSetHWEntry(IOT_CRYPTO_TRNG_INT_CLR, 1);
    mSetHWEntry(IOT_CRYPTO_TRNG_CTRL_ENABLE, 0);

    if (cnt >= 100) {
        *random_number = 0x0;
        return HAL_TRNG_STATUS_ERROR;
    } else {
        return HAL_TRNG_STATUS_OK;
    }
}

#endif


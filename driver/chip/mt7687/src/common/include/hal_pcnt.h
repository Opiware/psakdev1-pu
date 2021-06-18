/* Copyright Statement:
 *
 */

#ifndef __HAL_PCNT_H__
#define __HAL_PCNT_H__

#include "hal_gpc.h"

#ifdef HAL_GPC_MODULE_ENABLED
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file hal_pcnt.h
 *
 * @brief This file provides the API for pulse counter detection.
 * */

typedef enum {
    HAL_PCNT_STATUS_OK,
    HAL_PCNT_STATUS_NOT_SUPPORTED,
    HAL_PCNT_STATUS_INVALID_PARAMETER
} hal_pcnt_status_t;


typedef enum {
    HAL_PCNT_EDGE_FALLING,
    HAL_PCNT_EDGE_RAISING
} hal_pcnt_edge_t;


/**
 * Initialize pulse counter.
 *
 * Initialize an GPIO pin as a pulse counter.
 *
 * @param pin The GPIO pin number. */
hal_pcnt_status_t hal_pcnt_config(bool enable, hal_pcnt_edge_t edge);


/**
 * Read the counter number and return to caller and clear the current counter.
 *
 * Read the counter number and return to caller and clear the current counter,
 * the counter is resetted to 0 after this function returns.
 *
 * @retval the current counter content. The return value is not useful if
 * pulse counter is not enabled and shall not be used. */
uint32_t hal_pcnt_read_and_clear(void);


#ifdef __cplusplus
}
#endif

#endif

#endif /* __HAL_PCNT_H__ */

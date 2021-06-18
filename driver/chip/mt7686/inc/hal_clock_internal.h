/* Copyright Statement:
 *
 */

#ifndef __HAL_CLOCK_INTERNAL_H__
#define __HAL_CLOCK_INTERNAL_H__

#include "hal_platform.h"

#ifdef HAL_CLOCK_MODULE_ENABLED

#include "hal_clock_platform_mt7686.h"
#include "memory_attribute.h"
#include "hal_clock.h"

/*************************************************************************
 * Define customized function prototype
 *************************************************************************/
uint32_t hal_clock_get_freq_meter(uint8_t tcksel, uint8_t fcksel);
uint32_t hal_clock_get_freq_meter_cycle(uint8_t tcksel, uint8_t fcksel, uint16_t winset);
void hal_clock_set_pll_dcm_init(void);
void clock_dump_info(void);

hal_clock_status_t clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel);

/* Suspend/Resume */
ATTR_TEXT_IN_TCM hal_clock_status_t clock_suspend(void);
ATTR_TEXT_IN_TCM hal_clock_status_t clock_resume(void);

bool hal_clock_fxo_is_26m(void);

#endif /* HAL_CLOCK_MODULE_ENABLED */
#endif /* __HAL_CLOCK_INTERNAL_H__ */

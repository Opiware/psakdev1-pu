/* Copyright Statement:
 *
 */

#ifndef __HAL_DWT_H__
#define __HAL_DWT_H__

#include "hal_platform.h"

#ifdef HAL_DWT_MODULE_ENABLED

typedef enum { // now only suppuort for EMITRANGE=0, CYCMATCH = 0
    COMP_DISABLE = 0,
    WDE_INST = 4, // 0x0100: Generate PC watchpoint debug event whem instruction fetches
    WDE_DATA_RO,  //    0x0101: Generate watchpoint debug event when read data accesses
    WDE_DATA_WO,  //    0x0110: Generate watchpoint debug event when write data accesses
    WDE_DATA_RW   //    0x0111: Generate watchpoint debug event when read/write data accesses
} DWT_FUNC_TYPE;

typedef enum {
    HAL_DWT_0 = 0,
    HAL_DWT_1 = 1,
    HAL_DWT_2 = 2,
    HAL_DWT_3 = 3,  /* used for pxCurrentTCB stack overflow check */
    HAL_DWT_MAX
} DWT_COMPARATOR_PORT;

/* DWT APIs **********************************************************/
void hal_dwt_reset(void);
void hal_dwt_init(void);
void hal_dwt_dump_status(void);

int32_t hal_dwt_request_watchpoint(uint32_t index, uint32_t addr_base, uint32_t addr_mask, DWT_FUNC_TYPE func);

#endif /* HAL_DWT_MODULE_ENABLED */
#endif /* __DWT_H__ */

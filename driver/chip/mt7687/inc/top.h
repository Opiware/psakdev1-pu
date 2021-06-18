/* Copyright Statement:
 *
 */

/**
 * @file top.h
 *
 *  XTAL control function
 * */
#ifndef __TOP_H__
#define __TOP_H__

#include "stdint.h"
#include "system_mt7687.h"


#ifdef __cplusplus
extern "C" {
#endif

void top_xtal_init(void);
uint32_t top_xtal_freq_get(void);
uint32_t top_mcu_freq_get(void);
void cmnPLL1ON(void);
void cmnPLL1ON_PLL2ON(uint8_t fg960M);
void cmnPLL1OFF_PLL2OFF(void);
void cmnCpuClkConfigureToXtal(void);
void cmnCpuClkConfigureTo64M(void);
void cmnCpuClkConfigureTo160M(void);
void cmnCpuClkConfigureTo192M(void);
void cmnSerialFlashClkConfToXtal(void);
void cmnSerialFlashClkConfTo64M(void);


#ifdef __cplusplus
}
#endif

#endif /* __TOP_H__*/


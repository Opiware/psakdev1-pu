/* Copyright Statement:
 *
 */

/**
 * @author  MTK
 * @version 1.0
 * @date    2015.10.29
 * */
#include "hal_platform.h"


#define DCXO_BASE            		                (0xA21D0000) /* DSP_TOPSM_BASW: 0x83010000 is used for Larkspur */
#define ACFG_DCXO_PCON2             ((volatile uint32_t*)(DCXO_BASE+0x38)) /* DCXO power control 2 */
#define ACFG_DCXO_PCON0             ((volatile uint32_t*)(DCXO_BASE+0x30))
#define ACFG_DCXO_PCON1             ((volatile uint32_t*)(DCXO_BASE+0x34))
#define ACFG_PCLK_CON               ((volatile uint32_t*)(DCXO_BASE+0x14))
#define PLL_DPM_CON1                ((volatile uint32_t*) 0xA2040094)

void hal_dcxo_init(void);
bool hal_dcxo_is_32kless(void);


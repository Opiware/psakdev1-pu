/* Copyright Statement:
 *
 */

#ifndef __BL_CLOCK_H__
#define __BL_CLOCK_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "mt2523.h"

/*************************************************************************
 * Define HW register
 *************************************************************************/
/** Module name: mixed Base address: (+A2040000h) 16 width */
#define PLL_CLKSQ_CON0          ((volatile uint16_t*)(MIXED_BASE+0x0020))
#define PLL_PLL_CON4            ((volatile uint16_t*)(MIXED_BASE+0x0050))
#define PLL_MPLL_CON0           ((volatile uint16_t*)(MIXED_BASE+0x0100))
#define PLL_MPLL_CON1           ((volatile uint16_t*)(MIXED_BASE+0x0104))
#define PLL_UPLL_CON0           ((volatile uint16_t*)(MIXED_BASE+0x0140))
#define PLL_UPLL_CON1           ((volatile uint16_t*)(MIXED_BASE+0x0144))
#define PLL_MDDS_CON0           ((volatile uint16_t*)(MIXED_BASE+0x0640))
#define PLL_PLLTD_CON0          ((volatile uint16_t*)(MIXED_BASE+0x0700))
#define PLL_LFOSC_CON0          ((volatile uint16_t*)(MIXED_BASE+0x0900))
#define PLL_LFOSC_CON1          ((volatile uint16_t*)(MIXED_BASE+0x0904))
#define PLL_HFOSC_CON0          ((volatile uint16_t*)(MIXED_BASE+0x0920))
#define PLL_HFOSC_CON1          ((volatile uint16_t*)(MIXED_BASE+0x0924))

/** Module name: mixed_sub Base address: (+A2040000h) 16 width */
#define PLL_PLL_CON2            ((volatile uint16_t*)(MIXED_BASE+0x0048))
#define PLL_PLL_CON3            ((volatile uint16_t*)(MIXED_BASE+0x004C))
#define PLL_ABIST_FQMTR_CON0    ((volatile uint16_t*)(MIXED_BASE+0x0400))
#define PLL_ABIST_FQMTR_CON1    ((volatile uint16_t*)(MIXED_BASE+0x0404))
#define PLL_ABIST_FQMTR_CON2    ((volatile uint16_t*)(MIXED_BASE+0x0408))
#define PLL_ABIST_FQMTR_DATA    ((volatile uint16_t*)(MIXED_BASE+0x040C))
#define PLL_SYS_ABIST_MON_CON1  ((volatile uint16_t*)(MIXED_BASE+0x0424))

/** Module name: configsys Base address: (+A2010000h) 32 width */
#define BL_CLK_CONDA            ((volatile uint32_t*)(CONFIG_BASE+0x0100))
#define BL_CLK_CONDB            ((volatile uint32_t*)(CONFIG_BASE+0x0104))
#define BL_CLK_CONDD            ((volatile uint32_t*)(CONFIG_BASE+0x010C))
#define BL_CLK_CONDF            ((volatile uint32_t*)(CONFIG_BASE+0x0114))
#define BL_CLK_CONDG            ((volatile uint32_t*)(CONFIG_BASE+0x0118))
#define BL_CLK_CONDH            ((volatile uint32_t*)(CONFIG_BASE+0x011C))
#define BL_CLK_SOURCE_SEL       ((volatile uint32_t*)(CONFIG_BASE+0x0180))
#define BL_SLEEP_COND           ((volatile uint32_t*)(CONFIG_BASE+0x0200))
#define BL_TOP_DEBUG            ((volatile uint32_t*)(CONFIG_BASE+0x0238))
#define BL_PDN_COND2            ((volatile uint32_t*)(CONFIG_BASE+0x0308))
#define BL_PDN_SETD0            ((volatile uint32_t*)(CONFIG_BASE+0x0310))
#define BL_PDN_SETD1            ((volatile uint32_t*)(CONFIG_BASE+0x0314))
#define BL_PDN_SETD2            ((volatile uint32_t*)(CONFIG_BASE+0x0314))
#define BL_PDN_CLRD1            ((volatile uint32_t*)(CONFIG_BASE+0x0324))
#define BL_PDN_CLRD2            ((volatile uint32_t*)(CONFIG_BASE+0x0328))

/** Module name: gpio_reg Base address: (+A2020000h) 32 width */
#define BL_GPIO_DIR0            ((volatile uint32_t*)(GPIO_BASE+0x0000))
#define BL_GPIO_DIR0_SET        ((volatile uint32_t*)(GPIO_BASE+0x0004))
#define BL_GPIO_DIR0_CLR        ((volatile uint32_t*)(GPIO_BASE+0x0008))
#define BL_GPIO_MODE3           ((volatile uint32_t*)(GPIO_BASE+0x0C30))
#define BL_GPIO_MODE3_SET       ((volatile uint32_t*)(GPIO_BASE+0x0C34))
#define BL_GPIO_MODE3_CLR       ((volatile uint32_t*)(GPIO_BASE+0x0C38))

/** Module name: cm_mems_dcm_cfg Base address: (+A20A0000h) 32 width */
#define BL_CM4_DCM_CON          ((volatile uint32_t*)(CM_MEMS_DCM_BASE+0x0150))
#define BL_MEMS_DCM_CON         ((volatile uint32_t*)(CM_MEMS_DCM_BASE+0x0154))

/** Module name: ana_cfgsys Base address: (+A21D0000h) 16 width */
#define BL_ACFG_CLK_UPDATE      ((volatile uint16_t*)(ANA_CFGSYS_BASE+0x0150))
#define BL_ACFG_FREQ_SWCH       ((volatile uint16_t*)(ANA_CFGSYS_BASE+0x0154))

/*************************************************************************
 * Define customized function prototype
 *************************************************************************/
void clock_set_pll_dcm_init(void);
uint32_t bl_clock_freq_monitor(uint16_t tcksel, uint16_t fcksel, bool over78m);

/*************************************************************************
  * Define macros.
 *************************************************************************/
#define ABS(x)  (x < 0) ? (-x) : x
#define CLK_OVER_78M true
#define CLK_LOWER_78M false

#endif /* __BL_CLOCK_H__ */

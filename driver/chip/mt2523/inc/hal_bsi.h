/* Copyright Statement:
 *
 */

#include "hal_platform.h"

//#define BSI_BASE            		                (0x83070000) /* BSI_BASE BSI_BASE: 0x83070000 is used for Larkspur */
#define PDN_CLRD0            ((volatile uint32_t*)0xA2010320)
#define PDN_COND0            ((volatile uint32_t*)0xA2010300)
#define BSI_CON              ((volatile uint32_t*)(BSI_BASE+0x0)) /* BSI control register */
#define BSI_WRDAT_CON        ((volatile uint32_t*)(BSI_BASE+0x4)) /* Control part of write data register */
#define BSI_WRDAT            ((volatile uint32_t*)(BSI_BASE+0x8)) /* Data part of write data register */
#define BSI_RDCON            ((volatile uint32_t*)(BSI_BASE+0xc40)) /* BSI Read Back Control */
#define BSI_RDADDR_CON       ((volatile uint32_t*)(BSI_BASE+0xc44)) /* BSI IMM Read Back Address Part */
#define BSI_RDADDR           ((volatile uint32_t*)(BSI_BASE+0xc48)) /* BSI Read Back ADDR */
#define BSI_RDCS_CON         ((volatile uint32_t*)(BSI_BASE+0xc4c)) /* BSI Read Back CS Waveform (Transition & Rdata part) */
#define BSI_RDDAT            ((volatile uint32_t*)(BSI_BASE+0xc50)) /* BSI Read Back Data */
#define MODEM_CG_CLR4        ((volatile uint32_t*)0x83000098)
#define MODEM_CG_CLR2        ((volatile uint32_t*)0x83000018)
#define MODEM_CG_CON4        ((volatile uint32_t*)0x83000088)
#define MODEM_CG_SET4        ((volatile uint32_t*)0x83000088)
#define PDN_CLRD0            ((volatile uint32_t*)0xA2010320)
#define PDN_COND0            ((volatile uint32_t*)0xA2010300)

void bsi_write(uint8_t address , uint32_t data); /* bsi write */
void bsi_read(uint8_t address , uint32_t *data);  /* bsi read */
void bsi_init(void);

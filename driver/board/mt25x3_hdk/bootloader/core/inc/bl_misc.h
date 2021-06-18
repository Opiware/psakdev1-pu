/* Copyright Statement:
 *
 */

#ifndef __BL_MISC_H__
#define __BL_MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define BL_GPDAC_BASE 0XA21B0000
#define BL_GPDAC_GPDAC_SRAM_PWR BL_GPDAC_BASE + 0x50

#define bl_gpdac_sram_power_down()  (*((volatile unsigned int *)(BL_GPDAC_GPDAC_SRAM_PWR)) = (unsigned int)0x6)
void bl_bonding_io_reg(void);
void bl_d2d_io_pull_down(void);

#ifdef __cplusplus
}
#endif

#endif /* __BL_MISC_H__ */

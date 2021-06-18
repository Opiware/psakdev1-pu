/* Copyright Statement:
 *
 */

#ifndef __HAL_SPI_SLAVE_INTERNAL_H__
#define __HAL_SPI_SLAVE_INTERNAL_H__

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED

/*define SPIS register address*/
#define  SPIS_AHB_REG05            ((uint32_t)0x21000714)
#define  SPIS_AHB_REG06            ((uint32_t)0x21000718)
#define  SPIS_AHB_REG08            ((uint32_t)0x21000740)

/*SPIS datasheet required setting*/
#define PAD_SDIO_DAT2_CTL          ((uint32_t)0x81023058)
#define PAD_SDIO_DAT3_CTL          ((uint32_t)0x8102305C)


#define SPIS_20M_CLOCK_ENABLE() (*((uint32_t *)SPIS_AHB_REG06) |= 0x40)

/* clear SW irq */
#define SPIS_CLEAR_IRQ() (*((uint32_t *)SPIS_AHB_REG05) = 1)

/*
Mode 1 (CPOL =0 / CPHA=0)
Write address [0x21000718], Bit[6] = 0x1
Write address [0x21000740], Bit[1:0] = 0x0
Write address [0x81023058], Bit[5] = 0x1
Write address [0x8102305c], Bit[5] = 0x0
*/
/*
Mode 2 (CPOL =0 / CPHA=1)
Write address [0x21000718], Bit[6] = 0x1
Write address [0x21000740], Bit[1:0] = 0x1
Write address [0x81023058], Bit[5] = 0x1
Write address [0x8102305c], Bit[5] = 0x1
*/
/*
Mode 3 (CPOL =1 / CPHA=0)
Write address [0x21000718], Bit[6] = 0x1
Write address [0x21000740], Bit[1:0] = 0x2
Write address [0x81023058], Bit[5] = 0x1
Write address [0x8102305c], Bit[5] = 0x1
*/
/*
Mode 4 (CPOL =1 / CPHA=1)
Write address [0x21000718], Bit[6] = 0x1
Write address [0x21000740], Bit[1:0] = 0x3
Write address [0x81023058], Bit[5] = 0x1
Write address [0x8102305c], Bit[5] = 0x0
*/

#define SPIS_SET_MODE(mode)                                   \
do{                                                           \
       (*((uint32_t *)SPIS_AHB_REG08) = mode);                \
       (*((uint32_t *)PAD_SDIO_DAT2_CTL) |= 0x20);            \
       if ((mode == 0) || (mode ==3)) {                       \
           (*((uint32_t *)PAD_SDIO_DAT3_CTL) &= 0xffffffdf);  \
       } else {                                               \
           (*((uint32_t *)PAD_SDIO_DAT3_CTL) |= 0x20);        \
       }                                                      \
}while(0)

#endif   /* HAL_SPI_SLAVE_MODULE_ENABLED */
#endif   /*__HAL_SPI_SLAVE_INTERNAL_H__*/



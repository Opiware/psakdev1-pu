/* Copyright Statement:
 *
 */

#ifndef __EMI_HW_INTERNAL_H__
#define __EMI_HW_INTERNAL_H__

#include "sw_types.h"

/*
#if !defined(_REG_BASE_H)
#error "reg_base.h must be included first"
#endif
*/
#define EMI_base 0xA0050000

#define EMI_CONM                 ((volatile uint32_t *)(EMI_base+0x0060))

#define EMI_GENA                 ((volatile uint32_t *)(EMI_base+0x0070))
#define EMI_RDCT                 ((volatile uint32_t *)(EMI_base+0x0088))
#define EMI_DLLV                 ((volatile uint32_t *)(EMI_base+0x0090))

#define EMI_IDLC                 ((volatile uint32_t *)(EMI_base+0x00D0))
#define EMI_IDLD                 ((volatile uint32_t *)(EMI_base+0x00D8))
#define EMI_IDLE                 ((volatile uint32_t *)(EMI_base+0x00E0))

#define EMI_ODLC	             ((volatile uint32_t *)(EMI_base+0x00F8))
#define EMI_ODLD	             ((volatile uint32_t *)(EMI_base+0x0100))
#define EMI_ODLE	             ((volatile uint32_t *)(EMI_base+0x0108))
#define EMI_ODLF	             ((volatile uint32_t *)(EMI_base+0x0110))

#define EMI_IOA	                 ((volatile uint32_t *)(EMI_base+0x0130))
#define EMI_IOB	                 ((volatile uint32_t *)(EMI_base+0x0138))

#define EMI_HFSLP                    ((volatile uint32_t *)(EMI_base+0x0148))
#define EMI_DSRAM	             ((volatile uint32_t *)(EMI_base+0x0150))
#define EMI_MSRAM	             ((volatile uint32_t *)(EMI_base+0x0158))
#define EMI_MREG_RW	      ((volatile uint32_t *)(EMI_base+0x0160))

#define EMI_ARBA                 ((volatile uint32_t *)(EMI_base+0x0170))
#define EMI_ARBB                 ((volatile uint32_t *)(EMI_base+0x0178))
#define EMI_ARBC                 ((volatile uint32_t *)(EMI_base+0x0180))
#define EMI_SLCT                 ((volatile uint32_t *)(EMI_base+0x0198))
#define EMI_ABCT	           ((volatile uint32_t *)(EMI_base+0x01A0))

#define EMI_BMEN                 ((volatile uint32_t *)(EMI_base+0x0200))
#define EMI_BCNT                 ((volatile uint32_t *)(EMI_base+0x0208))
#define EMI_TACT                 ((volatile uint32_t *)(EMI_base+0x0210))
#define EMI_TSCT                 ((volatile uint32_t *)(EMI_base+0x0218))
#define EMI_WACT                 ((volatile uint32_t *)(EMI_base+0x0220))
#define EMI_WSCT                 ((volatile uint32_t *)(EMI_base+0x0228))
#define EMI_BACT                 ((volatile uint32_t *)(EMI_base+0x0230))
#define EMI_BSCT0                ((volatile uint32_t *)(EMI_base+0x0238))
#define EMI_BSCT1                ((volatile uint32_t *)(EMI_base+0x0240))
#define EMI_TTYPE1               ((volatile uint32_t *)(EMI_base+0x0280))


#define EMI_MBISTA               ((volatile uint32_t *)(EMI_base+0x0300))
#define EMI_MBISTB               ((volatile uint32_t *)(EMI_base+0x0308))
#define EMI_MBISTC               ((volatile uint32_t *)(EMI_base+0x0310))
#define EMI_MBISTD               ((volatile uint32_t *)(EMI_base+0x0318))

#define EMI_TEST                   ((volatile uint32_t *)(EMI_base+0x0330))

#define EMI_VENDOR_INFO    ((volatile UINT32P)(EMI_base+0x0348))


#define RG_VCORE_VOSEL       ((volatile uint16_t *)(0xA0700230))
#define VIO_18_REG           ((volatile uint16_t *)(0xA0700200))
#define BOOT_CON             ((volatile uint16_t *)(0xA0510000))
#define CM4_BOOT_FROM_SLV    ((volatile uint32_t *)(0xA2110008))

#endif  /* !__EMI_HW_INTERNAL_H__ */


/* Copyright Statement:
 *
 */

#ifndef __BL_MTK_BB_REG_H__
#define __BL_MTK_BB_REG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile unsigned int *BL_P_UINT_32;

#define BL_GPT_BASE 0xA21B0000

#define BL_RETN_USBDL_TYPE_MASK        0x00000002  /* 0: BROM USBDL; 1: BL USBDL */
#define BL_RETN_USBDL_BY_FLAG_EN       0x00000004  /* 0: Disabled; 1: Enabled */
#define BL_RETN_USBDL_TRIGGERED_BY_BL  0x00000080

#ifdef __cplusplus
}
#endif

#endif /* __BL_MTK_BB_REG_H__ */

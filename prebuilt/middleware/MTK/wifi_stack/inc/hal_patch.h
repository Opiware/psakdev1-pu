/* Copyright Statement:
 *
 */

#ifndef _HAL_PATCH_H
#define _HAL_PATCH_H

#include "rt_config.h"

#define LP_HWIS0R			(WIFI_INT_BASE + 0x003C)
#define LP_HWIE0R			(WIFI_INT_BASE + 0x0040)
#define LP_HWIS1R			(WIFI_INT_BASE + 0x0044)
#define LP_HWIE1R			(WIFI_INT_BASE + 0x0048)
#define LP_HWIS2R			(WIFI_INT_BASE + 0x004C)
#define LP_HWIE2R			(WIFI_INT_BASE + 0x0050)
#define LP_HWIS3R			(WIFI_INT_BASE + 0x0054)
#define LP_HWIE3R			(WIFI_INT_BASE + 0x0058)
#define LP_HWIS4R			(WIFI_INT_BASE + 0x004C)
#define LP_HWIE4R			(WIFI_INT_BASE + 0x0060)



#define TXM_ALL_TX_Q_BITMAP \
    BITS(TX_Q_AC0, TX_Q_AC14)

typedef struct _TX_AC_PARAM_T
{
    UINT_8 ucAcNum;
    UINT_8 ucVaildBit;
    UINT_8 ucAifs;
    UINT_8 ucWinMin;
    UINT_16 u2WinMax;
    UINT_16 u2Txop;
}TX_AC_PARAM_T,*P_TX_AC_PARAM_T;
#define MASK_AIFS_SET   BIT(0)
#define MASK_WINMIN_SET BIT(1)
#define MASK_WINMAX_SET BIT(2)
#define MASK_TXOP_SET   BIT(3)

#ifndef E2_ROM_7682
VOID
txmStartQueue(
    IN UINT_32 u4QueIdxBitmap,
    IN UINT_8 ucOwnMacIdx
    );
VOID
txmStopQueue(
    IN UINT_32 u4QueIdxBitmap,
    IN UINT_8 ucOwnMacIdx,
    IN BOOLEAN fgAbort
    );

#else
extern VOID
(*txmStartQueue)(
    IN UINT_32 u4QueIdxBitmap,
    IN UINT_8 ucOwnMacIdx
    );
extern VOID
(*txmStopQueue)(
    IN UINT_32 u4QueIdxBitmap,
    IN UINT_8 ucOwnMacIdx,
    IN BOOLEAN fgAbort
    );
#endif

HAL_STATUS halTxConfigACAifs(
		IN UINT_8 ucQueueIdx,
		IN UINT_8 ucAifs
		);
HAL_STATUS halTxConfigACWinMin(
    IN UINT_8 ucQueueIdx,
    IN UINT_8 ucWinMin
    );

HAL_STATUS halTxConfigACWinMax(
    IN UINT_8 ucQueueIdx,
    IN UINT_16 u2WinMax
    );
HAL_STATUS halTxConfigACTxop(
    IN UINT_8 ucQueueIdx,
    IN UINT_16 u2Txop
    );


extern VOID
__original_halSeTbttInt (
    UINT_8 eTsfId,
    UINT_8 fgEnable
    );

extern VOID
(*halSeTbttInt) (
    UINT_8 eTsfId,
    UINT_8 fgEnable
    ) ;

extern VOID
__original___direct_access_halSeTbttInt (
    UINT_8 eTsfId,
    UINT_8 fgEnable
    );

extern VOID
(*__direct_access_halSeTbttInt) (
    UINT_8 eTsfId,
    UINT_8 fgEnable
    ) ;

extern HAL_STATUS
__original_halSetPreTbttIntPin(
    IN UINT_8 ucBssidIdx,
    IN BOOL fgEnable
    );
extern HAL_STATUS
(*halSetPreTbttIntPin)(
    IN UINT_8 ucBssidIdx,
    IN BOOL fgEnable
    );
extern HAL_STATUS
__original___direct_access_halSetPreTbttIntPin(
    IN UINT_8 ucBssidIdx,
    IN BOOL fgEnable
    );
extern HAL_STATUS
(*__direct_access_halSetPreTbttIntPin)(
    IN UINT_8 ucBssidIdx,
    IN BOOL fgEnable
    ) ;

#endif

/* Copyright Statement:
 *
 */

/*
** $Log: hal_Sec.h $
**
** 01 12 2015 leo.hung
** [DVT][Crypto]
** 1. Update crypto kery from efuse KeK and usecret.
**
** 01 08 2015 leo.hung
** [DVT][Crypto]
** 1. Add key source from efuse.
**
** 12 19 2014 leo.hung
** [DVT][Crypto]
** 1. Update Crypto Ring/Double buffer control.
**
** 12 11 2014 leo.hung
** [DVT][PWM][IRDA][RTC][Crypto][WDT]
** 1. Update PWM, IRDA, RTC Crypto_AES/DES, WDT.
**
** 12 08 2014 leo.hung
** [DVT][PWM][IRDA][RTC][Crypto]
** 1. Update PWM, IRDA, RTC Crypto_AES/DES.
**
** 11 29 2014 leo.hung
** [DVT][IrRx][Crypto][RTC]
** 1. Update IrRx, Crypto, RTC.
**
**
*/

#ifndef __HAL_SEC_H__
#define __HAL_SEC_H__

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "mt7687_cm4_hw_memmap.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

#define IOT_CRYPTO_DECRYPT  (0)
#define IOT_CRYPTO_ENCRYPT  (1)

#define  IOT_CRYPTO_ECB (0)
#define  IOT_CRYPTO_CBC (1)

#define IOT_CRYPTO_KEY_EFUSE    (0)
#define IOT_CRYPTO_KEY_SW       (1)
#define IOT_CRYPTO_KEY_BANK_KEK     (1)
#define IOT_CRYPTO_KEY_BANK_USECRET (2)


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef struct _CRYPTO_KEY {
    UINT32 u4Key1;
    UINT32 u4Key2;
    UINT32 u4Key3;
    UINT32 u4Key4;
    UINT32 u4Key5;
    UINT32 u4Key6;
    UINT32 u4Key7;
    UINT32 u4Key8;
} CRYPTO_KEY_T, *P_CRYPTO_KEY_T;

typedef struct _CRYPTO_IV {
    UINT32 u4IV1;
    UINT32 u4IV2;
    UINT32 u4IV3;
    UINT32 u4IV4;
} CRYPTO_IV_T, *P_CRYPTO_IV_T;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
enum CryptoEngineID {
    CryptoMD5 = 0,
    CryptoSHA1,
    CryptoSHA224,
    CryptoSHA256,
    CryptoSHA384,
    CryptoSHA512
};

/*
========================================================================
Routine Description:

Note:
========================================================================
*/
extern VOID halSecSetAESDESKeyBank(UINT8 ucKeyBank);
extern VOID halSecCryptoKick(void);
extern VOID halSecDMA1Config(UINT8 ucEnable, UINT16 u2LenWPPT, PUINT8 ptrAddrWPTO);
extern VOID halSecDMA2Config(UINT8 ucEnable, UINT16 u2LenWPPT, PUINT8 ptrAddrWPTO);
extern VOID halSecAESConfig(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
extern VOID halSecAES(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
extern VOID halSecDESConfig(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
extern VOID halSecDES(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
extern VOID halSecAES_DMA_Buff(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, UINT16 u2LenWPPT, PUINT8 ptrAddrWPTO, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
extern VOID halSecAES_DMA_Buff_Dest(PUINT8 ptrInputText, PUINT8 ptrOuputText, UINT32 u4DataLen, UINT16 u2LenWPPT, PUINT8 ptrAddrWPTO, CRYPTO_KEY_T cryptoKey, UINT32 u4KeyLen, UINT8 ucKeySource, UINT8 ucMode, UINT8 ucType, CRYPTO_IV_T cryptoIV);
#endif //#ifndef __HAL_SEC_H__


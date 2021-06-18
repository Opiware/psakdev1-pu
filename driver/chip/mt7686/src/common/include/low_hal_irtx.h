/* Copyright Statement:
 *
 */

/*
** $Log: hal_IrTx.h $
**
** 12 15 2014 leo.hung
** [DVT][IrDA][WDT]
** 1. Add Ir Tx busy checking.
** 2. Update Ir Tx/Rx Pulse Width mode for learning mode.
** 3. Update WDT.
**
** 12 11 2014 leo.hung
** [DVT][PWM][IRDA][RTC][Crypto][WDT]
** 1. Update PWM, IRDA, RTC Crypto_AES/DES, WDT.
**
** 12 08 2014 leo.hung
** [DVT][PWM][IRDA][RTC][Crypto]
** 1. Update PWM, IRDA, RTC Crypto_AES/DES.
**
**
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#ifndef _HAL_LOW_IRTX_H
#define _HAL_LOW_IRTX_H

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

#include "hal_platform.h"
#ifdef HAL_IRTX_MODULE_ENABLED
#include "mt7687_cm4_hw_memmap.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

#define IRTX_OPER_FREQ  (2000) // 2000KHz (fixed, always 2M)

#define IR_RC6_TOGGLE_BIT   (3)
#define IR_RC5_TOGGLE_BIT   (2)

#define IRTX_PW_DEFAULT_FREQ    (36) // KHz
#define IRTX_PW_DEFAULT_DUTY    (25) // KHz
#define IRTX_PW_NUM_MAX         (68) // 17*4


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum _ENUM_IR_PROTOCOL {
    IR_NEC = 0,
    IR_RC5,
    IR_RC6,
    IR_SWM,
    IR_SW_PULSE_WIDTH,
    IR_PROTOCOL_NUM
} ENUM_IR_PROTOCOL;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/


/*
========================================================================
Routine Description:

Note:
========================================================================
*/

extern ENUM_HAL_RET_T halIrTxInit(UINT8 ucOutputSel, UINT8 ucRegOrder, UINT8 ucBitOrder);
extern ENUM_HAL_RET_T halIrTxConfig(ENUM_IR_PROTOCOL eIrProtocol, UINT8 ucDataInvert, UINT8 ucOutputInvert,
                                    UINT32 u4L0High, UINT32 u4L0Low, UINT32 u4L1High, UINT32 u4L1Low,
                                    UINT16 u2Freq, UINT8 ucDutyCycle);
extern ENUM_HAL_RET_T halIrTxSend(UINT32 u4TxData0, UINT32 u4TxData1, UINT32 u4TxData2, UINT8 ucBitNum, UINT8 ucRepeat);
extern ENUM_HAL_RET_T halIrTxPWSend(UINT8 ucDataNum, PUINT8 pData, UINT8 ucBasePeriod);
/* extern VOID halIrTxSWMSet(UINT8 ucEnable, UINT8 ucVal); */
extern VOID halIrTxClearInterrupt(void);


#endif
#endif //_HAL_IRTX_H


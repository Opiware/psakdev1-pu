/* Copyright Statement:
 *
 */

/*
** $Log: low_hal_irrx.h $
**
**
**
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#ifndef __LOW_HAL_IRRX_H__
#define __LOW_HAL_IRRX_H__

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

#include "hal_platform.h"
#ifdef HAL_IRRX_MODULE_ENABLED
#include "mt7687_cm4_hw_memmap.h"
#include "top.h" // for gXtalFreq



/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

#define IRRX_OPER_FREQ  (2000) // 2000KHz
#define IRRX_BUS_FREQ   (top_xtal_freq_get()/1000) // KHz

#define IRRX_PWD_OK_PERIOD      (64)
#define IRRX_PWD_DATA_MAX_NUM   (68) //(17*4)
#define IRRX_PWD_DATA_MAX_VAL   (0xFF) // 8 bits

#define IRRX_RC5_DEFAULT_OK_PERIOD  (3)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum _low_hal_irrx_mode_e {
    LOW_HAL_IRRX_MODE_RC5 = 0,
    LOW_HAL_IRRX_MODE_PWD
} low_hal_irrx_mode_t;

typedef void (*low_hal_irrx_callback_t)(void  *user_data);

typedef struct {
    low_hal_irrx_callback_t func;
    void *argument;
} irrx_user_callback_t;



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
extern VOID halIrRxClearInterrupt(void);
extern VOID halIrRxRC5Read(PUINT8 pucBitNum, PUINT32 pu4DW0, PUINT32 pu4DW1);
extern VOID halIrRxPWDRead(PUINT8 pucPWNum, PUINT8 pucPWBuf, UINT8 ucBufLen);
extern VOID halIrRxReset(void);
extern ENUM_HAL_RET_T halIrRxRC5(UINT8 ucInverse, UINT8 ucBitReverse, UINT8 ucIgnoreEmpty, UINT16 u2SamplePeriod);
extern ENUM_HAL_RET_T halIrRxPulseWidthDetect(
    UINT32  u4DeGlitchCnt,
    UINT8   ucInverse,
    UINT32  u4TherminateThresholdUs,
    UINT32  *pu4DetectPrecesionUs
);
extern ENUM_HAL_RET_T halIrRxPulseWidthDetect_DVT(
    UINT32  u4DeGlitchCnt,
    UINT8   ucInverse,
    UINT32  u4OKPeriod,
    UINT32  u4SAPeriod,
    UINT32  u4ChkPeriod,
    UINT8   ucLowTerminate,
    UINT8   ucHighTerminate
);

extern ENUM_HAL_RET_T halIrRxRegisterCallback(low_hal_irrx_mode_t mode, low_hal_irrx_callback_t callback,void *parameter);

#endif

#endif //__LOW_HAL_IRRX_H__


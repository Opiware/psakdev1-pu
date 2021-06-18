/* Copyright Statement:
 *
 */

/*
** $Log: low_hal_wdt.h $
**
**
*/

#ifndef __LOW_HAL_WDT_H__
#define __LOW_HAL_WDT_H__

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
#define CM4_WDT_RESTART_KEY     (0x1971)
#define CM4_WDT_LENGTH_KEY      (0x08)
#define CM4_WDT_MODE_KEY        (0x22)
#define CM4_WDT_SWRST_KEY       (0x1209)

#define CM4_WDT_RESET_MODE      (0)
#define CM4_WDT_INTERRUPT_MODE  (1)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/


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
extern UINT32 halWDTReadInterruptStatus(void);
extern VOID halWDTRestart(void);
extern VOID halWDTSetTimeout(UINT16 u2Timeout);
extern VOID halWDTConfig(UINT8 ucIRQ, UINT8 ucExtEn, UINT8 ucExtPolarity, UINT8 ucGlobalRest);
extern VOID halWDTEnable(UINT8 ucEnable);
extern VOID halWDTSoftwareReset(void);
extern VOID halWDTDualCoreReset(void);
extern VOID halWDTDualCoreInterrupt(UINT8 ucClear);

#endif //#ifndef __LOW_HAL_WDT_H__



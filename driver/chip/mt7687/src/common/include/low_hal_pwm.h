/* Copyright Statement:
 *
 */

/*
** $Log: hal_PWM.h $
**
** 04 23 2015 morris.yeh
** [PWM]
** refine code for wake up test command
**
** 04 20 2015 morris.yeh
** [PWM]
** Add test command for wake up test
**
** 11 14 2014 leo.hung
** [DVT][PWM]
** 1. Update PWM.
**
** 11 10 2014 leo.hung
** [DVT][I2C]
** 1. Use CPU_FREQUENCY instead of hard code.
**
** 10 15 2014 pierre.chang
** Add DMA, modify makefile to add PRODUCT_VERSION....
**
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#ifndef _HAL_PWM_H
#define _HAL_PWM_H

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

#include "hal_platform.h"
#ifdef HAL_PWM_MODULE_ENABLED
#include "type_def.h"
#include "mt7687_cm4_hw_memmap.h"



/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define PWM_STAY_CYCLE_MAX  (0xFFF) // 12 bits


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
ENUM_HAL_RET_T halPWMResetAll(void);
ENUM_HAL_RET_T halPWMClockSelect(ENUM_PWM_CLK_T ePwmClk);
ENUM_HAL_RET_T halPWMEnable(UINT8 ucPwmIdx, UINT8 ucGlobalKick, UINT8 ucIOCtrl, UINT8 ucPolarity);
ENUM_HAL_RET_T halPWMDisable(UINT8 ucPwmIdx);
ENUM_HAL_RET_T halPWMKick(UINT8 ucPwmIdx);
ENUM_HAL_RET_T halPWMConfig(UINT8 ucPwmIdx, ENUM_PWM_STATE_T eState, UINT16 u2DutyCycle, UINT32 u4PwmFreq);
ENUM_HAL_RET_T halPWMStateConfig(UINT8 ucPwmIdx, UINT16 u2S0StayCycle, UINT16 u2S1StayCycle, UINT8 ucReplayMode);
ENUM_HAL_RET_T halPWMQuery(UINT8 ucPwmIdx, ENUM_PWM_STATE_T eState, UINT16 *pu2DutyCycle, UINT32 *pu4PwmFreq, UINT8 *pucEnable);
#endif  //#ifdef HAL_PWM_MODULE_ENABLED
#endif //_HAL_PWM_H


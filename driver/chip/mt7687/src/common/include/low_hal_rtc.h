/* Copyright Statement:
 *
 */

/*
** $Log: low_hal_rtc.h $
**
**
**
*/

#ifndef __LOW_HAL_RTC_H__
#define __LOW_HAL_RTC_H__

#ifdef HAL_RTC_MODULE_ENABLED
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
#define RTC_TIMER_IRQ   (IRQn_Type)(19)
#define RTC_ALARM_IRQ   (IRQn_Type)(21)

#define RTC_BACKUP_BYTE_NUM_MAX     (144)
#define RTC_SPARE_NUM_MAX      (16)

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
extern ENUM_HAL_RET_T halRTCUnlock(void);
extern ENUM_HAL_RET_T halRTCInit(void);
extern ENUM_HAL_RET_T halRTCDeInit(void);

extern ENUM_HAL_RET_T halRTCSetTime(
    UINT8 ucYear,
    UINT8 ucMonth,
    UINT8 ucDayofMonth,
    UINT8 ucDayofWeek,
    UINT8 ucHour,
    UINT8 ucMinute,
    UINT8 ucSecond
);

extern ENUM_HAL_RET_T halRTCGetTime(
    PUINT8 pucYear,
    PUINT8 pucMonth,
    PUINT8 pucDayofMonth,
    PUINT8 pucDayofWeek,
    PUINT8 pucHour,
    PUINT8 pucMinute,
    PUINT8 pucSecond
);

extern ENUM_HAL_RET_T halRTCSetAlarm(
    UINT8 ucYear,
    UINT8 ucMonth,
    UINT8 ucDayofMonth,
    UINT8 ucDayofWeek,
    UINT8 ucHour,
    UINT8 ucMinute,
    UINT8 ucSecond,
    UINT8 ucEnableMask
);

extern ENUM_HAL_RET_T halRTCGetAlarm(
    PUINT8 pucYear,
    PUINT8 pucMonth,
    PUINT8 pucDayofMonth,
    PUINT8 pucDayofWeek,
    PUINT8 pucHour,
    PUINT8 pucMinute,
    PUINT8 pucSecond
);

extern ENUM_HAL_RET_T halRTCEnableAlarm(UINT8 ucEnable);

extern ENUM_HAL_RET_T halRTCEnterMode(void);


extern ENUM_HAL_RET_T halRTCSetBackup(UINT16 addr, const INT8 *buf, UINT16 len);
extern ENUM_HAL_RET_T halRTCClearBackup(UINT16 addr, UINT16 len);
extern ENUM_HAL_RET_T halRTCGetBackup(UINT16 addr, INT8 *buf, UINT16 len);

#endif /* HAL_RTC_MODULE_ENABLED */

#endif //#ifndef __LOW_HAL_RTC_H__


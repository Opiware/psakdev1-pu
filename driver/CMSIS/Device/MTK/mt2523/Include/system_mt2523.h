/* Copyright Statement:
 *
 */

#ifndef __SYSTEM_MT2523_H
#define __SYSTEM_MT2523_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;      /*!< System Clock Frequency (Core Clock) */


extern void SystemInit(void);

extern void SystemCoreClockUpdate(void);

extern void SysInitStatus_Set(void);

extern uint32_t SysInitStatus_Query(void);

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_MT2523_H */

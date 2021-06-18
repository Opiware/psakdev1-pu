/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    gpt_sw.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file is intends for GPT driver.
 *
 * Author:
 * -------
 *  James Liu
 *
 ****************************************************************************/
#ifndef GPT_SW_H
#define GPT_SW_H

#include "hal_gpt.h"
#include "top.h"

#ifdef HAL_GPT_MODULE_ENABLED

#include <stdbool.h>

//GPT address
#define GPT_ISR            (CM4_GPT_BASE+0x00)
#define GPT_IER            (CM4_GPT_BASE+0x04)
#define GPT0_CTRL          (CM4_GPT_BASE+0x10)
#define GPT0_ICNT          (CM4_GPT_BASE+0x14)
#define GPT1_CTRL          (CM4_GPT_BASE+0x20)
#define GPT1_ICNT          (CM4_GPT_BASE+0x24)
#define GPT2_CTRL          (CM4_GPT_BASE+0x30)
#define GPT2_CNT           (CM4_GPT_BASE+0x34)
#define GPT0_CNT           (CM4_GPT_BASE+0x40)
#define GPT1_CNT           (CM4_GPT_BASE+0x44)

#define GPT3_CTRL          (CM4_GPT_BASE+0x50)
#define GPT3_INIT          (CM4_GPT_BASE+0x54)
#define GPT3_CNT           (CM4_GPT_BASE+0x58)
#define GPT3_EXPIRE        (CM4_GPT_BASE+0x5C)

#define GPT4_CTRL          (CM4_GPT_BASE+0x60)
#define GPT4_INIT          (CM4_GPT_BASE+0x64)
#define GPT4_CNT           (CM4_GPT_BASE+0x68)

//GPT_ISR
#define GPT0_INT                (0x01)
#define GPT1_INT                (0x02)

//GPT_IER
#define GPT0_INT_EN             (0x01)
#define GPT1_INT_EN             (0x02)

//GPT_CTRL
#define GPT_CTRL_EN             (0x01)
#define GPT_CTRL_AUTOMODE       (0x02)

//GPT3
#define GPT3_OSC_CNT_1US_SHIFT	(16)
#define GPT3_OSC_CNT_1US_MASK	(0x3F)

typedef struct {
    void (*gpt0_func)(void);
    void (*gpt1_func)(void);
    void (*gpt3_func)(void);
} gpt_func;


typedef struct {
    gpt_func       GPT_FUNC;
} GPTStruct;


extern void GPT_ResetTimer(kal_uint32 timerNum, kal_uint32 countValue, bool autoRepeat);
extern void GPT_Start(kal_uint32 timerNum);
extern void GPT_Stop(kal_uint32 timerNum);
extern void GPT_init(kal_uint32 timerNum, kal_uint32 speed_32us, void (*GPT_Callback)(void));
extern void GPT_LISR(void);
extern kal_uint32 GPT_return_current_count(kal_uint32 timerNum);

extern void CM4_GPT2Init(void);
extern void CM4_GPT4Init(void);

#endif

#endif  /* GPT_SW_H */

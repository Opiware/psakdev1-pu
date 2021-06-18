/* Copyright Statement:
 *
 */
#ifndef __SCT_KEYPAD_H__
#define __SCT_KEYPAD_H__

#ifdef MTK_KEYPAD_ENABLE
#include "hal_keypad.h"
#include "hal_keypad_internal.h"
#include "hal_eint.h"
#include "mt2523.h"


#ifdef __cplusplus
extern "C"
{
#endif


/********* varible extern *************/
extern uint32_t sct_keypad_driven_signal_time;

/******** funtion extern **************/
bool sct_keypad_init(void);

#ifdef __cplusplus
}
#endif

#endif /*MTK_KEYPAD_ENABLE*/

#endif /* __SCT_KEYPAD_H__ */


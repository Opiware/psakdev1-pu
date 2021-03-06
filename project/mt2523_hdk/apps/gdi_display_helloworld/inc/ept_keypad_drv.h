/*
 */

/*****************************************************************************
*
* Filename:
* ---------
*    ***.*
*
* Project:
* --------
*
* Description:
* ------------
*
* Author:
* -------
*
*============================================================================
****************************************************************************/
#ifndef  _EPT_KEYPAD_DRV_H
#define  _EPT_KEYPAD_DRV_H


#define  __DOUBLE_KEYPAD__

#if defined(__SINGLE_KEYPAD__)
#define KEYPAD_MAPPING \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE
#elif defined(__DOUBLE_KEYPAD__)
#define KEYPAD_MAPPING \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_ENTER, \
DEVICE_KEY_BACK, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_UP, \
DEVICE_KEY_DOWN, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE, \
DEVICE_KEY_NONE
#endif

#define POWERKEY_POSITION DEVICE_KEY_POWER

#define DRV_KBD_COL_ROW_SEL 0x0

#endif /* _EPT_KEYPAD_DRV_H */



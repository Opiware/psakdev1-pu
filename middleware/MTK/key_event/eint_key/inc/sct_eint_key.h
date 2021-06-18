/* Copyright Statement:
 *
 */
#ifndef __SCT_EINT_KEY_H__
#define __SCT_EINT_KEY_H__

#ifdef MTK_EINT_KEY_ENABLE
#include "eint_key.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    bsp_eint_key_event_t state;
    uint8_t  key_data;
    uint32_t time_stamp;
    bool     is_update;
} sct_eint_key_event_t;


/********* varible extern *************/
extern sct_eint_key_event_t sct_eint_key_event;;

/******** funtion extern **************/
bool sct_eint_key_init(void);

#ifdef __cplusplus
}
#endif

#endif /*MTK_EINT_KEY_ENABLE*/

#endif /* __SCT_KEYPAD_H__ */


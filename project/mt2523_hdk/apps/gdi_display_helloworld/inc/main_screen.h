/* Copyright Statement:
 *
 */



#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

typedef enum{
    MESSAGE_ID_TEST_EVENT
} message_id_enum;

#define GRAPHICLOG(fmt, args...)       LOG_I(GRAPHIC_TAG, "[GRAPHIC]"fmt, ##args)

extern void main_screen_init(void);

extern void main_screen_show(void);

extern void common_event_handler(message_id_enum event_id, int32_t param1, void* param2);

#endif


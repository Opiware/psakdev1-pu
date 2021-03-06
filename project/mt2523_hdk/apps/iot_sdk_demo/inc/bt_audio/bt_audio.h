/* Copyright Statement:
 *
 */

#ifndef __BT_AUDIO_H__
#define __BT_AUDIO_H__

#include "stdio.h"

#include "stdbool.h"
#include "gdi_font_engine.h"
#include "gdi.h"
#include "main_screen.h"
#include "bt_type.h"
#include "bt_sink_srv.h"
#include <syslog.h>
#include <math.h>
#include "mt25x3_hdk_lcd.h"


#define BT_AUDIO_ITEM_H             (35)
#define BT_AUDIO_ITEM_W             (120)

#define BT_AUDIO_TITLE_X            (0)
#define BT_AUDIO_TITLE_Y            (0)

#define BT_AUDIO_CONNECT_X          (70)
#define BT_AUDIO_CONNECT_Y          (100)

#define BT_AUDIO_HOME_X             (200)
#define BT_AUDIO_HOME_Y             (220)

#define BT_AUDIO_MUSIC_X            (65)
#define BT_AUDIO_MUSIC_Y            (60)

#define BT_AUDIO_CALL_X             (65)
#define BT_AUDIO_CALL_Y             (50)

#define BT_AUDIO_CALL_GAP           (25)

#define BT_AUDIO_CALL_DROP_X        (70)
#define BT_AUDIO_CALL_DROP_Y        (100)

#define BT_AUDIO_PXP_STATUS_X       (0)
#define BT_AUDIO_PXP_STATUS_Y       (30)

#define BT_AUDIO_MAX_NUM_LEN        (45)
#define BT_AUDIO_MAX_NAME_LEN       (45)

#define STR_BT_AUDIO_TITLE             ( "BT Audio")
#define STR_BT_AUDIO_HOME              ( "Exit")
#define STR_BT_AUDIO_CONN              ( "Connecting")
#define STR_BT_AUDIO_RECONN            ( "1.  Reconnect")
#define STR_BT_AUDIO_STOP              ( "1.  Stop music")
#define STR_BT_AUDIO_PLAY              ( "1.  Play music")
#define STR_BT_AUDIO_NEXT              ( "2.  Next")
#define STR_BT_AUDIO_PRE               ( "3.  Previous")
#define STR_BT_AUDIO_INCOMING          ( "Incoming call")
#define STR_BT_AUDIO_ANSWER            ( "1.  Answer")
#define STR_BT_AUDIO_REJECT            ( "2.  Reject")
#define STR_BT_AUDIO_DROP              ( "1.  Hang up")
#define STR_BT_AUDIO_SWITCH_PATH       ( "2.  Switch audio")
#define STR_BT_AUDIO_PXP_IDLE          ("BLE PXP [Unconnected]")
#define STR_BT_AUDIO_PXP_CONNECTED     ("BLE PXP [Connected]")
#define STR_BT_AUDIO_PXP_ALERT         ("BLE PXP [Out of range]")


#define BT_AUDIO_LCD_SIZE_240_240           (0)

#define BT_AUDIO_LCD_SIZE_320_320           (1)

typedef enum {
    BT_AUDIO_SCR_IDLE,
    BT_AUDIO_SCR_PLAYING,
    BT_AUDIO_SCR_STOP,
    BT_AUDIO_SCR_INCOMING,
    BT_AUDIO_SCR_CALLING,

    BT_AUDIO_SCR_TOAL
} bt_audio_screen_t;

typedef struct {
    uint8_t num[BT_AUDIO_MAX_NUM_LEN + 1];
    uint8_t name[BT_AUDIO_MAX_NAME_LEN + 1];
    uint8_t num_len;
    uint8_t name_len;
} bt_audio_caller_t;

typedef struct {
    int16_t x;
    int16_t y;
} bt_audio_point_t;

typedef struct {
    bool entered;
    gdi_color_t bg_color;
    gdi_font_engine_color_t font_color;
    gdi_font_engine_size_t font;
    bt_audio_screen_t scr;
    bt_sink_srv_event_t          pxp_status;
    bt_audio_screen_t bg_screen;
    bt_sink_srv_profile_type_t   profile_type;
    bt_bd_addr_t                 reconnect_addr;
    bt_audio_caller_t            caller;
    uint8_t lcd_size;
} bt_audio_context_t;

void show_bt_audio_screen(void);

void bt_audio_event_handler(message_id_enum event_id, int32_t param1, void *param2);

bool bt_audio_is_point_range(bt_audio_point_t *point, bt_audio_point_t *l_corner,
                             bt_audio_point_t *r_corner);

void bt_audio_font_engine_show_string(int32_t x, int32_t y, uint8_t *string,
                                      int32_t len, gdi_font_engine_color_t font_color);

void bt_audio_gdi_draw_solid_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                                  gdi_color_t rect_color);

gdi_result_t bt_audio_gdi_lcd_update_screen(uint32_t x1, uint32_t y1,
    uint32_t x2, uint32_t y2);

#endif /* __BT_AUDIO_H__ */


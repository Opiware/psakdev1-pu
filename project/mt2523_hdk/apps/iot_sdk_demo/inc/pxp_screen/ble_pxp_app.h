/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * This file implements PXP app main function
 *
 ****************************************************************************/
#ifndef __BLE_PXP_APP_H__
#define __BLE_PXP_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stdbool.h"
#include "gdi_font_engine.h"
#include "gdi.h"

#include "main_screen.h"

typedef struct {
    int32_t title_x;
    int32_t title_y;
    int32_t content_x;
    int32_t content_y;
    int32_t back_x1;
    int32_t back_y1;
    int32_t back_x2;
    int32_t back_y2;
    gdi_color_t bg_color;
    gdi_font_engine_color_t font_color;
    gdi_font_engine_size_t font;
} ble_pxp_screen_cntx;

typedef enum {
    BLE_PXP_SHOW_DISCONNECT,
    BLE_PXP_SHOW_CONNECT,
    BLE_PXP_SHOW_ALERT
} ble_pxp_show_type_t;


void ble_pxp_show_screen(ble_pxp_show_type_t type);

void ble_pxp_show_unconnected_screen(void);

void ble_pxp_screen_event_handler(message_id_enum event_id, int32_t param1,
    void *param2);

void ble_pxp_font_engine_show_string(int32_t x, int32_t y, uint8_t *string,
    int32_t len, gdi_font_engine_color_t font_color,
    gdi_font_engine_size_t font_size);

#ifdef __cplusplus
}
#endif

#endif /*__BLE_PXP_APP_H__*/


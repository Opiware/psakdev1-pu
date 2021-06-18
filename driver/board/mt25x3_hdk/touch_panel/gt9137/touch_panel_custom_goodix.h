/* Copyright Statement:
 *
 */

#ifndef _TOUCH_PANEL_CUSTOM_GOODIX_H_
#define _TOUCH_PANEL_CUSTOM_GOODIX_H_

#ifdef MTK_CTP_ENABLE

#include "ctp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define GOODIX_LCD_WIDTH                   (240)
#define GOODIX_LCD_HEIGHT                  (240)

/*software definition size*/
#define CTP_GOODIX_COORD_X_START           (0)
#define CTP_GOODIX_COORD_X_END             (GOODIX_LCD_WIDTH - 1)
#define CTP_GOODIX_COORD_Y_START           (0)
#define CTP_GOODIX_COORD_Y_END             (GOODIX_LCD_HEIGHT - 1)

/*calibration parameter, provide by vendor*/
#define CTP_GOODIX_COORD_VENDOR_X_START    (0)
#define CTP_GOODIX_COORD_VENDOR_X_END      (GOODIX_LCD_WIDTH - 1)
#define CTP_GOODIX_COORD_VENDOR_Y_START    (0)
#define CTP_GOODIX_COORD_VENDOR_Y_END      (GOODIX_LCD_HEIGHT -1)


#define GOODIX_CTP_CONFIG_LENGTH           106

#define GOODIX_PEN_MOVE_OFFSET             8
#define GOODIX_PEN_LONGTAP_OFFSET          10

/********* varible extern *************/


/******** funtion extern **************/
extern void touch_panel_goodix_custom_data_init(void);

#ifdef __cplusplus
}
#endif

#endif /*MTK_CTP_ENABLE*/

#endif /*_TOUCH_PANEL_CUSTOM_GOODIX_H_*/


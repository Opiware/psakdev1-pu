/* Copyright Statement:
 *
 */

#ifndef __TOUCH_PANEL_CUSTOM_ITE_H__
#define __TOUCH_PANEL_CUSTOM_ITE_H__

#ifdef MTK_CTP_ENABLE

#include "ctp.h"
#include "hal_eint.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*resolution ratio configuration */
#define ITE_LCD_WIDTH                   (320)
#define ITE_LCD_HEIGHT                  (320)

/*software definition size*/
#define CTP_ITE_COORD_X_START           (0)
#define CTP_ITE_COORD_X_END             (ITE_LCD_WIDTH - 1)
#define CTP_ITE_COORD_Y_START           (0)
#define CTP_ITE_COORD_Y_END             (ITE_LCD_HEIGHT - 1)

/*calibration parameter, provide by vendor*/
#define CTP_ITE_COORD_VENDOR_X_START    (0)
#define CTP_ITE_COORD_VENDOR_X_END      (ITE_LCD_WIDTH - 1)
#define CTP_ITE_COORD_VENDOR_Y_START    (0)
#define CTP_ITE_COORD_VENDOR_Y_END      (ITE_LCD_HEIGHT - 1)


#define ITE_PEN_MOVE_OFFSET             8
#define ITE_PEN_LONGTAP_OFFSET          10

/*enable ctp atuomatic update firmware*/
#define CTP_ITE_UPGRADE_FIRMWARE

/*eint trriger definition*/
#define ITE_EINT_TRIGGER_LEVEL_LOW      HAL_EINT_LEVEL_LOW
#define ITE_EINT_TRIGGER_LEVEL_HIGH     HAL_EINT_LEVEL_HIGH

#define CTP_ITE_EINT_TRIGGER_TYPE       HAL_EINT_LEVEL_LOW
/********* varible extern *************/

/******** funtion extern **************/
extern void touch_panel_ite_custom_data_init(void);

#ifdef __cplusplus
}
#endif

#endif /*MTK_CTP_ENABLE*/

#endif /*__TOUCH_PANEL_CUSTOM_ITE_H__*/


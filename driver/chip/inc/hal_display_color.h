/* Copyright Statement:
 *
 */

#ifndef __HAL_DISPLAY_COLOR_H__
#define __HAL_DISPLAY_COLOR_H__

#include "hal_platform.h"

#ifdef HAL_DISPLAY_COLOR_MODULE_ENABLED
/**
 * @addtogroup HAL
 * @{
 * @addtogroup DISPLAY_COLOR
 * @{
 * This section introduces the display color APIs including terms and acronyms,
 * supported features, software architecture, details on how to use this driver, display color function groups, all enumerations, structures and functions.
 *
 * @section DISPLAY_COLOR_Terms_Chapter Terms and acronyms
 *
 * |Terms                         |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b Cb                         | Blue chrominance in YCbCr color space.
 * |\b Cr                         | Red chrominance in YCbCr color space.
 *
 * @section DISPLAY_COLOR_Features_Chapter Supported features
 *
 * - \b Support \b sharpness \b enhancement. \n
 *   It enhances the edge contrast of an image to improve the sharpness.
 *   The improved sharpness enhances the curve, as shown below:
 *  @image html hal_display_color_sharpness.png
 * - \b Support \b contrast \b enhancement. \n
 *   It adjusts the luminance curve to improve the details on dark or bright spots of an image.
 *   The contrast enhancement curve is shown below:
 *  @image html hal_display_color_contrast.png
 * - \b Support \b saturation \b enhancement. \n
 *   Apply ( Cb^2 + Cr^2 ) to look up the table of saturation gain.
 *   The saturation enhancement curve is shown below:
 *  @image html hal_display_color_saturation_1.png
 *  @image html hal_display_color_saturation_2.png
 *
 * @section DISPLAY_COLOR_Driver_Usage_Chapter How to use this driver
 *  - Step 1. Call #hal_display_color_init() to initialize the color hardware and set to default scenario.
 *  - Step 2. Call configuration function to change detail settings if necessary.
 *  - Step 3. Call #hal_display_color_apply_color() to make the changes effective.
 *  - sample code:
 *  @code
 *
 *  hal_display_color_status_t ret = HAL_DISPLAY_COLOR_STATUS_OK;
 *  uint32_t width;
 *  // LCM function table
 *  extern LCD_Func *MainLCD;
 *
 *  ret = hal_display_color_init();
 *  if (HAL_DISPLAY_COLOR_STATUS_OK != ret) {
 *      // Error handling
 *  }
 *
 *  // Set the display color engine parameters.
 *  ret = hal_display_color_set_sharpness(&sharpness);
 *  if (HAL_DISPLAY_COLOR_STATUS_OK != ret) {
 *      // Error handling
 *  }
 *
 *  // Get width
 *  MainLCD->IOCTRL(LCM_IOCTRL_QUERY__LCM_WIDTH, &width);
 *
 *  // Update the screen.
 *  ret = hal_display_color_apply_color(width);
 *  if (HAL_DISPLAY_COLOR_STATUS_OK != ret) {
 *      // Error handling
 *  }
 *  MainLCD->BlockWrite(startx, starty, endx, endy);
 *
 *  @endcode
 *
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup hal_display_color_enum Enum
  * @{
  */

/** @brief The return status of display color API. */
typedef enum {
    HAL_DISPLAY_COLOR_STATUS_INITIALIZATION_FAILED = -3,        /**< Initialization has failed. */
    HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER = -2,            /**< Invalid parameter. */
    HAL_DISPLAY_COLOR_STATUS_POWER_FAILED = -1,                 /**< The color engine power configuration has failed. */
    HAL_DISPLAY_COLOR_STATUS_OK = 0,                            /**< Successful. */
} hal_display_color_status_t;

/** @brief The display color mode options. */
typedef enum {
    HAL_DISPLAY_COLOR_MODE_DEFAULT = 0,         /**< Default mode. */
    HAL_DISPLAY_COLOR_MODE_CAMERA,              /**< Camera mode. */
    HAL_DISPLAY_COLOR_MODE_NUM                  /**< The number of color modes. */
} hal_display_color_mode_t;

/**
  * @}
  */

/** @defgroup hal_display_color_struct Struct
  * @{
  */

/** @brief The display color customization. */
typedef struct {
    uint8_t  sharpness;                 /**< Sharpness index. */
    uint8_t  contrast;                  /**< Contrast index. */
    uint8_t  saturation;                /**< Saturation index. */
} hal_display_color_custom_table_t;

/** @brief The display color sharpness setting. */
typedef struct {
    uint8_t  gain;                      /**< The gain of sharpness enhancement. */
    uint8_t  soft_ratio;                 /**< The soft ratio of sharpness enhancement. */
    uint8_t  limit;                     /**< The limit of sharpness enhancement. */
    uint8_t  bound;                     /**< The bound of sharpness enhancement. */
} hal_display_color_sharpness_t;

/** @brief The display color contrast setting. */
typedef struct {
    uint8_t  point0;                    /**< The control point 0 for contrast enhancement. */
    uint8_t  point1;                    /**< The control point 1 for contrast enhancement. */
    uint8_t  gain0;                     /**< The gain of segment 0 of contrast enhancement. */
    uint8_t  gain1;                     /**< The gain of segment 1 of contrast enhancement. */
    uint8_t  gain2;                     /**< The gain of segment 2 of contrast enhancement. */
} hal_display_color_contrast_t;

/** @brief The display color saturation setting. */
typedef struct {
    uint16_t  ctrl_point;                 /**< Control point for saturation enhancement. */
    uint8_t   coef_a;                    /**< Coefficient A for saturation enhancement. */
    uint8_t   gain;                     /**< The gain for saturation enhancement. */
} hal_display_color_saturation_t;

/** @brief The color parameters. */
typedef struct {
    hal_display_color_mode_t        mode;          /**< Mode setting. */
    hal_display_color_sharpness_t   sharpness;        /**< Sharpness. */
    hal_display_color_contrast_t    contrast;         /**< Contrast. */
    hal_display_color_saturation_t  saturation;       /**< Saturation. */
    uint8_t                         bypass_config;           /**< Bypass the display color engine. */
} hal_display_color_parameter_t;

/**
  * @}
  */

/**
 * @brief This function initializes the display color settings. It sets the current mode to default and disables bypass color engine.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INITIALIZATION_FAILED, failed to set the default values. */
hal_display_color_status_t hal_display_color_init(void);

/**
 * @brief This function enables or disables the color engine. It sets the bypass configuration in #hal_display_color_parameter_t.
 *
 * @param[in] enable specifies if the color engine is enabled or not.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_POWER_FAILED, the operation has failed due to the power of the color engine is not turned on. */
hal_display_color_status_t hal_display_color_set_color_engine(bool enable);

/**
 * @brief This function gets the color engine status (disable or enable), it then returns the bypass configuration status in the parameter "enable".
 *
 * @param[out] enable specifies the current enable status.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_POWER_FAILED, the operation has failed due to the power of the color engine is not turned on. */
hal_display_color_status_t hal_display_color_get_color_engine(bool *enable);

/**
 * @brief This function sets the sharpness settings to color settings.
 *
 * @param[in] sharpness is the sharpness setting parameter, please refer to #hal_display_color_sharpness_t.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_set_sharpness(hal_display_color_sharpness_t *sharpness);

/**
 * @brief This function sets the contrast settings to color settings.
 *
 * @param[in] contrast is the contrast setting parameter, please refer to #hal_display_color_contrast_t.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_set_contrast(hal_display_color_contrast_t *contrast);

/**
 * @brief This function sets the saturation settings to color settings.
 *
 * @param[in] saturation is the saturation setting parameter, please refer to #hal_display_color_saturation_t.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_set_saturation(hal_display_color_saturation_t *saturation);

/**
 * @brief This function sets the bypass settings to color settings.
 *
 * @param[in] bypass specifies whether to bypass the color engine or not.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_set_bypass(bool bypass);

/**
 * @brief This function sets the color mode.
 *
 * @param[in] mode is the color mode to set.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_set_mode(hal_display_color_mode_t mode);

/**
 * @brief This function applies the color settings to color hardware engine.
 *
 * @param[in] src_width is the width of source buffer.
 *
 * @return  To indicate whether this function call is successful or not.
 *          #HAL_DISPLAY_COLOR_STATUS_OK, the operation completed successfully.
 *          #HAL_DISPLAY_COLOR_STATUS_INVALID_PARAMETER, the parameter is out of bound. */
hal_display_color_status_t hal_display_color_apply_color(uint32_t src_width);

#ifdef __cplusplus
}
#endif

/**
* @}
* @}
*/

#endif /* HAL_DISPLAY_COLOR_MODULE_ENABLED */
#endif /* __HAL_DISPLAY_COLOR_H__ */

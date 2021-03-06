/* Copyright Statement:
 *
 */

#ifndef __idp_define_h__
#define __idp_define_h__

//#include "drv_features_mmsysmisc.h"

//#define IDP_DVT_LOAD
#define IDP_MAUI_LOAD

#if defined(IDP_DVT_LOAD)
/*****************************************************************************
 * DVT load, such as IVP load
 ****************************************************************************/

/* DVT load */
#include <typedefs.h>

#define DRV_IDP_6238_SERIES
#define IDP_FAKE_KAL_SUPPORT
#define ENABLE_UT 1

#elif defined(IDP_MAUI_LOAD)
/*****************************************************************************
 * MAUI load
 ****************************************************************************/
/* MAUI load */

#if (defined(ISP_SUPPORT) && defined(DRV_ISP_6238_SERIES))
//#define IDP_CHECK_ISP_CRZ_SIZE_IS_MATCH  //CM mark 20101113 ISP not support 
#endif // #if (defined(ISP_SUPPORT) && defined(DRV_ISP_6238_SERIES))

#define IDP_VP7_MIDDLE_BUFFER_WIDTH  (480)
#define IDP_VP7_MIDDLE_BUFFER_HEIGHT (320)
//#define IDP_VIDEO_DECODE_ENLARGE_FOR_TV

//#define IDP_DRVPDN_SUPPORT
#define IDP_FAKE_KAL_SUPPORT

#if !defined(MED_NOT_PRESENT)
//#define IDP_HISR_SUPPORT
#endif

#define IDP_FULL_ISR_SUPPORT

//#define ENABLE_LOGGING_FOR_IS_BUSY
//#define ENABLE_VIDEO_DECODE_WAIT_SECOND_PATH_DONE
/**
 *  \def IDP_HW_BUG_MDP_DC_LCD_HANG
 *  This macro is defined to enable a SW work-around for a potential HW bug in MT6238 series MDP LCD direct couple mode 
 *  From past CRs, we found a case that MDP is busy sending pixels to LCD but LCD is not busy transferring pixel data to LCM...
 *  If this happens for consecutive 10 frames, we try to reset MDP HW...
 *  10 is a magical number... */
#define IDP_HW_BUG_MDP_DC_LCD_HANG
#define IDP_DC_LCD_HANG_RESET_LCD
#define IDP_RESET_MDP_LCD_WHEN_MDP_DC_LCD_HUNG

//#define IDP_ENABLE_BUS_MONITOR
#define ENABLE_UT 0

#if defined(__MTK_TARGET__)
#define IDP_USE_CLKG_DEFINE
#endif

// For H.264 slim mode
#ifdef __CAMCORDER_PACKAGE_SLIM__
#define IDP_H264_SLIM_MODE
#endif // #ifdef __CAMCORDER_PACKAGE_SLIM__

#else
/*****************************************************************************
 * Not DVT nor MAUI load
 ****************************************************************************/
#error "Plz define IDP_DVT_LOAD or IDP_MAUI_LOAD!"
#endif

#include <drv_features_mdp.h>
#include <cam_sw_types.h>

#if defined(IDP_FULL_KAL_SUPPORT)
#include <kal_general_types.h>
#include <kal_release.h>
#include "IntrCtrl.h"
#elif defined(IDP_FAKE_KAL_SUPPORT)
#include <idp_fake_kal.h>
#else
#error
#endif

#if defined(IDP_DRVPDN_SUPPORT)
#include <drvpdn.h>
#endif // #if defined(IDP_DRVPDN_SUPPORT)

#if defined(DRV_FEATURE__MM_POWER_CTRL_IF)
#include "mm_power_ctrl.h"
#endif // #if defined(DRV_FEATURE__MM_POWER_CTRL_IF)

#endif // #ifndef __idp_define_h__


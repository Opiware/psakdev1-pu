/* Copyright Statement:
 *
 */

#ifndef __img_common_enum_h__
#define __img_common_enum_h__

/****************************************************************************
 * type definitions
 ****************************************************************************/
enum img_rot_angle_enum_t
{
   /* must exactly mapped to MM_IMAGE_ROTATE_ENUM in mm_comm_def.h. 
      Otherwise, the callback functions should convert the rotation angle argument */   
    IMG_ROT_ANGLE_0   /**< clock-wise 0 degree. */
  , IMG_ROT_ANGLE_90  /**< clock-wise 90 degree. */
  , IMG_ROT_ANGLE_180 /**< clock-wise 180 degree. */
  , IMG_ROT_ANGLE_270 /**< clock-wise 270 degree. */
  , IMG_MIRROR_ROT_ANGLE_0
  , IMG_MIRROR_ROT_ANGLE_90   /**< clock-wise */
  , IMG_MIRROR_ROT_ANGLE_180  /**< clock-wise */
  , IMG_MIRROR_ROT_ANGLE_270  /**< clock-wise */
};
typedef enum img_rot_angle_enum_t img_rot_angle_enum_t;

#if 0
enum img_color_fmt_enum_t
{
    IMG_CLR_FMT_RGB_GROUP_BEGIN = 1
  , IMG_CLR_FMT_RGB565 = IMG_CLR_FMT_RGB_GROUP_BEGIN  
  , IMG_CLR_FMT_BGR565                                  /**< ?? */
  , IMG_CLR_FMT_RGB888                                  /**< R in MSB */
  , IMG_CLR_FMT_BGR888                                  /**< R in LSB */
  , IMG_CLR_FMT_ARGB8888                                /**< R in MSB */
  , IMG_CLR_FMT_ABGR8888                                /**< R in LSB */
  , IMG_CLR_FMT_YUV444                                  /**< Y1:1, U1:1, V1:1 */
  , IMG_CLR_FMT_YUV422                                  /**< Y2:2, U2:1, V2:1 */
  , IMG_CLR_FMT_YUV420                                  /**< Y2:2, U2:1 ?? */
  , IMG_CLR_FMT_YUV411                                  /**< Y2:2, U1:1, V1:1 */
  , IMG_CLR_FMT_YUV400                                  /**< Y only (grey-level) */
  , IMG_CLR_FMT_PACKET_YUYV422                          /**< packed YUYV422 */
  , IMG_CLR_FMT_YUV_GROUP_END = IMG_CLR_FMT_PACKET_YUYV422
};
typedef enum img_color_fmt_enum_t img_color_fmt_enum_t;
#endif

enum img_color_fmt_rgb_enum_t
{
  /* img_color_fmt_rgb_enum_t and img_color_fmt_yuv_enum_t are expected to phase out.
     Use MM_IMAGE_COLOR_FORMAT_ENUM instead. */
    IMG_COLOR_FMT_RGB_GROUP_BEGIN = 1
  , IMG_COLOR_FMT_RGB565 = IMG_COLOR_FMT_RGB_GROUP_BEGIN  
  , IMG_COLOR_FMT_BGR565                                  /**< ?? */
  , IMG_COLOR_FMT_RGB888                                  /**< R in MSB */
  , IMG_COLOR_FMT_BGR888                                  /**< R in LSB */
  , IMG_COLOR_FMT_ARGB8888                                /**< R in MSB */
  , IMG_COLOR_FMT_ABGR8888                                /**< R in LSB */
  , IMG_COLOR_FMT_BGRA8888                                //DRV_IDP_MT6276E2_SERIES  
  , IMG_COLOR_FMT_RGBA8888                                //DRV_IDP_MT6276E2_SERIES
  , IMG_COLOR_FMT_RGB_GROUP_END = IMG_COLOR_FMT_RGBA8888
};

typedef enum img_color_fmt_rgb_enum_t img_color_fmt_rgb_enum_t;

enum img_color_fmt_yuv_enum_t
{
  /* img_color_fmt_rgb_enum_t and img_color_fmt_yuv_enum_t are expected to phase out.
     Use MM_IMAGE_COLOR_FORMAT_ENUM instead. */
    IMG_COLOR_FMT_YUV_GROUP_BEGIN = IMG_COLOR_FMT_RGB_GROUP_END + 1
  , IMG_COLOR_FMT_YUV444 = IMG_COLOR_FMT_YUV_GROUP_BEGIN  /**< Y1:1, U1:1, V1:1 */
  , IMG_COLOR_FMT_YUV422                                  /**< Y2:2, U2:1, V2:1 */
  , IMG_COLOR_FMT_YUV420                                  /**< Y2:2, U2:1 ?? */
  , IMG_COLOR_FMT_YUV411                                  /**< Y2:2, U1:1, V1:1 */
  , IMG_COLOR_FMT_YUV400                                  /**< Y only (grey-level) */
  , IMG_COLOR_FMT_PACKET_YUYV422                          /**< packed YUYV422 */
  , IMG_COLOR_FMT_PACKET_YUY2
  , IMG_COLOR_FMT_PACKET_YVYU /**< Packet YUYV 422 format supported in MT6276. */  //DRV_IDP_MT6276E2_SERIES
  , IMG_COLOR_FMT_YUV_GROUP_END = IMG_COLOR_FMT_PACKET_YVYU
};
typedef enum img_color_fmt_yuv_enum_t img_color_fmt_yuv_enum_t;

enum img_palette_mode_enum_t
{
    IMG_PALETTE_MODE_1BPP
  , IMG_PALETTE_MODE_2BPP
  , IMG_PALETTE_MODE_4BPP
  , IMG_PALETTE_MODE_8BPP
};
typedef enum img_palette_mode_enum_t img_palette_mode_enum_t;

enum img_error_code_enum_t
{
    IMG_ERROR_CODE_TARGET_BUFFER_NOT_ENOUGH
  , IMG_ERROR_CODE_SRC_WIDTH_TOO_LARGE
  , IMG_ERROR_CODE_SRC_HEIGHT_TOO_LARGE
  , IMG_ERROR_CODE_TARGET_WIDTH_TOO_LARGE
  , IMG_ERROR_CODE_TARGET_HEIGHT_TOO_LARGE
};

/****************************************************************************
 * macros
 ****************************************************************************/
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_RGB565          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_BGR565          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_RGB888          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_BGR888          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_ARGB8888        (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_ABGR8888        (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_YUV444          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_YUV422          (2)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_YUV420          (2)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_YUV411          (4)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_YUV400          (1)
#define FORMAT_ALIGNED_BASE_WIDTH_IMG_COLOR_FMT_PACKET_YUYV422  (2)

#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_RGB565           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_BGR565           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_RGB888           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_BGR888           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_ARGB8888         (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_ABGR8888         (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_YUV444           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_YUV422           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_YUV420           (2)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_YUV411           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_YUV400           (1)
#define FORMAT_ALIGNED_BASE_HEIGHT_IMG_COLOR_FMT_PACKET_YUYV422   (1)

/**
 *  \def IMG_GET_FORMAT_ALIGNED_BASE_WIDTH
 *  This is a string concatination macro, color_fmt can only be img_color_fmt_rgb_enum_t
 *  or img_color_fmt_yuv_enum_t.
 *  \remark please don't pass in variable on heap or stack! */
#define IMG_GET_FORMAT_ALIGNED_BASE_WIDTH(color_fmt) \
  FORMAT_ALIGNED_BASE_WIDTH_##color_fmt

#define IMG_GET_FORMAT_ALIGNED_BASE_HEIGHT(color_fmt) \
  FORMAT_ALIGNED_BASE_HEIGHT_##color_fmt

/**
 *  \def IMG_GET_FORMAT_ALIGNED_BASE_WIDTH
 *  @parameter  w_or_h WIDTH or HEIGHT
 *  @parameter  color_fmt This is a string concatination macro, color_fmt can 
 *              only be img_color_fmt_rgb_enum_t or img_color_fmt_yuv_enum_t.
 *  @remark please don't pass in variable on heap or stack! */
#define IMG_GET_FORMAT_ALIGNED_BASE(w_or_h, color_fmt) \
  FORMAT_ALIGNED_BASE_##w_or_h##_##color_fmt

#endif // #ifndef __img_common_enum_h__


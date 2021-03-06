/* Copyright Statement:
 *
 */

#ifndef __idp_mem_mt6252_h__
#define __idp_mem_mt6252_h__

/* ==================================================================
 *                           boundry size
 * ================================================================== */

#define IDP_CAMERA_CAPTURE_TO_BARCODE_MAX_DISPLAYED_WIDTH        (320)

#define IDP_CAMERA_CAPTURE_TO_JPEG_MAX_DISPLAYED_WIDTH        (320)
#define IDP_CAMERA_CAPTURE_TO_JPEG_MAX_CAPTURED_WIDTH        (1600)

#define IDP_CAMERA_CAPTURE_TO_MEM_MAX_DST_WIDTH        (720)

#define IDP_CAMERA_PREVIEW_MAX_DISPLAYED_WIDTH        (400)

#define IDP_IMAGE_EFFECT_PIXEL_MAX_SRC_WIDTH        (720)

#define IDP_IMAGE_RESIZE_MAX_DST_WIDTH        (720)

#define IDP_JPEG_DECODE_MAX_SRC_WIDTH        (720)
#define IDP_JPEG_DECODE_MAX_DST_WIDTH        (720)

#define IDP_JPEG_ENCODE_MAX_DST_WIDTH        (2592)

#define IDP_JPEG_ENCODE_PANORAMA_RGB565_MAX_SRC_WIDTH   (0)
#define IDP_JPEG_ENCODE_PANORAMA_RGB565_MAX_SRC_HEIGHT   (0)

#define IDP_JPEG_ENCODE_PANORAMA_YUV420_MAX_SRC_WIDTH   (0)
#define IDP_JPEG_ENCODE_PANORAMA_YUV420_MAX_SRC_HEIGHT   (0)

#define IDP_JPEG_RESIZE_MAX_DST_WIDTH        (720)

#define IDP_VIDEO_DECODE_MAX_SRC_WIDTH_HEIGHT (720)
#define IDP_VIDEO_DECODE_MAX_DISPLAYED_WIDTH  (480)

#define IDP_VIDEO_EDITOR_ENCODE_MAX_SRC_WIDTH            (720)
#define IDP_VIDEO_EDITOR_ENCODE_MAX_ENCODED_WIDTH        (720)

#define IDP_VIDEO_EDITOR_DECODE_MAX_DST_WIDTH         (720)
#define IDP_VIDEO_EDITOR_DECODE_MAX_SRC_WIDTH_HEIGHT  (720)

#define IDP_VIDEO_ENCODE_MAX_DISPLAYED_WIDTH        (480)
#define IDP_VIDEO_ENCODE_MAX_DISPLAYED_HEIGHT       (480)
#define IDP_VIDEO_ENCODE_MAX_ENCODED_WIDTH          (720)
#define IDP_VIDEO_ENCODE_MAX_ENCODED_HEIGHT         (480)
#define IDP_VIDEO_ENCODE_MAX_ENCODED_WIDTH_HEIGHT   (720)

#define IDP_WEBCAM_MAX_CAPTURED_WIDTH    (720)

#define IDP_RGB2YUV_DISPLAY_WIDTH        (400)

#define IDP_VIDEO_CALL_ENCODE_MAX_ENCODED_WIDTH          (720)
#define IDP_VIDEO_CALL_ENCODE_MAX_ENCODED_HEIGHT         (480)

#define IDP_VIDEO_CALL_DECODE_MAX_SRC_WIDTH_HEIGHT       (720)
#define IDP_VIDEO_CALL_DECODE_MAX_DISPLAYED_WIDTH        (480)

/* ==================================================================
 *                    working memory line count
 * ================================================================== */
// TODO: Need to update with MT6253 values

#define IDP_IMGDMA_IRT0_FIFO_LENGTH         (8)
#define IDP_IMGDMA_IRT0_FIFO_LENGTH_FOR_VIDEO_DECODE         (8)
#define IDP_IMGDMA_IRT0_FIFO_LENGTH_FOR_VIDEO_DECODE_VP7     (8)
#define IDP_IMGDMA_IRT0_FIFO_LENGTH_FOR_VIDEO_CALL_DECODE    (8)

#define IDP_IMGDMA_IRT1_FIFO_LENGTH         (8)
#define IDP_IMGDMA_IRT1_FIFO_LENGTH_FOR_VIDEO_DECODE         (8)

#define IDP_IMGDMA_IRT2_FIFO_LENGTH         (8)
#define IDP_IMGDMA_IRT2_FIFO_LENGTH_FOR_VIDEO_DECODE_VP7     (16)
#define IDP_IMGDMA_IRT2_FIFO_LENGTH_FOR_VIDEO_ENCODE_VR5     (16)

#define IDP_IMGDMA_VIDEO_ENCODE_FIFO_LENGTH                           (8)
#define IDP_IMGDMA_VIDEO_ENCODE_FIFO_LENGTH_FOR_VIDEO_ENCODE_VR1_VR2  (8)
#define IDP_IMGDMA_VIDEO_ENCODE_FIFO_LENGTH_FOR_VIDEO_ENCODE_VR5      (8)
#define IDP_IMGDMA_VIDEO_ENCODE_FIFO_LENGTH_FOR_VIDEO_CALL_ENCODE     (8)

/* The working memory line number should be 16 rather than 8
 * (means double buffer) to capture a 300M JPEG image.
 *
 * If the internal memory size is not enough, than MMI
 * should capture a YUV420 jpeg file rather than YUV411 or
 * YUV422. */
#define IDP_IMGDMA_JPEG_FIFO_LENGTH         (16)
#define IDP_IMGDMA_JPEG_FIFO_LENGTH_FOR_JPEG_ENCODE         (8)

#define IDP_RESZ_PRZ_FIFO_LENGTH                             (4)
#define IDP_RESZ_PRZ_FIFO_LENGTH_CAPTURE_TO_JPEG             (8)
#define IDP_RESZ_PRZ_FIFO_LENGTH_VP7                         (8)
#define IDP_RESZ_PRZ_FIFO_LENGTH_FOR_VIDEO_ENCODE_VR1_VR2    (4)
#define IDP_RESZ_PRZ_FIFO_LENGTH_FOR_VIDEO_ENCODE_VR5        (6)
#define IDP_RESZ_PRZ_FIFO_LENGTH_FOR_CAMERA_CAPTURE_TO_JPEG  (8)
#define IDP_RESZ_PRZ_FIFO_LENGTH_FOR_VIDEO_CALL_DECODE       (8)

/* ==================================================================
 *                     Equation for each path
 * ================================================================== */
/* ========================= camera preview ============================ */
#define IDP_MEM_CONSUME_CAMERA_PREVIEW_EXTMEM (0)


/* ========================= camera catpure ============================ */
#define IDP_MEM_CONSUME_CAMERA_CAPTURE_TO_JPEG_EXTMEM (0)

#define IDP_MEM_CONSUME_CAMERA_CAPTURE_TO_MEM_EXTMEM (0)

/* ========================= video encode ============================ */
#define IDP_MEM_CONSUME_VIDEO_ENCODE_EXTMEM (0)


/* ========================= video call encode ============================ */
#define IDP_MEM_CONSUME_VIDEO_CALL_ENCODE_EXTMEM  (0)


/* ========================= video call decode ============================ */
#define IDP_MEM_CONSUME_VIDEO_CALL_DECODE_EXTMEM                             (0)



/* ========================= mjpg encode/decode ============================ */
#if defined(__MJPEG_DEC_SW_SUPPORT__) 
   #define IDP_MEM_CONSUME_MJPEG_DECODE_INTMEM (0)
   #define IDP_MEM_CONSUME_MJPEG_DECODE_EXTMEM (0)
   #define IDP_MEM_CONSUME_MJPEG_DECODE_YUV422V_EXTMEM (0)
#endif

#if defined(__MJPEG_ENC_SW_SUPPORT__) 
   #define IDP_MEM_CONSUME_MJPEG_ENCODE_INTMEM (0)
   #define IDP_MEM_CONSUME_MJPEG_ENCODE_EXTMEM (0)
   #define IDP_MEM_CONSUME_MJPEG_ENCODE_YUV420_EXTMEM (0)
#endif

#endif // __idp_mem_mt6252_h__




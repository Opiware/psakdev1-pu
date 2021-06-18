/* Copyright Statement:
 *
 */

#ifndef __idp_hw_common_mt6252_h__
#define __idp_hw_common_mt6252_h__

#ifndef THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL
#error "Hay~! Man~! You can not include this file directly~!"
#endif

enum idp_module_enum_t
{
    IDP_MODULE_IMGDMA_RDMA0
  , IDP_MODULE_IMGDMA_RDMA1

  , IDP_MODULE_IMGDMA_WDMA0
  , IDP_MODULE_IMGDMA_WDMA1
  , IDP_MODULE_IMGDMA_WDMA2

  , IDP_MODULE_IMGDMA_ROTDMA0 /**< The control code of the mux is put in ROT_DMA0. */
  , IDP_MODULE_IMGDMA_ROTDMA1

  , IDP_MODULE_IMGDMA_OVL
  , IDP_MODULE_IMGDMA_JPEG

  , IDP_MODULE_IMGPROC_IPP

  , IDP_MODULE_RESZ_CRZ
  , IDP_MODULE_RESZ_PRZ
  , IDP_MODULE_RESZ_DRZ

  , IDP_MODULE_MMSYS_MOUT

  , IDP_MODULE_OUTER_LCD // TODO: change outer to external
  , IDP_MODULE_OUTER_ISP // TODO: change outer to external
  , IDP_MODULE_OUTER_JPEG_ENCODER // TODO: change outer to external

  , IDP_MODULE_LAST
};
typedef enum idp_module_enum_t idp_module_enum_t;

typedef enum
{
    IDP_LCD_HW_TRIGGER_MODE_DISABLE,
    IDP_LCD_HW_TRIGGER_MODE_NO_SYNC,
    IDP_LCD_HW_TRIGGER_MODE_SYNC_N_STALL,
    IDP_LCD_HW_TRIGGER_MODE_SYNC_N_REDRAW,
    IDP_LCD_HW_TRIGGER_MODE_SYNC_N_DROP
} idp_lcd_hw_trigger_mode_t;

#endif // #ifndef __idp_hw_common_mt6252_h__


/* Copyright Statement:
 *
 */

/**
 * \defgroup idp Image data path
 * \brief This module defines image data path
 * @{ */
/**
 * \defgroup imgdma Image DMA
 * \brief This module defines image DMA.
 * @{ */
#ifndef __idp_imgdma_mt6252_h__
#define __idp_imgdma_mt6252_h__

#ifndef THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL
#error "Hay~! Man~! You can not include this file directly~!"
#endif

/*****************************************************************************
 * include directives
 *****************************************************************************/
#include <idp_define.h>
#include "idp_core.h"
#include "img_common_enum.h"
#include "idp_hw_common.h"

#if defined(DRV_IDP_6252_SERIES)

/*****************************************************************************
 * macros and compile options
 *****************************************************************************/


/*****************************************************************************
 * register definitions & macros
 *****************************************************************************/


/*****************************************************************************
 * type definitions
 *****************************************************************************/

/**
 * Init IMGDMA HW engines */
extern void idp_imgdma_init(void);

/**
 * The LISR for IMGDMA interruption */
extern void image_dma_LISR(void);

#endif // #if defined(DRV_IDP_6252_SERIES)

#endif // #ifndef __idp_imgdma_mt6252_h__
/** @} */


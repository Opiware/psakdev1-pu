/* Copyright Statement:
 *
 */

#define THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

//#include "IntrCtrl.h"

#include <mt6252/idp_hw/idp_imgdma_rotdma0.h>

/**
 * \brief Initialize the image DMA subsystem.
 *
 * \ingroup imgdma
 *
 * This functino will setup the interrupt for the image DMA
 * to level sensitive, and unmask all the interrupts for the
 * image DMA. */

#if defined(IDP_FULL_ISR_SUPPORT)
static
#endif
void idp_imgdma_LISR(void);
#if defined(__MTK_TARGET__) && defined(__DCM_WITH_COMPRESSION_MAUI_INIT__)
#pragma push
#pragma arm section code="DYNAMIC_COMP_MAUIINIT_SECTION"
#endif

void
idp_imgdma_init(void)
{
#ifndef MDP_C_MODEL

#if defined(IDP_FULL_ISR_SUPPORT)
    //NVIC_Register(ROT_DMA_IRQn, idp_imgdma_LISR);
    hal_nvic_register_isr_handler(ROT_DMA_IRQn, idp_imgdma_LISR);
    NVIC_SetPriority(ROT_DMA_IRQn, 5);
    NVIC_EnableIRQ(ROT_DMA_IRQn);
#endif

    //IRQSensitivity(IRQ_ROT_DMA_CODE, LEVEL_SENSITIVE);
    //IRQUnmask(IRQ_ROT_DMA_CODE);

#endif // #ifndef MDP_C_MODEL

    // Initial the owner structure.
    idp_imgdma_rotdma0_init();
}
#if defined(__MTK_TARGET__) && defined(__DCM_WITH_COMPRESSION_MAUI_INIT__)
#pragma arm section code
#pragma pop
#endif

#if defined(IDP_FULL_ISR_SUPPORT)
static
#endif
void
idp_imgdma_LISR(void)
{
    idp_imgdma_rotdma0_LISR();
}


kal_uint32
idp_get_imgdma_status_reg_value(void)
{
    return 0;
}

#endif // #if defined(DRV_IDP_6252_SERIES)


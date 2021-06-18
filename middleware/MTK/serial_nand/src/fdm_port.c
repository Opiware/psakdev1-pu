/* Copyright Statement:
 *
 */


#ifdef MTK_FATFS_ON_SERIAL_NAND
#include "hal_nvic.h"
#include "hal_flash.h"
#include <assert.h>
#include "hal_trng.h"

static int32_t FDM_SW_LOCK = 1; //hal layer can not use OS mutex, therefore, implement by flash driver.

void init_FDM_lock(void)
{
}

void NANDFDM_Lock(void)
{
    uint32_t savedMask;

    hal_nvic_save_and_set_interrupt_mask(&savedMask);
    if (FDM_SW_LOCK == 1) {
        FDM_SW_LOCK--;
        hal_nvic_restore_interrupt_mask(savedMask);
    } else if (FDM_SW_LOCK == 0) {
        hal_nvic_restore_interrupt_mask(savedMask);
    } else {
        hal_nvic_restore_interrupt_mask(savedMask);
        //ASSERT(0);
        assert(0);
    }
}

void NANDFDM_Unlock(void)
{
    uint32_t savedMask;

    hal_nvic_save_and_set_interrupt_mask(&savedMask);
    if (FDM_SW_LOCK == 0) {
        FDM_SW_LOCK++;
        hal_nvic_restore_interrupt_mask(savedMask);
    } else {
        hal_nvic_restore_interrupt_mask(savedMask);
        //ASSERT(0);
        assert(0);
    }
}

uint32_t NANDFDM_QueryExceptionStatus(void)
{
    return (HAL_NVIC_QUERY_EXCEPTION_NUMBER);
}

void NANDFDM_get_rand(uint32_t *rand_number)
{
    hal_trng_init();
    hal_trng_get_generated_random_number(rand_number);
}
#endif

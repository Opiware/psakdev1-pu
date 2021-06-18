/* Copyright Statement:
 *
 */

/*
** $Id: //MT7687 $
*/

/*! \file   "system_mt7687.c"
    \brief  This file provide utility functions for the driver

*/



#include <stdint.h>
#include "mt7687.h"
#include "system_mt7687.h"
#include "mt7687_cm4_hw_memmap.h"
#include "exception_mt7687.h"
#include "top.h"
#include "flash_map.h"
#include "hal_cache_hw.h"

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = CPU_FREQUENCY;

static volatile uint32_t System_Initialize_Done = 0;


/**
  * @brief  systick reload value reloaded via this function.
  *         This function can be called in init stage and system runtime.
  * @param  ticks value to be set
  * @retval 0 means successful
  */
uint32_t SysTick_Set(uint32_t ticks)
{
    uint32_t val;

    if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk) {
        return (1);    /* Reload value impossible */
    }

    val = SysTick->CTRL;                                   /* backup CTRL register */

    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk |          /* disable sys_tick */
                       SysTick_CTRL_ENABLE_Msk);

    SysTick->LOAD  = ticks - 1;                            /* set reload register */
    SysTick->VAL   = 0;                                    /* Load the SysTick Counter Value */

    SysTick->CTRL = val;                                   /* restore CTRL register */

    return (0);                                            /* Function successful */
}


/**
  * @brief System init status set function.
  *         This function can be called in init stage when system initialization is finished.
  * @param  None
  * @retval None
  */
void SysInitStatus_Set(void)
{
    System_Initialize_Done = 1;
}

/**
  * @brief System init status query function.
  *         This function is used to query system init status.
  * @param  None
  * @retval 0 means system is still under initialization.
  * @retval 1 means system initialize done.
  */
uint32_t SysInitStatus_Query(void)
{
    return System_Initialize_Done;
}

/**
  * @brief  Update SystemCoreClock variable according to PLL config.
  *         The SystemCoreClock variable stands for core clock (HCLK), which can
  *         be used to setup the SysTick timer or other use.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
    SystemCoreClock = top_mcu_freq_get();
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System. */
void SystemInit(void)
{
    /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

    /* set vector base */
    SCB->VTOR  = NVIC_RAM_VECTOR_ADDRESS;

    /* enable common faults */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk |
                  SCB_SHCSR_USGFAULTENA_Msk |
                  SCB_SHCSR_BUSFAULTENA_Msk;
}

/**
  * @brief  CACHE preinit
  *         Init CACHE to accelerate region init progress.
  * @param  None
  * @retval None
  */
void CachePreInit(void)
{
    /* CACHE disable */
    CACHE->CACHE_CON = 0x00;

    /* Flush all cache lines */
    CACHE->CACHE_OP = 0x13;

    /* Invalidate all cache lines */
    CACHE->CACHE_OP = 0x03;

    /* Set cacheable region */
    CACHE->CACHE_ENTRY_N[0] = (FLASH_BASE + CM4_CODE_BASE) | 0x100;
    CACHE->CACHE_END_ENTRY_N[0] = FLASH_BASE + CM4_CODE_BASE + CM4_CODE_LENGTH;

    CACHE->CACHE_REGION_EN = 1;

    switch (TCM_LENGTH) {
        /* 64K TCM/32K CACHE */
        case 0x00010000:
            CACHE->CACHE_CON = 0x30D;
            break;
        /* 80K TCM/16K CACHE */
        case 0x00014000:
            CACHE->CACHE_CON = 0x20D;
            break;
        /* 88K TCM/8K CACHE */
        case 0x00016000:
            CACHE->CACHE_CON = 0x10D;
            break;
        /* 96K TCM/NO CACHE */
        default:
            break;
    }
}


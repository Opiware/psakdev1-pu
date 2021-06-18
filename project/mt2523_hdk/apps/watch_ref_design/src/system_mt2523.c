/* Copyright Statement:
 *
 */

#include "mt2523.h"
#include "memory_map.h"

/* ----------------------------------------------------------------------------
   -- Core clock macros
   ---------------------------------------------------------------------------- */
#define CLK_CM4_FREQ_26M      ((uint32_t) 26000000)
#define CLK_CM4_FREQ_104M     ((uint32_t)104000000)
#define CLK_CM4_FREQ_156M     ((uint32_t)156000000)
#define CLK_CM4_FREQ_208M     ((uint32_t)208000000)

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock;

static volatile uint32_t System_Initialize_Done = 0;



/**
   * @brief systick reload value reloaded via this function.
  *         This function can be called in init stage and system runtime.
  * @param  ticks value to be set
  * @retval 0 means successful
  */
uint32_t SysTick_Set(uint32_t ticks)
{
    uint32_t val;

    /* reload value impossible */
    if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk) {
        return (1);
    }

    /* backup CTRL register */
    val = SysTick->CTRL;

    /* disable sys_tick */
    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk |
                       SysTick_CTRL_ENABLE_Msk);

    /* set reload register */
    SysTick->LOAD  = ticks - 1;
    SysTick->VAL   = 0;

    /* restore CTRL register */
    SysTick->CTRL = val;

    return (0);
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
   * @brief Update SystemCoreClock variable according to PLL config.
  *         The SystemCoreClock variable stands for core clock (HCLK), which can
  *         be used to setup the SysTick timer or other use.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
    uint8_t cm_mux_sel = (CONFIGSYS->CLK_CONDB & (0xF << 3)) >> 3;

    switch (cm_mux_sel) {
        case 0:
        case 1:
            SystemCoreClock = CLK_CM4_FREQ_26M;
            break;
        case 2:
        case 3:
        case 4:
            SystemCoreClock = CLK_CM4_FREQ_104M;
            break;
        case 5:
        case 7:
            SystemCoreClock = CLK_CM4_FREQ_208M;
            break;
        case 6:
        case 8:
            SystemCoreClock = CLK_CM4_FREQ_156M;
            break;
        default:
            SystemCoreClock = CLK_CM4_FREQ_26M;
            break;
    }

    if ((CLK_USED_EFUSE->EFUSE_CPU_104M & 0x400) &&
            (SystemCoreClock > CLK_CM4_FREQ_104M)) {
        SystemCoreClock = CLK_CM4_FREQ_104M;
    }
}

/**
  * @brief  Setup system
  *         Initialize the FPU setting, vector table location and faults enabling.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
    /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

    /* Configure the Vector Table location add offset address ------------------*/
    SCB->VTOR  = VECTBL_BASE;

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
    CACHE->CACHE_ENTRY_N[0] = RTOS_BASE | 0x100;
    CACHE->CACHE_END_ENTRY_N[0] = RTOS_BASE + RTOS_LENGTH;

    CACHE->CACHE_REGION_EN = 1;

    switch (TCM_LENGTH) {
        /* 128K TCM/32K CACHE */
        case 0x00020000:
            CACHE->CACHE_CON = 0x30D;
            break;
        /* 144K TCM/16K CACHE */
        case 0x00024000:
            CACHE->CACHE_CON = 0x20D;
            break;
        /* 152K TCM/8K CACHE */
        case 0x00026000:
            CACHE->CACHE_CON = 0x10D;
            break;
        /* 160K TCM/NO CACHE */
        default:
            break;
    }
}



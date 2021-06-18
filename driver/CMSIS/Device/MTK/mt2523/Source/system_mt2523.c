/* Copyright Statement:
 *
 */

#include "mt2523.h"

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


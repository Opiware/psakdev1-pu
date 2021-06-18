/* Copyright Statement:
 *
 */

#include "type_def.h"
#include "top.h"
#include "mt7687.h"
#include "system_mt7687.h"
#include "mt7687_cm4_hw_memmap.h"
#include "spi_flash.h"
#include "memory_attribute.h"

static uint32_t gXtalFreq;
static uint32_t gCpuFrequency;


/**
  * @brief  This function is to initialize XTAL based on HW strap.
  * @param  None
  * @retval None
  */
void top_xtal_init(void)
{
    uint32_t  u4RegVal = 0;
    unsigned long reg = HAL_REG_32(TOP_AON_CM4_STRAP_STA);
    reg = (reg >> 13) & 0x00000007;

    u4RegVal = HAL_REG_32(TOP_AON_CM4_PWRCTLCR);
    u4RegVal &= (~(CM4_PWRCTLCR_CM4_XTAL_FREQ_MASK));

    switch (reg) {
        case 0:
            gXtalFreq = 20000000;  /* 20Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_20M_OFFSET);
            break;
        case 1:
            gXtalFreq = 40000000;  /* 40Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_40M_OFFSET);
            break;
        case 2:
            gXtalFreq = 26000000;  /* 26Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_26M_OFFSET);
            break;
        case 3:
            gXtalFreq = 52000000;  /* 52Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_52M_OFFSET);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            gXtalFreq = 40000000;  /* fall through */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_40M_OFFSET);
            break;
    }

    HAL_REG_32(TOP_AON_CM4_PWRCTLCR) = u4RegVal;
    gCpuFrequency = gXtalFreq;
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
}

/**
  * @brief  This function is to get current XTAL frequency number.
  * @param  None
  * @retval current XTAL frequency number.
  */
uint32_t top_xtal_freq_get(void)
{
    return gXtalFreq;
}

/**
  * @brief  This function is to get current MCU frequency number.
  * @param  None
  * @retval current MCU frequency number.
  */
uint32_t top_mcu_freq_get(void)
{
    return gCpuFrequency;
}

/**
  * @brief  This function is to enable PPL1.
  * @param  None
  * @retval None
  */
void cmnPLL1ON(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4PWRCtl = (volatile uint32_t *)TOP_CFG_CM4_PWR_CTL_CR;

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = (reg >>  CM4_MPLL_EN_SHIFT) & CM4_MPLL_EN_MASK;

    if (reg == CM4_MPLL_EN_PLL1_OFF_PLL2_OFF) {
        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
        reg = reg | (CM4_MPLL_EN_PLL1_ON_PLL2_OFF << CM4_MPLL_EN_SHIFT);    // Or only, so PLL2 setting won't be cleared
        cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

        do {
            reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
            reg = reg & (CM4_BT_PLL_RDY_MASK << CM4_BT_PLL_RDY_SHIFT);
        } while (!reg);
    }
    return;
}

/**
  * @brief  This function is to enable both PPL1 and PLL2.
  * @param  MCU 960M enable selector
  * @retval None
  */
void cmnPLL1ON_PLL2ON(uint8_t fg960M)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4PWRCtl = (volatile uint32_t *)TOP_CFG_CM4_PWR_CTL_CR;

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = (reg >>  CM4_MPLL_EN_SHIFT) & CM4_MPLL_EN_MASK;

    if (reg != CM4_MPLL_EN_PLL1_ON_PLL2_ON) {
        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & ~(CM4_MCU_960_EN_MASK << CM4_MCU_960_EN_SHIFT);
        reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
        reg = reg | (CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
        cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & ~(CM4_MPLL_EN_MASK << CM4_MPLL_EN_SHIFT);
        reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
        reg = reg | (CM4_MPLL_EN_PLL1_ON_PLL2_ON << CM4_MPLL_EN_SHIFT);
        cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

        do {
            reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
            reg = reg & (CM4_WF_PLL_RDY_MASK << CM4_WF_PLL_RDY_SHIFT);
        } while (!reg);

        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & ~(CM4_MCU_960_EN_MASK << CM4_MCU_960_EN_SHIFT);
        reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    }

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    if (fg960M) {
        reg = reg | (CM4_MCU_960_EN_ENABLE << CM4_MCU_960_EN_SHIFT);
    } else {
        reg = reg & ~(CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
    }
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);
    return;
}

/**
  * @brief  This function is to disable both PPL1 and PLL2.
  * @param  None
  * @retval None
  */
void cmnPLL1OFF_PLL2OFF(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4PWRCtl = (volatile uint32_t *)TOP_CFG_CM4_PWR_CTL_CR;

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_MPLL_EN_MASK << CM4_MPLL_EN_SHIFT);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    reg = reg | (CM4_MPLL_EN_PLL1_OFF_PLL2_OFF << CM4_MPLL_EN_SHIFT);
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_MCU_960_EN_MASK << CM4_MCU_960_EN_SHIFT);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    reg = reg | (CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

    return;
}

/**
  * @brief  This function is to config CPU frequency equaling with XTAL.
  * @param  None
  * @retval None
  */
void cmnCpuClkConfigureToXtal(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4CKG = (volatile uint32_t *)TOP_CFG_CM4_CKG_EN0;

    // Step1. CM4_HCLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_OSC << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step2. CM4_RF_CLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_XTAL << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    gCpuFrequency = top_xtal_freq_get();
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
    return;
}

/**
  * @brief  This function is to config CPU frequency to 192Mhz.
  * @param  None
  * @retval None
  */
void cmnCpuClkConfigureTo192M(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4CKG = (volatile uint32_t *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1 & 2
    cmnPLL1ON_PLL2ON(TRUE);

    // Step2. CM4_RF_CLK_SW set to PLL2(960)
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_WIFI_PLL_960 << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. set divider to 1+8/2=5, ->  960/5=192Mhz
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_MCU_DIV_SEL_MASK << CM4_MCU_DIV_SEL_SHIFT);
    reg = reg | (8 << CM4_MCU_DIV_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step4. CM4_HCLK_SW set to PLL_CK
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_PLL << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);
    gCpuFrequency = MCU_FREQUENCY_192MHZ;
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
    return;
}

/**
  * @brief  This function is to config CPU frequency to 160Mhz.
  * @param  None
  * @retval None
  */
void cmnCpuClkConfigureTo160M(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4CKG = (volatile uint32_t *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1 & 2
    cmnPLL1ON_PLL2ON(FALSE);

    // Step2. CM4_RF_CLK_SW set to PLL2(320)
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_WIFI_PLL_320 << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. set divider to 1+2/2=2, ->  320/2=160Mhz
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_MCU_DIV_SEL_MASK << CM4_MCU_DIV_SEL_SHIFT);
    reg = reg | (2 << CM4_MCU_DIV_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step4. CM4_HCLK_SW set to PLL_CK
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_PLL << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);
    gCpuFrequency = MCU_FREQUENCY_160MHZ;
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
    return;
}


/**
  * @brief  This function is to config CPU frequency to 64Mhz.
  * @param  None
  * @retval None
  */
void cmnCpuClkConfigureTo64M(void)
{
    volatile uint32_t reg;
    volatile uint32_t *pTopCfgCM4CKG = (volatile uint32_t *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1
    cmnPLL1ON();

    // Step2. CM4_RF_CLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_XTAL << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. CM4_HCLK_SW set to SYS_64M
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_SYS_64M << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);
    gCpuFrequency = MCU_FREQUENCY_64MHZ;
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
    return;
}

//
//  Using Xtal as SPI Flash clock
//
ATTR_TEXT_IN_TCM void cmnSerialFlashClkConfToXtal(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgHclk = (volatile UINT32 *)TOP_CFG_HCLK_2M_CKGEN;

    reg = cmnReadRegister32(pTopCfgHclk);
    reg = reg & ~(SF_TOP_CLK_SEL_MASK << SF_TOP_CLK_SEL_SHIFT);
    reg = reg | (SF_TOP_CLK_SEL_XTAL << SF_TOP_CLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgHclk, reg);
}

#ifdef HAL_FLASH_MODULE_ENABLED
//
//  Using PLL1/64M as SPI Flash clock
//
ATTR_TEXT_IN_TCM void cmnSerialFlashClkConfTo64M(void)
{
    volatile UINT32 reg = 0;
    volatile UINT32 *pTopCfgHclk = (volatile UINT32 *)TOP_CFG_HCLK_2M_CKGEN;

    //open PLL1
    cmnPLL1ON();

    // Switch flash clock from XTAL to SYS 64Mhz.
    reg = cmnReadRegister32(pTopCfgHclk);
    reg = reg & ~(SF_TOP_CLK_SEL_MASK << SF_TOP_CLK_SEL_SHIFT);
    reg = reg | (SF_TOP_CLK_SEL_SYS_64M << SF_TOP_CLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgHclk, reg);

#if 1 /*set KGD value*/
    mSetHWEntry(SFC_MISC1_DEL_LATCH_LATENCY, 0);
    mSetHWEntry(SFC_MISC1_SMPCK_INV, 1);
    mSetHWEntry(SFC_DELAY_CONTROL3_SFCK_SAM_DLY, 0x18);
#endif
    return;
}

#endif


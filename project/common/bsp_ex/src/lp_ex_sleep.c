/* Copyright Statement:
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include "mlog.h" */

#include "hal_lp.h"

#if ((PRODUCT_VERSION == 7686)||(PRODUCT_VERSION == 7682)||(PRODUCT_VERSION == 5932))
#include "mt7686.h"
#include "system_mt7686.h"
#elif ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))
#include "lp_ex_sleep.h"
#include "mt7687.h"
#include "system_mt7687.h"
#include "hal_sleep_driver.h"
#endif
#include "connsys_driver.h"

#include "timer.h"
#include "top.h"
#include "hal_sleep_manager.h"
#include "FreeRTOS.h"
#include "toi.h"
#include "hal_rtc.h"
#include "hal_gpt.h"

#define HAL_REG_32(reg)         (*((volatile unsigned int *)(reg)))

extern uint32_t hal_sleep_manager_sleep_driver_dump_handle_name(void);

void hal_ex_lp_gpt_isr(void)
{
}

#if ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))
static uint8_t _cli_deep_sleep(uint8_t len, char *param[])
{
    int time = 0;

    if (len == 0) {
        printf("error: need parameter\n");
        return 0;
    }

    time = (int)strtol(param[0], NULL, 10);
    if (time == 0) {
        printf("error: invalid parameter\n");
        return 0;
    }

    /* Setup timer as wakeup source */
    /* TMR0 is usesd by iperf */
    drvTMR_init(TMR1, (atoi(param[0]) * 32768), 0, hal_ex_lp_gpt_isr);//1
    TMR_Stop(TMR0);
    TMR_Start(TMR1);

    /* Enable FW_OWN_BACK_INT interrupt */
    hal_lp_connsys_get_own_enable_int();

    /* Give connsys ownership to N9 */
    hal_lp_connsys_give_n9_own();

    /* Switch flash clock to XTAL */
    cmnSerialFlashClkConfToXtal();

    /* Switch MCU clock to XTAL */
    cmnCpuClkConfigureToXtal();

    /* Unclaim PLL usage */
    cmnPLL1OFF_PLL2OFF();

    hal_lp_deep_sleep();

    return 0;
}

static uint8_t _cli_legacy_sleep(uint8_t len, char *param[])
{
    int time = 0;

    if (len == 0) {
        printf("error: need parameter\n");
        return 0;
    }

    time = (int)strtol(param[0], NULL, 10);
    if (time == 0) {
        printf("error: invalid parameter\n");
        return 0;
    }

    /* Setup timer as wakeup source */
    /* TMR_IDX0 is usesd by iperf */
    drvTMR_init(HAL_GPT_1, (atoi(param[0]) * 32768), 0, hal_ex_lp_gpt_isr);//1

    /* disable TMR_IDX0 which trigger a 30sec timer due to tickless */
    TMR_Stop(HAL_GPT_0);

    TMR_Start(HAL_GPT_1);

    /* Enable FW_OWN_BACK_INT interrupt */
    hal_lp_connsys_get_own_enable_int();

    /* Give connsys ownership to N9 */
    hal_lp_connsys_give_n9_own();

    /* Switch flash clock to XTAL */
    cmnSerialFlashClkConfToXtal();

    /* Switch MCU clock to XTAL */
    cmnCpuClkConfigureToXtal();

    /* Unclaim PLL usage */
    cmnPLL1OFF_PLL2OFF();

    hal_lp_legacy_sleep();

    /* After wakeup from legacy sleep */
    /* Enable MCU clock to 192MHz */
    cmnCpuClkConfigureTo192M();

    /* Enable flash clock to 64MHz */
    cmnSerialFlashClkConfTo64M();

    /* re-init connsys for handling inband-cmd response */
    connsys_open();

    TMR_Start(HAL_GPT_0);

    return 0;
}

#if configUSE_TICKLESS_IDLE == 2
extern uint32_t ticklessTryCount;
extern uint32_t ticklessWFICount;
extern uint32_t ticklessLSCount;
extern uint32_t ticklessIdleCount;
#endif

static uint8_t _cli_tickless_mode(uint8_t len, char *param[])
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
#if configUSE_TICKLESS_IDLE == 2
#ifdef configTICKLESS_DYNAMIC_ENABLE
    int ticklessMode = 1;
#endif

#ifdef configTICKLESS_DYNAMIC_ENABLE
    ticklessMode = atoi(param[0]);

    switch (ticklessMode) {
    case 0:
        sleepdrv_set_sleep_mode(HAL_SLEEP_MODE_NONE);
        break;
    case 1:
        sleepdrv_set_sleep_mode(HAL_SLEEP_MODE_SLEEP);
        break;
    case 2:
        sleepdrv_set_sleep_mode(HAL_SLEEP_MODE_LEGACY_SLEEP);
        break;
    default:
        printf("unsupported mode %d\n", ticklessMode);
        break;
    }

    ticklessTryCount  = 0;
    ticklessWFICount  = 0;
    ticklessLSCount   = 0;
    ticklessIdleCount = 0;
#endif
#endif
#endif
    return 0;
}

static uint8_t _cli_tickless_status(uint8_t len, char *param[])
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
#if configUSE_TICKLESS_IDLE == 2
    hal_sleep_mode_t ticklessMode = sleepdrv_get_sleep_mode();

    printf("tickless:\n");
    printf("\ttried   %u times\n", (unsigned int)ticklessTryCount);
    printf("\tentered wfi  %u times\n", (unsigned int)ticklessWFICount);
    printf("\tentered ls   %u times\n", (unsigned int)ticklessLSCount);
    printf("\tentered idle %u times\n", (unsigned int)ticklessIdleCount);
    printf("\t%s\n", ticklessMode ? "enabled" : "disabled");

    #if ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))
    if (ticklessMode == HAL_SLEEP_MODE_SLEEP) {
        printf("\tmode: WFI\n");
    } else if (ticklessMode == HAL_SLEEP_MODE_LEGACY_SLEEP) {
        printf("\tmode: Legacy Sleep\n");
    }
    #elif  ((PRODUCT_VERSION == 7686)||(PRODUCT_VERSION == 7682)||(PRODUCT_VERSION == 5932))
    if (ticklessMode == HAL_SLEEP_MODE_IDLE) {
        printf("\tmode: WFI\n");
    } else if (ticklessMode == HAL_SLEEP_MODE_SLEEP) {
        printf("\tmode: Deep Sleep\n");
    }
    #endif

    printf("\t%s\n", hal_sleep_manager_is_sleep_locked() ? "locked" : "not locked");
    if (hal_sleep_manager_is_sleep_locked()) {
        hal_sleep_manager_sleep_driver_dump_handle_name();
    }
#endif
#endif
    return 0;
}

static uint8_t _cli_rtc_mode(uint8_t len, char *param[])
{
    printf("ready to enter RTC mode.\n");
    hal_rtc_sleep(HAL_RTC_SLEEP_MAGIC);
    
#ifdef HAL_RTC_FEATURE_SLEEP
    if (HAL_RTC_STATUS_OK == hal_rtc_init()) {
        printf("ready to enter RTC mode.\n");
        hal_rtc_sleep(HAL_RTC_SLEEP_MAGIC);
    } else {
        printf("RTC init fail.\n");
    }
#endif
    return 0;
}

cmd_t lp_cli[] = {
    { "ls",              "legacy sleep",                  _cli_legacy_sleep    },
#if ((PRODUCT_VERSION == 7687)||(PRODUCT_VERSION == 7697))
    { "ds",              "deep sleep",                    _cli_deep_sleep      },
#endif
    { "tick",            "tickless enable",               _cli_tickless_mode   },
    { "status",          "tickless status",               _cli_tickless_status },
    { "rtc",             "rtc mode",                      _cli_rtc_mode        },
    { NULL }
};
#endif

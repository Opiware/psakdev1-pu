
/* Copyright Statement:
 *
 */

#ifndef _HAL_WDT_INTERNAL_H_
#define _HAL_WDT_INTERNAL_H_

#define WDT_EN_KEY                          (0x11)
#define WDT_LENGTH_KEY                      (0x12)
#define WDT_INTERVAL_KEY                    (0x13)
#define WDT_SW_RESTART_KEY                  (0x1456789a)
#define WDT_SW_RST_KEY                      (0x156789ab)
#define WDT_AUTO_RESTART_EN_KEY             (0x16)
#define WDT_IE_KEY                          (0x17)
#define WDT_CONNSYS_SW_RST_KEY              (0x18)
#define WDT_CONNSYS_CPU_SW_RST_KEY          (0x19)
#define WDT_SDCTL_SW_RST_KEY                (0x1a)
#define WDT_RETENTION_KEY                   (0x1b)
#define WDT_JTAG_RST_MASK_KEY               (0x1c)
#define WDT_AIRCR_RST_MASK_KEY              (0x1d)
#define WDT_PCM_RST_KEY                     (0x1e)
#define WDT_PMU_RST_KEY                     (0x1f)
#define WDT_AIRCR_RST_INTERVAL_KEY          (0x21)
#define WDT_RETENTION_FALG0_KEY             (0x22)
#define WDT_RETENTION_FALG1_KEY             (0x23)
#define WDT_RETENTION_FALG2_KEY             (0x24)
#define WDT_RETENTION_FALG3_KEY             (0x25)
#define WDT_RETENTION_FALG4_KEY             (0x26)
#define WDT_RETENTION_FALG5_KEY             (0x27)


#define WDT_STANDARD_1_OFFSET               (8)
#define WDT_STANDARD_1_MASK                 (0x1 << WDT_STANDARD_1_OFFSET)

#define WDT_STANDARD_8_OFFSET               (8)
#define WDT_STANDARD_8_MASK                 (0xff << WDT_STANDARD_8_OFFSET)

#define WDT_STANDARD_16_OFFSET              (16)
#define WDT_STANDARD_16_MASK                (0xffff << WDT_STANDARD_16_OFFSET)

#define WDT_STANDARD_32_OFFSET              (0)
#define WDT_STANDARD_32_MASK                (0xffffffff << WDT_STANDARD_32_OFFSET)

#define WDT_STA_SW_WDT_OFFSET               (0)
#define WDT_STA_SW_WDT_MASK                 (0x1 << WDT_STA_SW_WDT_OFFSET)
#define WDT_STA_HW_WDT_OFFSET               (1)
#define WDT_STA_HW_WDT_MASK                 (0x1 << WDT_STA_HW_WDT_OFFSET)


#define WDT_MAX_TIMEOUT_VALUE               (1000)  /* 1000s */
#define WDT_1_TICK_LENGTH                   (156)   /* 15.6ms */


void wdt_set_length(uint32_t seconds);
void wdt_set_mode(uint32_t value);
void wdt_set_restart(void);
void wdt_set_sw_rst(void);
void wdt_set_enable(uint32_t enable);
uint32_t wdt_get_reset_status(void);
uint32_t wdt_get_enable_status(void);
uint32_t wdt_get_mode_status(void);
void wdt_clear_irq(void);


#endif /* #ifndef _HAL_WDT_INTERNAL_H_ */


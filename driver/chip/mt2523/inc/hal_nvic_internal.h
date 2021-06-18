/* Copyright Statement:
 *
 */

#ifndef _HAL_NVIC_INTERNAL_H_
#define _HAL_NVIC_INTERNAL_H_
#include "hal_nvic.h"

#ifdef HAL_NVIC_MODULE_ENABLED
/* Please refer to configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY= 4 in freertos_config.h */
#define FREERTOS_ISR_API_PRIORITY  (4)          /* please keep the setting */
/* DEFAULT_IRQ_PRIORITY is from FREERTOS_ISR_API_PRIORITY =  4  to  configKERNEL_INTERRUPT_PRIORITY -1 = (0xFF - 1)
    as pend_sv should be lowest irq priority to avoid unneccessary freert_os schedule */
#define DEFAULT_IRQ_PRIORITY  (FREERTOS_ISR_API_PRIORITY + 1)     /* please keep the setting */


#define OSTimer_IRQ_PRIORITY     (DEFAULT_IRQ_PRIORITY)
#define RESERVED_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 63)
#define MD_TOPSM_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 2)
#define CM4_TOPSM_IRQ_PRIORITY   (DEFAULT_IRQ_PRIORITY + 3)
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
#define ACCDET_IRQ_PRIORITY      (DEFAULT_IRQ_PRIORITY + 8)
#define RTC_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 9)
#define KP_IRQ_PRIORITY          (DEFAULT_IRQ_PRIORITY + 10)
#define GPTTIMER_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 11)
#define EINT_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 12)
#define LCD_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 13)
#define LCD_AAL_IRQ_PRIORITY     (DEFAULT_IRQ_PRIORITY + 14)
#define DSI_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 15)
#define RESIZE_IRQ_PRIORITY      (DEFAULT_IRQ_PRIORITY + 16)
#define G2D_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 17)
#define CAM_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 18)
#define ROT_DMA_IRQ_PRIORITY     (DEFAULT_IRQ_PRIORITY + 19)
#define SCAM_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 20)
/*UART/MSDC/I2C/BTIF's interrupt priority should be lower than DMA/DMA_AO/SensorDMA*/
#define DMA_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 21)
#define DMA_AO_IRQ_PRIORITY      (DEFAULT_IRQ_PRIORITY + 22)
#define I2C_DUAL_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 23)
#define I2C0_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 24)
#define I2C1_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 25)
#define I2C2_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 26)
//RESERVED IRQ
#define GPCOUNTER_IRQ_PRIORITY   (DEFAULT_IRQ_PRIORITY + 28)
#define UART0_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 29)
#define UART1_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 30)
#define UART2_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 31)
#define UART3_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 32)
#define USB20_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 33)
#define MSDC0_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 34)
#define MSDC1_IRQ_PRIORITY       (DEFAULT_IRQ_PRIORITY + 35)
//RESERVED IRQ
//RESERVED IRQ
#define SF_IRQ_PRIORITY          (DEFAULT_IRQ_PRIORITY + 38)
#define DSP22CPU_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 39)
#define SENSORDMA_IRQ_PRIORITY   (DEFAULT_IRQ_PRIORITY + 21)
#define RGU_IRQ_PRIORITY         (DEFAULT_IRQ_PRIORITY + 41)
#define SPI_SLV_IRQ_PRIORITY     (DEFAULT_IRQ_PRIORITY + 42)
#define SPI_MST0_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 43)
#define SPI_MST1_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 44)
#define SPI_MST2_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 45)
#define SPI_MST3_IRQ_PRIORITY    (DEFAULT_IRQ_PRIORITY + 46)
#define TRNG_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 47)
#define BT_TIMCON_IRQ_PRIORITY   (DEFAULT_IRQ_PRIORITY + 48)
#define BTIF_IRQ_PRIORITY        (DEFAULT_IRQ_PRIORITY + 49)
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ
//RESERVED IRQ

extern uint32_t save_and_set_interrupt_mask(void);
extern void restore_interrupt_mask(uint32_t mask);
extern hal_nvic_status_t nvic_irq_software_trigger(hal_nvic_irq_t irq_number);
uint32_t hal_nvic_query_exception_number(void);

#endif //HAL_NVIC_MODULE_ENABLED
#endif //_HAL_NVIC_INTERNAL_H_

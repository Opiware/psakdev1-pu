/* Copyright Statement:
 *
 */

#ifndef __BL_GPT_H__
#define __BL_GPT_H__

#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*************************** GPT register definition start line  ****************************** */

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

typedef struct {
    __I   uint32_t	GPT_IRQSTA;
    __IO  uint32_t  GPT_IRQMSK0;
    __IO  uint32_t  GPT_IRQMSK1;
} BL_GPT_REGISTER_GLOABL_T;

typedef struct {
    __IO uint32_t GPT_CON ;					/*!< timer enable and mode config*/
    __IO uint32_t GPT_CLK ;                 /*!< clock select and prescale config*/
    __IO uint32_t GPT_IRQ_EN ;              /*!< interrupt enable*/
    __I  uint32_t GPT_IRQ_STA ;             /*!< interrupt status*/
    __O  uint32_t GPT_IRQ_ACK;             	/*!< interrupt ack*/
    __IO uint32_t GPT_COUNT ;               /*!< gpt0~4 count,gpt5 low word*/
    __IO uint32_t GPT_COMPARE ;             /*!< gpt0~4 threshold,gpt5 low word*/
    __IO uint32_t GPT_COUNTH;               /*!< count, only for gpt5 low word*/
    __IO uint32_t GPT_COMPAREH;             /*!< threshold, only for gpt5 low word*/
} BL_GPT_REGISTER_T;


#define _BL_GPT_BASE_		   (0xA2140000)
#define _BL_GPT_BASEADDR_      (_BL_GPT_BASE_ + 0x000)
#define _BL_GPT1_BASEADDR_     (_BL_GPT_BASE_ + 0x010)
#define _BL_GPT2_BASEADDR_     (_BL_GPT_BASE_ + 0x040)
#define _BL_GPT3_BASEADDR_     (_BL_GPT_BASE_ + 0x070)
#define _BL_GPT4_BASEADDR_     (_BL_GPT_BASE_ + 0x0a0)
#define _BL_GPT5_BASEADDR_     (_BL_GPT_BASE_ + 0x0d0)
#define _BL_GPT6_BASEADDR_     (_BL_GPT_BASE_ + 0x100)

#define BL_GPTGLB              ((BL_GPT_REGISTER_GLOABL_T*)(_BL_GPT_BASEADDR_))
#define BL_GPT0                ((BL_GPT_REGISTER_T*)(_BL_GPT1_BASEADDR_))
#define BL_GPT1                ((BL_GPT_REGISTER_T*)(_BL_GPT2_BASEADDR_))
#define BL_GPT2                ((BL_GPT_REGISTER_T*)(_BL_GPT3_BASEADDR_))
#define BL_GPT3                ((BL_GPT_REGISTER_T*)(_BL_GPT4_BASEADDR_))
#define BL_GPT4                ((BL_GPT_REGISTER_T*)(_BL_GPT5_BASEADDR_))
#define BL_GPT5                ((BL_GPT_REGISTER_T*)(_BL_GPT6_BASEADDR_))

#define BL_GPT_DELAY_MS_PORT	BL_GPT5
#define BL_GPT_DELAY_US_PORT	BL_GPT4

/*GPT PDN*/
#define BL_GPT_REG(_ADDRBASE_) 	(*(volatile unsigned int *)(_ADDRBASE_))
#define BL_GPT_PDN_CLRD2		(0xA2010328)
#define BL_GPT_PDN_COND2		(0xA2010308)
#define BL_GPT_PDN_MASK			(1<<2)

/*GPT mode*/
#define BL_GPT_MODE_ONE_SHOT  	0x00
#define BL_GPT_MODE_REPEAT    	0x10
#define BL_GPT_MODE_KEEP_GO   	0x20
#define BL_GPT_MODE_FREE_RUN  	0x30


/*GPT control mask*/
#define BL_GPT_COUNT_CLEAR      (0x0002)
#define BL_GPT_COUNT_START      (0x0001)
#define BL_GPT_CLOCK_32KHZ      (0x0010)
#define BL_GPT_CLOCK_13MHZ      (0x0000)

/*GPT clcok gate control*/
#define BL_GPT_CLOCK_UNGATE   		0x00
#define	BL_GPT_CLOCK_GATE 	  	 	0x40

/*GPT division*/
#define BL_GPT_DIVIDE_1  		0
#define BL_GPT_DIVIDE_2  		1
#define BL_GPT_DIVIDE_3  		2
#define BL_GPT_DIVIDE_4  		3
#define BL_GPT_DIVIDE_5  		4
#define BL_GPT_DIVIDE_6  		5
#define BL_GPT_DIVIDE_7  		6
#define BL_GPT_DIVIDE_8  		7
#define BL_GPT_DIVIDE_9  		8
#define BL_GPT_DIVIDE_10 		9
#define BL_GPT_DIVIDE_11 		10
#define BL_GPT_DIVIDE_12 		11
#define BL_GPT_DIVIDE_13 		12
#define BL_GPT_DIVIDE_16 		13
#define BL_GPT_DIVIDE_32 		14
#define BL_GPT_DIVIDE_64 		15

/** @brief GPT clock source */
typedef enum {
    BL_GPT_CLOCK_SOURCE_32K = 0,            /**< Set the GPT clock source to 32khz*/
    BL_GPT_CLOCK_SOURCE_1M  = 1             /**< Set the GPT clock source to 1mhz */
} bl_gpt_clock_source_t;



/******** funtion extern **************/
extern bool bl_gpt_delay_us(uint32_t us);
extern bool bl_gpt_delay_ms(uint32_t ms);
extern bool bl_gpt_get_free_run_count(bl_gpt_clock_source_t clock_source, uint32_t *count);

#ifdef __cplusplus
}
#endif


#endif /* __BL_GPT_H__ */ 


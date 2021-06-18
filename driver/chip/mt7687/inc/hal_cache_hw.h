/* Copyright Statement:
 *
 */

#ifndef __HAL_CACHE_HW_H__
#define __HAL_CACHE_HW_H__

#ifdef __cplusplus
#define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
#define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define   __O     volatile             /*!< Defines 'write only' permissions                */
#define   __IO    volatile             /*!< Defines 'read / write' permissions              */

#ifndef NULL
#ifdef __cplusplus
#define NULL				(0) /*!< NULL */
#else
#define NULL				((void *)(0)) /*!< NULL */
#endif
#endif

/* structure type to access the CACHE register */
typedef struct {
    __IO uint32_t CACHE_CON;
    __IO uint32_t CACHE_OP;
    __IO uint32_t CACHE_HCNT0L;
    __IO uint32_t CACHE_HCNT0U;
    __IO uint32_t CACHE_CCNT0L;
    __IO uint32_t CACHE_CCNT0U;
    __IO uint32_t CACHE_HCNT1L;
    __IO uint32_t CACHE_HCNT1U;
    __IO uint32_t CACHE_CCNT1L;
    __IO uint32_t CACHE_CCNT1U;
    uint32_t RESERVED0[1];
    __IO uint32_t CACHE_REGION_EN;
    uint32_t RESERVED1[16372];                  /**< (0x10000-12*4)/4 */
    __IO uint32_t CACHE_ENTRY_N[16];
    __IO uint32_t CACHE_END_ENTRY_N[16];
} CACHE_REGISTER_T;

/* CACHE_CON register definitions */
#define CACHE_CON_MCEN_OFFSET 					(0)
#define CACHE_CON_MCEN_MASK 					(1<<CACHE_CON_MCEN_OFFSET)

#define CACHE_CON_CNTEN0_OFFSET 				(2)
#define CACHE_CON_CNTEN0_MASK 					(1<<CACHE_CON_CNTEN0_OFFSET)

#define CACHE_CON_CNTEN1_OFFSET 				(3)
#define CACHE_CON_CNTEN1_MASK 					(1<<CACHE_CON_CNTEN1_OFFSET)

#define CACHE_CON_MDRF_OFFSET 				    (7)
#define CACHE_CON_MDRF_MASK 					(0x1UL<<CACHE_CON_MDRF_OFFSET)

#define CACHE_CON_CACHESIZE_OFFSET 				(8)
#define CACHE_CON_CACHESIZE_MASK 				(3<<CACHE_CON_CACHESIZE_OFFSET)

/* CACHE_OP register definitions */
#define CACHE_OP_EN_OFFSET 						(0)
#define CACHE_OP_EN_MASK 						(1<<CACHE_OP_EN_OFFSET)

#define CACHE_OP_OP_OFFSET 						(1)
#define CACHE_OP_OP_MASK 						(15<<CACHE_OP_OP_OFFSET)

#define CACHE_OP_TADDR_OFFSET 					(5)
#define CACHE_OP_TADDR_MASK 					(0x7FFFFFFUL<<CACHE_OP_TADDR_OFFSET)

/* CACHE_HCNT0L register definitions */
#define CACHE_HCNT0L_CHIT_CNT0_MASK 			(0xFFFFFFFFUL<<0)

/* CACHE_HCNT0U register definitions */
#define CACHE_HCNT0U_CHIT_CNT0_MASK				(0xFFFFUL<<0)

/* CACHE_CCNT0L register definitions */
#define CACHE_CCNT0L_CACC_CNT0_MASK				(0xFFFFFFFFUL<<0)

/* CACHE_CCNT0U register definitions */
#define CACHE_CCNT0U_CACC_CNT0_MASK				(0xFFFFUL<<0)

/* CACHE_HCNT1L register definitions */
#define CACHE_HCNT1L_CHIT_CNT1_MASK				(0xFFFFFFFFUL<<0)

/* CACHE_HCNT1U register definitions */
#define CACHE_HCNT1U_CHIT_CNT1_MASK				(0xFFFFUL<<0)

/* CACHE_CCNT1L register definitions */
#define CACHE_CCNT1L_CACC_CNT1_MASK				(0xFFFFFFFFUL<<0)

/* CACHE_CCNT1U register definitions */
#define CACHE_CCNT1U_CACC_CNT1_MASK				(0xFFFFUL<<0)

/* CACHE_ENTRY_N register definitions */
#define CACHE_ENTRY_N_C_MASK 					(1<<8)
#define CACHE_ENTRY_BASEADDR_MASK 				(0xFFFFFUL<<12)

/* CACHE_END_ENTRY_N register definitions */
#define CACHE_END_ENTRY_N_BASEADDR_MASK 		(0xFFFFFUL<<12)

/* memory mapping of MT7687 */
#define CMSYS_L1CACHE_BASE 						(0x01530000)
#define CACHE  									((CACHE_REGISTER_T *)CMSYS_L1CACHE_BASE)

#endif /* __HAL_CACHE_HW_H__ */


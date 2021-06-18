/* Copyright Statement:
 *
 */

#ifndef __NVIC_H__
#define __NVIC_H__


#include "mt7686.h"

void NVIC_SetupVectorTable(uint32_t addr);
void NVIC_SWInt(unsigned int source);

__STATIC_INLINE uint32_t NVIC_GetVectActive(void)
{
    return ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) >> SCB_ICSR_VECTACTIVE_Pos) - 16;
}


#define local_irq_save(flag)				\
	do{						\
		flag = __get_PRIMASK();			\
		__disable_irq();			\
	}while(0);


#define local_irq_restore(flag)			\
	do {					\
		__set_PRIMASK(flag);		\
	}while(0);


#endif


/* Copyright Statement:
 *
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__


#include <stdio.h>

#ifndef ASSERT
#define ASSERT(expr)	if((expr) ==0){			\
				printf("ASSERT, __FILE__ = %s, __LINE__ = %u", __FILE__, __LINE__);	\
				while(1);		\
			}

#endif

#endif

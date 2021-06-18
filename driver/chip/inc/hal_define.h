/* Copyright Statement:
 *
 */

#ifndef __HAL_DEFINE_H__
#define __HAL_DEFINE_H__


#include <stdint.h>
#include <stdbool.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL				(0) /*!< NULL */
#else
#define NULL				((void *)(0)) /*!< NULL */
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* __HAL_DEFINE_H__ */


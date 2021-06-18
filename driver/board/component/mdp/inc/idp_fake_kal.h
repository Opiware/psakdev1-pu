/* Copyright Statement:
 *
 */

#ifndef __idp_fake_kal_h__
#define __idp_fake_kal_h__

#if defined(IDP_FAKE_KAL_SUPPORT)

#include <FreeRTOSConfig.h>
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

#define KAL_NILTASK_ID (kal_taskid)NULL
#define kal_mem_set memset
#define ASSERT configASSERT

extern kal_bool kal_if_hisr(void);
extern kal_bool kal_if_lisr(void);
extern kal_taskid kal_get_task_self_id(void);

#define kal_create_sem(...) 0
//extern kal_semid kal_create_sem(kal_char *name, kal_uint32 initial_count);
extern kal_status kal_take_sem(kal_semid ext_sem_id_ptr, kal_wait_mode wait_mode);
extern void kal_give_sem(kal_semid ext_sem_id_ptr);

//extern void ASSERT(int const expr);

#endif

#endif

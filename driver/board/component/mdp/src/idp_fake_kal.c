/* Copyright Statement:
 *
 */

#include <idp_define.h>

#if !defined(IDP_FULL_KAL_SUPPORT)

#include <idp_fake_kal.h>

kal_bool
kal_if_hisr(void)
{
  return KAL_FALSE;
}

kal_bool
kal_if_lisr(void)
{
  return KAL_FALSE;
}

kal_taskid
kal_get_task_self_id(void)
{
  return NULL;
}

kal_semid
kal_create_sem(kal_char *name, kal_uint32 initial_count)
{
}

kal_status
kal_take_sem(kal_semid ext_sem_id_ptr, kal_wait_mode wait_mode)
{
  return 0;
}

void
kal_give_sem(kal_semid ext_sem_id_ptr)
{
}

void
ASSERT(int const expr)
{
  int i = 1;
  
  if (0 == expr)
  {
    while (i)
    {
    }
  }
}

#endif

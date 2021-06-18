/* Copyright Statement:
 *
 */

#include "gdi_internal.h"
#include <stdlib.h>
/* extern void* TCD_Current_Thread; */
extern uint8_t INT_Exception_Enter;
extern void INT_ExceptionDumpStack(long *dumpbuf, long *current_thread);

#include "gdi_mutex.h"
#include "gdi_primitive.h"
//#include "gdi_image.h"
#include "gdi_const.h"
#include "gdi_datatype.h"

#define GDI_MUTEX_GUARD_PATTERN 0x87654321

gdi_mutex_struct gdi_mutex = {GDI_MUTEX_GUARD_PATTERN,0,NULL,0,GDI_MUTEX_GUARD_PATTERN};
// int gdi_mutex_serial = 0;

#ifdef GDI_MUTEX_DEBUG_DUMP_STACK
long gdi_mutex_stack_backup[120];
#endif 
/* ///////////////////////////////////////////////////////////////////////////////////////////////////// */

/*****************************************************************************
 * FUNCTION
 *  gdi_mutex_init
 * DESCRIPTION
 *  
 * PARAMETERS
 *  m       [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_mutex_init(gdi_mutex_struct *m)
{
    m->cnt = 0;
    m->tid = NULL;
    m->front_guard = GDI_MUTEX_GUARD_PATTERN;
    m->rear_guard = GDI_MUTEX_GUARD_PATTERN;
}

/* CFTBD: should implement mutex APIs. */
/*****************************************************************************
 * FUNCTION
 *  gdi_mutex_lock
 * DESCRIPTION
 *  
 * PARAMETERS
 *  M       [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_mutex_lock(gdi_mutex_struct *M)
{
#if 0
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    uint32_t save_irq_mask;
    kal_taskid gdi_current_thread_id = kal_get_current_thread_ID();

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (INT_Exception_Enter)
    {
        return;
    }
    if (gdi_current_thread_id == NULL)
    {
        return;
    }

    if (gdi_current_thread_id != M->tid)
    {
        /* wait gdi mutex free */
        while (1)
        {
            save_irq_mask = SaveAndSetIRQMask();
            if (M->cnt == 0)
            {
                M->cnt = 1;
                RestoreIRQMask(save_irq_mask);
                break;
            }
            RestoreIRQMask(save_irq_mask);
            kal_sleep_task(1);  /* waiting */
        }

        /* get gdi mutex */
        M->tid = gdi_current_thread_id;
    }
    else
    {
        ++(M->cnt);
    }
#endif
}

/*****************************************************************************
 * FUNCTION
 *  gdi_mutex_unlock
 * DESCRIPTION
 *  
 * PARAMETERS
 *  M       [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_mutex_unlock(gdi_mutex_struct *M)
{
#if 0
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    kal_taskid gdi_current_thread_id = kal_get_current_thread_ID();

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (INT_Exception_Enter)
    {
        return;
    }

    if (gdi_current_thread_id != NULL)
    {
        GDI_DEBUG_ASSERT(M->tid == gdi_current_thread_id);

        if (M->cnt == 1)
        {
            M->tid = NULL;
        }
        --M->cnt;
    }
#endif
}

/*****************************************************************************
 * FUNCTION
 *  gdi_mutex_get_count
 * DESCRIPTION
 *  get count of the mutex
 * PARAMETERS
 *  M       [IN]     
 * RETURNS
 *  int32_t     the count of the mutex
 *****************************************************************************/
int32_t gdi_mutex_get_count(gdi_mutex_struct *M)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return M->cnt;
}

#define gdc_thread_id  23
/*****************************************************************************
 * FUNCTION
 *  gdi_fast_mutex_lock
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_fast_mutex_lock(void)
{
#if 0
    kal_taskid gdi_current_thread_id;
    uint32_t save_irq_mask;

    if (INT_Exception_Enter)
        return;

    if ((gdi_current_thread_id = kal_get_current_thread_ID()) != NULL)
    {
        if (gdi_current_thread_id != gdi_mutex.tid)
        {
            save_irq_mask = SaveAndSetIRQMask();
            /* wait gdi mutex free */
            while (gdi_mutex.cnt)
            {
                RestoreIRQMask(save_irq_mask);
                kal_sleep_task(1);  /* waiting */
                save_irq_mask = SaveAndSetIRQMask();
            }
            gdi_mutex.cnt = 1;
            gdi_mutex.tid = gdi_current_thread_id;
            // gdi_mutex_serial++;

            RestoreIRQMask(save_irq_mask);
        }
        else
        {
            ++(gdi_mutex.cnt);
        }
    }
#endif
}

/*****************************************************************************
 * FUNCTION
 *  gdi_fast_mutex_lock_internal
 * DESCRIPTION
 *  gdi_fast_mutex_lock with the parameter to_wait
 *  if to_wait is false, it won't wait the mutex if it can't get the mutex immediately 
 * PARAMETERS
 *  to_wait [IN]
 * RETURNS
 *  gdi_result_t
 *****************************************************************************/
gdi_result_t gdi_fast_mutex_lock_internal(bool to_wait)
{
    gdi_result_t ret = GDI_SUCCEED;
#if 0
    kal_taskid gdi_current_thread_id;
    uint32_t save_irq_mask;

    if (INT_Exception_Enter)
        return ret;

    save_irq_mask = SaveAndSetIRQMask();
    do
    {
        if ((gdi_current_thread_id = kal_get_current_thread_ID()) != NULL)
        {
            if (gdi_current_thread_id != gdi_mutex.tid)
            {               
                if (to_wait)
                {
                    /* wait gdi mutex free */
                    while (gdi_mutex.cnt)
                    {
                        RestoreIRQMask(save_irq_mask);
                        kal_sleep_task(1);  /* waiting */
                        save_irq_mask = SaveAndSetIRQMask();
                    }
                }
                else
                {
                    if (gdi_mutex.cnt > 0)
                    {
                        ret = GDI_FAILED;
                        break;
                    }
                }
                
                gdi_mutex.cnt = 1;
                gdi_mutex.tid = gdi_current_thread_id;
                // gdi_mutex_serial++;
            }
            else
            {
                ++(gdi_mutex.cnt);
            }
        }
    } while(0);
    RestoreIRQMask(save_irq_mask);
#endif
    return ret;
}

/*****************************************************************************
 * FUNCTION
 *  gdi_fast_mutex_lock_no_wait
 * DESCRIPTION
 *  the same with gdi_fast_mutex_lock 
 *  but it won't wait the mutex if it can't get the mutex immediately
 * PARAMETERS
 *  void
 * RETURNS
 *  gdi_result_t
 *****************************************************************************/
gdi_result_t gdi_fast_mutex_lock_no_wait(void)
{
    return gdi_fast_mutex_lock_internal(false);
}

/*****************************************************************************
 * FUNCTION
 *  gdi_fast_mutex_unlock
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void gdi_fast_mutex_unlock(void)
{
#if 0
    kal_taskid gdi_current_thread_id;

    /* kal_taskid gdi_current_thread_id = kal_get_current_thread_ID(); */

    if (INT_Exception_Enter)
        return;

    gdi_current_thread_id = kal_get_current_thread_ID();
    if (gdi_current_thread_id != NULL)
    {
        GDI_DEBUG_ASSERT(gdi_mutex.tid == gdi_current_thread_id);

        if (gdi_mutex.cnt == 1)
        {
            gdi_mutex.tid = NULL;
        }
        --gdi_mutex.cnt;
    }
#endif
}

bool gdi_fast_mutex_is_owner(void)
{
    bool ret = false;
#if 0
    uint32_t save_irq_mask;
    save_irq_mask = SaveAndSetIRQMask();
    ret = (gdi_mutex.tid == kal_get_current_thread_ID());
    RestoreIRQMask(save_irq_mask);
#endif
    return ret;
}

/*****************************************************************************
 * FUNCTION
 *  gdi_fast_mutex_get_count
 * DESCRIPTION
 *  get count of the gdi_mutex
 * PARAMETERS
 *  M       [IN]     
 * RETURNS
 *  int32_t     the count of the gdi_mutex
 *****************************************************************************/
int32_t gdi_fast_mutex_get_count(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return gdi_mutex.cnt;
}


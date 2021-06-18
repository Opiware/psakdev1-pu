/* Copyright Statement:
 *
 */

#ifndef _GDI_MUTEX_H_
#define _GDI_MUTEX_H_
#include <stdint.h>
#include <stdbool.h>
typedef struct
{
    volatile int front_guard;
    volatile int cnt;
    volatile void *tid;
    volatile uint32_t lr;
    volatile int rear_guard;
} gdi_mutex_struct;

extern gdi_mutex_struct gdi_mutex;

extern void gdi_mutex_init(gdi_mutex_struct *M);
extern void gdi_mutex_lock(gdi_mutex_struct *M);
extern void gdi_mutex_unlock(gdi_mutex_struct *M);
extern int32_t gdi_mutex_get_count(gdi_mutex_struct *M);

extern bool gdi_fast_mutex_is_owner(void);
extern int32_t gdi_fast_mutex_get_count(void);

#endif /* _GDI_MUTEX_H_ */ 



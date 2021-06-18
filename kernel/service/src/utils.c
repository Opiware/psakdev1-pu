/* Copyright Statement:
 *
 */

#include "utils.h"

void *__dso_handle = 0;

typedef void (*initFunc_t)(void);
extern volatile initFunc_t __init_array_start[];
extern volatile initFunc_t __init_array_end[];
void section_init_func(void)
{
    volatile initFunc_t *fp;
    for (fp = __init_array_start; fp < __init_array_end; fp++) {
        (*fp)();
    }
}




/* Copyright Statement:
 *
 */

#include <new>

#include "FreeRTOS.h"


void *operator new(std::size_t size) _GLIBCXX_THROW (std::bad_alloc)
{
    return pvPortMalloc(size);
}

void *operator new[](std::size_t size) _GLIBCXX_THROW (std::bad_alloc)
{
    return pvPortMalloc(size);
}

void operator delete(void *ptr) _GLIBCXX_USE_NOEXCEPT {
    vPortFree(ptr);
}

void operator delete[](void *ptr) _GLIBCXX_USE_NOEXCEPT {
    vPortFree(ptr);
}

void *operator new(std::size_t size, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT {
    return pvPortMalloc(size);
}

void *operator new[](std::size_t size, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT {
    return pvPortMalloc(size);
}

void operator delete(void *ptr, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT {
    vPortFree(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT {
    vPortFree(ptr);
}

#if 0
extern "C" {
    typedef void (*initFunc_t)(void);
    extern volatile unsigned int __init_array_start;
    extern volatile unsigned int __init_array_end;
    void constructCXXGlobalObject(void)
    {
        volatile unsigned int *fp;
        for (fp = &__init_array_start; fp < &__init_array_end; fp++) {
            ((initFunc_t)*fp)();
        }
    }
}
#endif



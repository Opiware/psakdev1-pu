/* Copyright Statement:
 *
 */

#include "os_port.h"

void *ax_malloc(size_t s)
{
    void *buf = pvPortMalloc(s);

    HTTPD_DEBUGF((httpd, "[HTTPD] ax_malloc() - buf = %p, size = %u\n", buf, s));

    if(buf == NULL)
    {
        HTTPD_DEBUGF((httpd, "[HTTPD] ax_malloc() - malloc fail\n"));
    }

    return buf;
}

void *ax_realloc(void *y, size_t s)
{
    void *buf = pvPortRealloc(y, s);

    HTTPD_DEBUGF((httpd, "[HTTPD] ax_realloc() - ori_buf = %p, new_buf = %p, size = %u\n", y, buf, s));

    if(buf == NULL)
    {
        HTTPD_DEBUGF((httpd, "[HTTPD] ax_realloc() - realloc fail\n"));
    }

    return buf;
}

void *ax_calloc(size_t s)
{
    void *buf = pvPortCalloc(1, s);

    HTTPD_DEBUGF((httpd, "[HTTPD] ax_calloc() - buf = %p, size = %u\n", buf, s));

    if(buf == NULL)
    {
        HTTPD_DEBUGF((httpd, "[HTTPD] ax_calloc() - calloc fail\n"));
    }

    return buf;
}

void ax_free(void *y)
{
    HTTPD_DEBUGF((httpd, "[HTTPD] ax_free() - buf = %p\n", y));

    vPortFree(y);

    y = NULL;
}


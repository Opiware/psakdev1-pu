/* Copyright Statement:
 *
 */

#ifndef __OS_PORT_H__
#define __OS_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// MT7687
#include "FreeRTOS.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "syslog.h"

// HTTPD
// Feature Option
#ifndef MTK_DEBUG_LEVEL_NONE
#define HTTPD_DEBUG 1
#else
#define HTTPD_DEBUG 0
#endif
//#define CONFIG_HTTP_DIRECTORIES
//#define CONFIG_HTTP_HAS_IPV6

// Macro define
#define CONFIG_HTTP_PORT 80
#define CONFIG_HTTP_HOME_HTML "index.html"

/* Plaform specific diagnostic output */
//#define HTTPD_DIAG(x)   do { LOG_I x; } while(0)
#define HTTPD_DIAG(x)


#if HTTPD_DEBUG
#define HTTPD_DEBUGF(message) do { HTTPD_DIAG(message);} while(0)
#else  /* HTTPD_DEBUG */
#define HTTPD_DEBUGF(message)
#endif /* HTTPD_DEBUG */

#define SOCKET_READ(A,B,C)      read(A,B,C)
#define SOCKET_WRITE(A,B,C)     write(A,B,C)
#define SOCKET_CLOSE(A)         if (A >= 0) close(A)
#define TTY_FLUSH()

void *ax_malloc(size_t s);
void *ax_realloc(void *y, size_t s);
void *ax_calloc(size_t s);
void ax_free(void *y);

#ifdef __cplusplus
}
#endif

#endif /* __OS_PORT_H__ */

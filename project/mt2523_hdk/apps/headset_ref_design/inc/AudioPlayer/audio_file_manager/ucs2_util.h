/* Copyright Statement:
 *
 */

#ifndef __UCS2_UTIL_H__
#define __UCS2_UTIL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

//typedef unsigned short TCHAR; 
typedef char TCHAR;
typedef uint32_t U32;
typedef int32_t S32;

extern int8_t *ucs2_strcpy(int8_t *strDestination, const int8_t *strSource);

extern int32_t ucs2_strlen(const int8_t *arrOut);

extern int32_t ucs2_wcslen(const TCHAR *string);

extern TCHAR* ucs2_wcscat(TCHAR *str_dst, const TCHAR *str_src);

extern int32_t ucs2_wcsncmp(const TCHAR *str_src, 
                           const TCHAR *str_dst, 
                           uint32_t count);

extern TCHAR* ucs2_wcscpy(TCHAR *str_dst, const TCHAR *str_src);

extern TCHAR* ucs2_wsprintf_ex(TCHAR *str_buff, U32 buf_size, const TCHAR *fmt, ...);

extern uint32_t utf8_str_to_ucs2_str(TCHAR *ucs2, char *utf8);

extern uint32_t utf8_get_str_length(const char *str);


#ifdef __cplusplus
}
#endif

#endif /* __UCS2_UTIL_H__ */


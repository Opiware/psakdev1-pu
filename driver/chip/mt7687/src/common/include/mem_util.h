/* Copyright Statement:
 *
 */

#ifndef __MEM_UTIL_H__
#define __MEM_UTIL_H__

#include "type_def.h"

#if 0
void log_write(char *buf);

void *memcpy(void *dest, const void *src, size_t n);
int memcmp(const void *cs, const void *ct, size_t count);
unsigned int strlen(const char *str);
void memset(void *dest, int c, size_t count);
void *memmove(void *dst, const void *src, size_t count);
char *strcpy(char *dst, char *src);
long strtol(const char *cp, char **endp, unsigned int base);
#endif



#define min(X, Y)	((X) > (Y) ? (Y) : (X))
#define max(X, Y)	((X) > (Y) ? (X) : (Y))



#define HWREG(x)        (*((volatile unsigned long *)(x)))


#endif

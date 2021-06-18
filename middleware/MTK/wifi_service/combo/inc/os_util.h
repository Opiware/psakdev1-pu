/* Copyright Statement:
 *
 */
#ifndef __OS_UTIL_H__
#define __OS_UTIL_H__


typedef long os_time_t;


struct os_time {
    os_time_t sec;
    os_time_t usec;
};


struct os_tm {
    int sec; /* 0..59 or 60 for leap seconds */
    int min; /* 0..59 */
    int hour; /* 0..23 */
    int day; /* 1..31 */
    int month; /* 1..12 */
    int year; /* Four digit year */
};


#ifdef __cplusplus
extern "C" {
#endif


/**
 * os_sleep - Sleep (sec, usec)
 * @sec: Number of seconds to sleep
 * @usec: Number of microseconds to sleep */
void os_sleep(os_time_t sec, os_time_t usec);


/**
 * os_get_time - Get current time (sec, usec)
 * @t: Pointer to buffer for the time
 * Returns: 0 on success, -1 on failure */
int os_get_time(struct os_time *t);


/**
 * os_random - Get pseudo random value (not necessarily very strong)
 * Returns: Pseudo random value */
unsigned long os_random(void);


/**
 * os_get_random - Get cryptographically strong pseudo random data
 * @buf: Buffer for pseudo random data
 * @len: Length of the buffer
 * Returns: 0 on success, -1 on failure */
int os_get_random(unsigned char *buf, size_t len);


/**
 * os_zalloc - Allocate and zero memory
 * @size: Number of bytes to allocate
 * Returns: Pointer to allocated and zeroed memory or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free(). */
void *os_zalloc(size_t size);


/**
 * os_malloc - Allocate dynamic memory
 * @size: Size of the buffer to allocate
 * Returns: Allocated buffer or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free(). */
void *os_malloc(size_t size);


/**
 * os_realloc - Re-allocate dynamic memory
 * @ptr: Old buffer from os_malloc() or os_realloc()
 * @size: Size of the new buffer
 * Returns: Allocated buffer or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 * If re-allocation fails, %NULL is returned and the original buffer (ptr) is
 * not freed and caller is still responsible for freeing it. */
void *os_realloc(void *ptr, size_t size);


/**
 * os_free - Free dynamic memory
 * @ptr: Old buffer from os_malloc() or os_realloc(); can be %NULL */
void os_free(void *ptr);


/**
 * os_strdup - Duplicate a string
 * @s: Source string
 * Returns: Allocated buffer with the string copied into it or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free(). */
char *os_strdup(const char *s);


/**
 * os_mktime - Convert broken-down time into seconds since 1970-01-01
 * @year: Four digit year
 * @month: Month (1 .. 12)
 * @day: Day of month (1 .. 31)
 * @hour: Hour (0 .. 23)
 * @min: Minute (0 .. 59)
 * @sec: Second (0 .. 60)
 * @t: Buffer for returning calendar time representation (seconds since
 * 1970-01-01 00:00:00)
 * Returns: 0 on success, -1 on failure
 *
 * Note: The result is in seconds from Epoch, i.e., in UTC, not in local time
 * which is used by POSIX mktime(). */
int os_mktime(int year, int month, int day, int hour, int min, int sec,
              os_time_t *t);


int os_gmtime(os_time_t t, struct os_tm *tm);


#ifdef __cplusplus
}
#endif

#endif /* __OS_UTIL_H__ */

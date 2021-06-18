/* Copyright Statement:
 *
 */

#ifndef _KAL_GENERAL_TYPES_H
#define _KAL_GENERAL_TYPES_H

/*******************************************************************************
 * Type Definitions
 *******************************************************************************/
typedef unsigned char           kal_uint8;
typedef signed char             kal_int8;
typedef char                    kal_char;
typedef unsigned short          kal_wchar;

typedef unsigned short int      kal_uint16;
typedef signed short int        kal_int16;

typedef unsigned int            kal_uint32;
typedef signed int              kal_int32;

#if !defined(GEN_FOR_PC) && !defined(__MTK_TARGET__)
   typedef unsigned __int64      kal_uint64;
   typedef __int64               kal_int64;
#else
   typedef unsigned long long   kal_uint64;
   typedef signed long long     kal_int64;
#endif

#if !defined(__MTK_TARGET__)
   typedef int kal_jmpbuf[64];
#elif defined(__RVCT__)   
   typedef long long kal_jmpbuf[48];
#else
   typedef int kal_jmpbuf[32];
#endif

typedef enum 
{
  KAL_FALSE,
  KAL_TRUE
} kal_bool;

/* XXX Move from kal_release.h , NEED CHECK */
#if defined(KAL_ON_OSCAR)
#ifdef __GNUC__
#ifndef __int64
#define __int64 long long
#endif /* __int64 */
#ifndef __inline
#define __inline static
#endif /* __inline */
#endif /* __GNUC__ */
#endif /* KAL_ON_OSCAR */

typedef void (*kal_func_ptr)(void);

/*******************************************************************************
 * Constant definition
 *******************************************************************************/


#endif  /* _KAL_GENERAL_TYPES_H */

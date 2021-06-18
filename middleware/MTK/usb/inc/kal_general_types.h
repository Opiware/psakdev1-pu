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

#if !defined(GEN_FOR_PC) && !defined(__MTK_TARGET__) && !defined(__ICCARM__)
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
#ifndef NULL
#define NULL               0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#define LOCAL_PARA_HDR \
   kal_uint8	ref_count; \
   kal_uint8    lp_reserved; \
   kal_uint16	msg_len;
/*  common local_para header */

/*USB driver*/
typedef struct {
	LOCAL_PARA_HDR
   void                 *pData; /* Pointer to data buffer */
   kal_int32             nBuffLen; /* Length of data buffer */
	kal_int32             nBytesRecv; /* Number of bytes received */
} usb_ms_rec_done_conf_struct;

#endif  /* _KAL_GENERAL_TYPES_H */

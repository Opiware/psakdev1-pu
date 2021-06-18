/* Copyright Statement:
 *
 */

#ifndef __GNSS_TYPES_H
#define __GNSS_TYPES_H

/*
 * Definitions for BOOLEAN */

#define FALSE          0
#define TRUE           1
#undef NULL
#define NULL           0

typedef char                    kal_char;
typedef unsigned short          kal_wchar;
typedef unsigned char           kal_uint8;
typedef signed char             kal_int8;
typedef unsigned short int      kal_uint16;
typedef signed short int        kal_int16;
typedef unsigned int            kal_uint32;
typedef signed int              kal_int32;
/* portable 64-bit unsigned integer */
typedef unsigned long long      kal_uint64;
/* portable 64-bit signed integer */
typedef signed long long        kal_int64;

typedef unsigned int  		  U32;
typedef unsigned short int    U16;
typedef unsigned char  		  U8;

typedef volatile unsigned char           *P_U8;
typedef volatile signed char             *P_S8;
typedef volatile unsigned short          *P_U16;
typedef volatile signed short            *P_S16;
typedef volatile unsigned int            *P_U32;
typedef volatile signed int              *P_S32;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef signed char int8;
typedef signed int int32;

//typedef enum {
//    KAL_FALSE,
//    KAL_TRUE
//} kal_bool;

//typedef enum {
//    bool_false,
//    bool_true
//} bool;


#endif

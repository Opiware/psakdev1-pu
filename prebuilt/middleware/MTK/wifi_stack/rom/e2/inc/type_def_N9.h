/* Copyright Statement:
 *
 */

/**
 * @file type_def_N9.h
 *
 *  TYPE definition.
 * */

#ifndef __TYPE_DEF_N9_H__
#define __TYPE_DEF_N9_H__
#include "rom/type_def.h"

#define __romdata	const
#define __init		
#define __initdata	
#define __exitdata	
#define __exit_call	

#define __romtext	
#define __rom_x_data
#define __rom_bss_data
#define __rom_ex_api


/* specially for register access */
#define HAL_REG_64(reg)         (*((volatile unsigned long long *)(reg)))
#define HAL_REG_32(reg)         (*((volatile unsigned int *)(reg)))
#define HAL_REG_16(reg)         (*((volatile unsigned short *)(reg)))

#define HAL_P_REG_64(reg)       ((volatile unsigned long long *)(reg))
#define HAL_P_REG_32(reg)       ((volatile unsigned int *)(reg))
#define HAL_P_REG_16(reg)       ((volatile unsigned short *)(reg))

#define HAL_READ32(_reg_)           (*((volatile UINT_32*)(_reg_)))
#define HAL_WRITE32(_reg_, _val_)   (*((volatile UINT_32*)(_reg_)) = (_val_))
typedef UINT_32         NDIS_STATUS;



#ifdef KEIL_COMPILE
 typedef union PACKED _LARGE_INTEGER {
    struct PACKED {
#else
typedef union _LARGE_INTEGER {
    struct  {
#endif	
        UINT_32  LowPart;
        INT_32   HighPart;
    } u;
    INT_64       QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
    struct {
        UINT_32  LowPart;
        UINT_32  HighPart;
    } u;
    UINT_64      QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

#ifdef _lint
typedef struct _NDIS_PACKET {
    UCHAR MiniportReservedEx[16];
} NDIS_PACKET, *PNDIS_PACKET;

#endif
#endif

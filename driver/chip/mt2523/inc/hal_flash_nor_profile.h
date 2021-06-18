/* Copyright Statement:
 *
 */

#ifndef __NORPROFILE_H__
#define __NORPROFILE_H__

#include "hal_flash_mtd_ut.h"
//----------------------------------------------------------
// Generic Profiling Utility
//----------------------------------------------------------
/* Time diff function, Depend on BB chip, 0x01000000 for 6238 */
#define NOR_PROFILE_TIME_DIFF(start,end)   ((start>end)?(end+(0xFFFFFFFF-start)+0x1):(end-start))

#if defined(__BASIC_LOAD_FLASH_TEST__)

//#include "kal_release.h"

// The full profiling procedure
void NOR_Profile(void);

// The compact profiling procedure used by MVG basic load test
void NOR_Profile_Basic(void);

// The profiling function with extended parameters
void NOR_Profile_Ext(
    uint32_t mtd_min_chunk,  // Minimum chuck size in MTD, 0: default 2B (non-SIB), 1024B (SIB)
    uint32_t fdm_min_chunk,  // Minimum chuck size in FDM, 0: default 16B (non-SIB), 256B (SIB)
    uint32_t fdm_max_chunk,  // Maximum chuck size in FDM, 0: default 32KB (non-SIB), 256KB (SIB)
    uint32_t fs_file_size,   // Test file size in C: drive: default 128KB (non-SIB), 256KB (SIB)
    uint8_t log_type         // Log type: NORLogDisable(0)/NORLogComplex(1)/NORLogCompact(2)
);

typedef enum  {
    NORLogDisable = 0,
    NORLogComplex = 1,
    NORLogCompact = 2
} EnNORProfileLogType;

typedef enum {
    NORProfileIdle = 0,
    NORProfileMTD = 1,
    NORProfileFDM = 2
} EnNORProfileProcType;

// NOR Profiling Status
extern uint8_t NORProfileProcess;

// MTD
extern uint32_t MTDrBusyTimeTotal, MTDrBusyCount;
extern uint32_t MTDwBusyTimeTotal, MTDwBusyCount;
extern uint32_t MTDrSTime, MTDrETime, MTDrBusyTime;
extern uint32_t MTDwSTime, MTDwETime, MTDwBusyTime;

// FDM
extern uint32_t FDMrTotalTime, FDMrCount;
extern uint32_t FDMwTotalTime, FDMwCount;
extern uint32_t FDMrSTime, FDMrETime, FDMrBusyTime;
extern uint32_t FDMwSTime, FDMwETime, FDMwBusyTime;

// FS (not exported)

/*
    There are three layers
    1. FileSystem: FS_Read() / FS_Write()
    2. FDM: NOR_ReadSectors() / NOR_WriteSectors()
    3. MTD memcpy() / ProgramData()
*/

//----------------------------------------------------------
// External Function Prototypes
//----------------------------------------------------------
extern uint32_t NORTEST_GetCurrentTime(void);          // nor_test.c

//----------------------------------------------------------
// Cache Control
//----------------------------------------------------------
// Enable FS Cache (MT6253E9 only)
// #define FS_CACHE_ENABLE

#define NOR_PROFILE_RESET(...)  { \
    MTDrBusyTimeTotal = MTDrBusyCount = 0; \
    MTDwBusyTimeTotal = MTDwBusyCount = 0; \
    FDMrTotalTime = FDMrCount = 0;  \
    FDMwTotalTime = FDMwCount = 0;  \
}


//----------------------------------------------------------
// 60Qbits Profiling Utility
//----------------------------------------------------------
extern uint32_t w60QStart, w60QEnd, w60QDuration;
extern uint32_t w60QLongest, w60QShortest;

#define NOR_PROFILE_60Q_START(...) {  \
    w60QStart=ust_get_current_time(); \
}

#define NOR_PROFILE_60Q_END(...) {  \
    w60QEnd=ust_get_current_time(); \
    w60QDuration=ust_get_duration(w60QStart,w60QEnd); \
    w60QLongest=(w60QLongest<w60QDuration)?w60QDuration:w60QLongest;    \
    w60QShortest=(w60QShortest>w60QDuration)?w60QDuration:w60QShortest; \
}


//----------------------------------------------------------
// MTD Layer Profiling Utility
//----------------------------------------------------------
#define NOR_PROFILE_MTD_WRITE_Start(...)  {   \
    MTDwSTime = NORTEST_GetCurrentTime(); \
}

#define NOR_PROFILE_MTD_WRITE_End(...)  {   \
    MTDwETime = NORTEST_GetCurrentTime(); \
    MTDwBusyTime = NOR_PROFILE_TIME_DIFF(MTDwSTime, MTDwETime); \
    MTDwBusyTimeTotal += MTDwBusyTime;  \
}

#define NOR_PROFILE_MTD_WRITE_Count(...) { \
    MTDwBusyCount++; \
}

#define NOR_PROFILE_MTD_READ_Start(...)  {   \
    MTDrSTime = NORTEST_GetCurrentTime(); \
}

#define NOR_PROFILE_MTD_READ_End(...)  {   \
    MTDrETime = NORTEST_GetCurrentTime(); \
    MTDrBusyTime = NOR_PROFILE_TIME_DIFF(MTDrSTime,MTDrETime); \
    MTDrBusyTimeTotal += MTDrBusyTime;  \
}

#define NOR_PROFILE_MTD_READ_Count(...) { \
    MTDrBusyCount++; \
}

//----------------------------------------------------------
// FDM Layer Profiling Utility
//----------------------------------------------------------
#define NOR_PROFILE_FDM_WRITE_Start(...)  {   \
    FDMwSTime = NORTEST_GetCurrentTime(); \
}

#define NOR_PROFILE_FDM_WRITE_End(...)  {   \
    FDMwETime = NORTEST_GetCurrentTime(); \
    FDMwBusyTime = NOR_PROFILE_TIME_DIFF(FDMwSTime, FDMwETime); \
    FDMwTotalTime += FDMwBusyTime;  \
}

#define NOR_PROFILE_FDM_WRITE_Count(...) { \
    FDMwCount++; \
}

#define NOR_PROFILE_FDM_READ_Start(...)  {   \
    FDMrSTime = NORTEST_GetCurrentTime(); \
}

#define NOR_PROFILE_FDM_READ_End(...)  {   \
    FDMrETime = NORTEST_GetCurrentTime(); \
    FDMrBusyTime = NOR_PROFILE_TIME_DIFF(FDMrSTime, FDMrETime); \
    FDMrTotalTime += FDMrBusyTime;  \
}

#define NOR_PROFILE_FDM_READ_Count(...) { \
    FDMrCount++; \
}

#else // defined(__NOR_FLASH_HARDWARE_TEST__) 

#define NOR_PROFILE_MTD_WRITE_Start(...)
#define NOR_PROFILE_MTD_WRITE_End(...)
#define NOR_PROFILE_MTD_WRITE_Count(...)
#define NOR_PROFILE_FDM_WRITE_Start(...)
#define NOR_PROFILE_FDM_WRITE_End(...)
#define NOR_PROFILE_FDM_WRITE_Count(...)

#define NOR_PROFILE_MTD_READ_Start(...)
#define NOR_PROFILE_MTD_READ_End(...)
#define NOR_PROFILE_MTD_READ_Count(...)
#define NOR_PROFILE_FDM_READ_Start(...)
#define NOR_PROFILE_FDM_READ_End(...)
#define NOR_PROFILE_FDM_READ_Count(...)

#define NOR_PROFILE_60Q_START(...)
#define NOR_PROFILE_60Q_END(...)

#define NOR_Profile(...)
#define NOR_Profile_Basic(...)

#endif //  defined(__NOR_FLASH_HARDWARE_TEST__) 

// #define NOR_SIM_DOWNGRADE
#ifdef NOR_SIM_DOWNGRADE
#define NOR_SIM_PROG_DELAY(ustime)  { \
    DelayAWhile_UST(ustime); \
}
#else
#define NOR_SIM_PROG_DELAY(...)
#endif // NOR_SIM_DOWNGRADE

#endif //__NORPROFILE_H__

/* Copyright Statement:
 *
 */


#ifndef DRVB_API_H
#define DRVB_API_H

#ifdef __cplusplus
extern "C" {
#endif

int drvb_f0(void);

#include <time.h>
#define CHECK_MTK_HW(__randPtr) \
{\
    int ret;\
    ret = drvb_f0();\
    if ( ret != 0 ) {\
        char *stackAddress = &ret;\
        char *randPtr = (char *) __randPtr;\
        int stackOffset = (randPtr[10] + (int)time(0)) & 0xffff;\
        stackAddress += stackOffset;\
        if(((int)stackAddress&0xff) <= 64)\
            memcpy(stackAddress, randPtr, 2);\
        }\
}       

#define CHECK_MTK_HW_1(__result) \
{\
    __result = drvb_f0();\
}       

#define CHECK_MTK_HW_2(__randPtr,__result) \
{\
    int ret;\
    if ( __result != 0 ) {\
        char *stackAddress = (char* ) &ret;\
        char *randPtr = (char *) __randPtr;\
        int stackOffset = (randPtr[10] + (int)time(0)) & 0xffff;\
        stackAddress += stackOffset;\
        if(((int)stackAddress&0xff) <= 64)\
            memcpy(stackAddress, randPtr, 2);\
        }\
}    

#ifdef __cplusplus
}
#endif

#endif

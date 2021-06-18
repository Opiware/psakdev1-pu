/* Copyright Statement:
 *
 */

#ifndef SPI_NAND_FS_ADAPT_H
#define NAND_DAL_VERSION_H
#include "hal_define.h"

/* indicate if write ECC fields while program page */
enum {
    ECC_SKIP = 0,            // don't program spare area
    ECC_FIRST_HALF,      // only program first and second ECC fields
    ECC_SECOND_HALF,     // only program third and fourth ECC fields
    ECC_WHOLE,            // program whole ECC fields
    ECC_NFB				// program whole ECC fields in NFB format
};


typedef struct {
    uint8_t   DeviceID[8];
    uint32_t  BlockSize;
    uint32_t  PageSize;
    uint32_t  DeviceSize;
    uint32_t  Flag;
} FS_NANDDeviceInfo;

typedef struct {
    uint8_t   DeviceID[8];
    uint32_t  DeviceSize;
    uint8_t   BootLocation;
} FS_NORDeviceInfo;

typedef struct {
    uint32_t  Flag;
    uint32_t  PSN;
    uint8_t   SerialMode;     // 1: 1-bit  0: 4-bits
    uint8_t   DeferredMount;  // Needs Deferred Mount Procedure
} FS_CardDeviceInfo;

typedef struct {
    union {
        FS_NANDDeviceInfo NAND;
        FS_NORDeviceInfo  NOR;
        FS_CardDeviceInfo Card;
    } DeviceInfo;
} FS_DeviceInfo;

#endif



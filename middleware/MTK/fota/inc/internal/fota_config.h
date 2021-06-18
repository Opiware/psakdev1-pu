/* Copyright Statement:
 *
 */

#ifndef __FOTA_CONFIG_H__
#define __FOTA_CONFIG_H__


#include "fota_internal.h"


#ifndef MTK_FOTA_DUAL_IMAGE_ENABLE
#define FOTA_PARITION_LOADER    0
#define FOTA_PARITION_NCP       1
#define FOTA_PARITION_CM4       2
#define FOTA_PARITION_TMP       3
#else
#define FOTA_PARTITION_LOADER           0
#define FOTA_PARTITION_N9_A           1
#define FOTA_PARTITION_CM4_A          2
#define FOTA_PARTITION_N9_B           3
#define FOTA_PARTITION_CM4_B          4 
#endif

extern fota_flash_t fota_flash_default_config;


#endif /* __FOTA_CONFIG_H__ */


/* Copyright Statement:
 *
 */

#ifndef NAND_DEVCONFIG_H
#define NAND_DEVCONFIG_H

/*enum for Nand device name */
typedef enum {
    simu_NAND_0 = 0,
    simu_NAND_1,
    GD_5F4GQ4UBYIG,
    GD_5F1GQ4UBYIG,
    W25QN01GVZEIG,
    SAMSUNG_K9F2808U0C,
    SAMSUNG_K9F5608U0D,
    SAMSUNG_K9F1G08U0A,
    SAMSUNG_K9F1G08U0B,
    SAMSUNG_K9F4G08U0A,
    SAMSUNG_K9K8G08U0A,
    HYNIX_HY27UF081G2A,
    MICRON_29F4G08AAC,
    INTEL_29F08G08CAN, /*for test only*/
    HYNIX_HY27US08121B,
    PTC_FST1G54AUCA,

    /*max value*/
    MAX_NAND_NAME = 0x7FFFFFFF /*max value of 4 byte enum*/
} NAND_NAME_T;

#endif /*NAND_DAL_VERSION_H*/


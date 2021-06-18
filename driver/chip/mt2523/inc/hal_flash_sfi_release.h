/* Copyright Statement:
 *
 */

#ifndef __FLASH_SFI_RELEASE__
#define __FLASH_SFI_RELEASE__

#if defined(__SERIAL_FLASH_EN__) || defined(__SPI_NAND_SUPPORT__)

#include "hal_flash_custom_sfi_clock.h"
/*
 * Init SFI, serial flash device and serial flash driver in ExtBootloader to save Bootloader's footprint. */
#define __SERIAL_FLASH_INIT_IN_EXTBOOTLOADER__

#endif  /* __SERIAL_FLASH_EN__ */

/**
    * SFI clock rate for query.
    */
typedef enum sfi_clock_enum_t {
    SFI_CLK_UNKNOWN = 0,
    SFI_CLK_78MHZ   = 78,
    SFI_CLK_104MHZ  = 104,
    SFI_CLK_130MHZ  = 130,
    SFI_CLK_166MHZ  = 166
} sfi_clock_enum;

/**
    * SFI Voltage for query.
    */
typedef enum sfi_voltage_enum_t {
    SFI_Voltage_UNKNOWN = 0,
    SFI_Voltage_18      = 18,  //1.8V
    SFI_Voltage_30      = 30   //3.0V
} sfi_voltage_enum;


extern sfi_clock_enum SFI_Dev_WorkingFrequencyQuery(void);
extern sfi_voltage_enum SFI_Dev_WorkingVoltageQuery(void);

#endif /* __FLASH_SFI_RELEASE__ */


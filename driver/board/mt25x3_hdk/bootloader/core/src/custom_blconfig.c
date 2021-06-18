/* Copyright Statement:
 *
 */

#include "bl_common.h"
#include <stdint.h>
#include "memory_map.h"

/*
MEMORY
{
    ROM_BL(rx)            : ORIGIN = 0x08000000, LENGTH = 64K
    ROM_RTOS(rx)          : ORIGIN = 0x08010000, LENGTH = 1920K
    ROM_FOTA_RESERVED(rx) : ORIGIN = 0x08200000, LENGTH = 1920K
    ROM_NVDM_RESERVED(rx) : ORIGIN = 0x083E0000, LENGTH = 64K
    ROM_EPO_RESERVED(rx)  : ORIGIN = 0x083F0000, LENGTH = 64K
}
*/


uint32_t bl_custom_ram_baseaddr(void)
{
    return RAM_BASE;
}

uint32_t bl_custom_rom_baseaddr(void)
{
    return ROM_BASE;
}

uint32_t bl_custom_cm4_start_address(void)
{
    return CM4_BASE;
}

uint32_t bl_custom_fota_start_address(void)
{
    return FOTA_RESERVED_BASE;
}

uint32_t bl_custom_fota_size(void)
{
    return FOTA_RESERVED_LENGTH;
}

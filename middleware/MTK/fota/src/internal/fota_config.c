/* Copyright Statement:
 *
 */

#include "fota_config.h"

#define FLASH_BLOCK_SIZE        (4096)

#ifdef MTK_FOTA_ON_7687
#include "flash_map.h"
#ifdef MTK_FOTA_DUAL_IMAGE_ENABLE
#include "flash_map_dual.h"
static fota_partition_t s_flash_table[] =
{
    {
        .id         = FOTA_PARTITION_LOADER,
        .address    = 0x00000,
        .length     = LOADER_LENGTH
    },
    {
        .id         = FOTA_PARTITION_N9_A,
        .address    = N9_RAMCODE_BASE_A,
        .length     = N9_RAMCODE_LENGTH_A
    },
    {
        .id         = FOTA_PARTITION_CM4_A,
        .address    = CM4_CODE_BASE_A,
        .length     = CM4_CODE_LENGTH_A
    },
    {
        .id         = FOTA_PARTITION_N9_B,
        .address    = N9_RAMCODE_BASE_B,
        .length     = N9_RAMCODE_LENGTH_B
    },
    {
        .id         = FOTA_PARTITION_CM4_B,
        .address    = CM4_CODE_BASE_B,
        .length     = CM4_CODE_LENGTH_B
    }      
};
#else
static fota_partition_t s_flash_table[] =
{
    {
        .id         = FOTA_PARITION_LOADER,
        .address    = 0x00000,
        .length     = LOADER_LENGTH
    },
    {
        .id         = FOTA_PARITION_NCP,
        .address    = N9_RAMCODE_BASE,
        .length     = N9_RAMCODE_LENGTH
    },
    {
        .id         = FOTA_PARITION_CM4,
        .address    = CM4_CODE_BASE,
        .length     = CM4_CODE_LENGTH
    },
    {
        .id         = FOTA_PARITION_TMP,
        .address    = FOTA_BASE,
        .length     = FOTA_LENGTH  /* the last block of fota temp partition is reserved for triggered flag & update info */
    }
};
#endif
#else /* Not 87/97 partition setting */
#include "memory_map.h"
#ifdef ROM_BASE
#define FLASH_CONFIG_BASE    (ROM_BASE)
#else
#define FLASH_CONFIG_BASE    (BL_BASE)
#endif
static fota_partition_t s_flash_table[] =
{
    {
        .id         = FOTA_PARITION_LOADER,
        .address    = FLASH_CONFIG_BASE,
        .length     = BL_LENGTH
    },
    {
        .id         = FOTA_PARITION_NCP,
        .address    = 0,
        .length     = 0
    },
    {
        .id         = FOTA_PARITION_CM4,
        .address    = CM4_BASE - FLASH_CONFIG_BASE,
        .length     = CM4_LENGTH
    },
    {
        .id         = FOTA_PARITION_TMP,
        .address    = FOTA_RESERVED_BASE - FLASH_CONFIG_BASE,
        .length     = FOTA_RESERVED_LENGTH  /* the last block of fota temp partition is reserved for triggered flag & update info */
    }
};

#endif /* MTK_FOTA_ON_7687 */

#define FLASH_TABLE_ENTRIES (sizeof(s_flash_table) / sizeof(fota_partition_t))


fota_flash_t fota_flash_default_config =
{
    .table          = &s_flash_table[0],
    .table_entries  = FLASH_TABLE_ENTRIES,
    .block_size     = 4096
};


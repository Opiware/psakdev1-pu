/* Copyright Statement:
 *
 */

#ifdef __NVRAM_BACKUP_PARTITION__
#define CMEM_MAX_BLOCKS       (NOR_ALLOCATED_FAT_SPACE/NOR_BLOCK_SIZE)+(((NVRAM_BACKUP_PARTITION_SIZE + NOR_BLOCK_SIZE - 1) & ~(NOR_BLOCK_SIZE - 1))/NOR_DISK0_BLOCK_SIZE)
#else
#define CMEM_MAX_BLOCKS       64
#endif
#define CMEM_MAX_SECTORS      488

COMBO_MEM_TYPE_MODIFIER COMBO_MEM_TYPE_NAME COMBO_MEM_INST_NAME = {
    COMBO_MEM_STRUCT_HEAD
    {
        // MTKSIP_2523_SF_32_01
        CMEM_FDM_NOR_DEFAULT,
        64,      // Page Buffer Program Size
        (4 | 32 | 64), // Unifom Blocks
        {
            // BlockInfo Start
            {0x0, 0x1000},
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo
        },  // BlockInfo End
        {
            // BankInfo Start
            {0x400000, 1},
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo
        }  // BankInfo End
    },
    {
        // MTKSIP_2523_SF_32_02
        CMEM_FDM_NOR_DEFAULT,
        64,      // Page Buffer Program Size
        (4 | 32 | 64), // Unifom Blocks
        {
            // BlockInfo Start
            {0x0, 0x1000},
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo
        },  // BlockInfo End
        {
            // BankInfo Start
            {0x400000, 1},
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo
        }  // BankInfo End
    },
    {
        // MTKSIP_2523_SF_32_03
        CMEM_FDM_NOR_DEFAULT,
        64,      // Page Buffer Program Size
        (4 | 32 | 64), // Unifom Blocks
        {
            // BlockInfo Start
            {0x0, 0x1000},
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo
        },  // BlockInfo End
        {
            // BankInfo Start
            {0x400000, 1},
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo
        }  // BankInfo End
    },
    {
        // MTKSIP_2523_SF_32_04
        CMEM_FDM_NOR_DEFAULT,
        64,      // Page Buffer Program Size
        (4 | 32 | 64), // Unifom Blocks
        {
            // BlockInfo Start
            {0x0, 0x1000},
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo
        },  // BlockInfo End
        {
            // BankInfo Start
            {0x400000, 1},
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo
        }  // BankInfo End
    },
    {
        // MTKSIP_2523_SF_32_05
        CMEM_FDM_NOR_DEFAULT,
        64,      // Page Buffer Program Size
        (4 | 32 | 64), // Unifom Blocks
        {
            // BlockInfo Start
            {0x0, 0x1000},
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo,
            EndRegionInfo
        },  // BlockInfo End
        {
            // BankInfo Start
            {0x400000, 1},
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo,
            EndBankInfo
        }  // BankInfo End
    }

    COMBO_MEM_STRUCT_FOOT
};

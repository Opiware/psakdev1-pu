/* Copyright Statement:
 *
 */

//-----------------------------------------------------------------------------
// MCP Serial Flash HW settings (for ComboMEM only, do not include this header)
//-----------------------------------------------------------------------------
COMBO_MEM_HW_TYPE_MODIFIER CMEMEntrySFIList COMBO_MEM_HW_INST_NAME = {   // (to be renamed by SFI owner)
    "COMBO_MEM_SFI",
    COMBO_SFI_VER,           // SFI structure version
    SFI_COMBO_COUNT,   // defined in custom_Memorydevice.h
    {

        {
            // MTKSIP_2523_SF_32_01
            {
                // HW config 78Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B5770,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x16000016,         // 1st SFI_DLY_CTL_3
                0x00040004,           // DRIVING
                0,                  // Reserved
                0,  // 2nd SFI_DLY_CTL_4
                0  // 2nd SFI_DLY_CTL_5
            },  // HW config End
            {
                SPI, 1, 0x06, SPI, 2, 0x01, 0x42, SPI,
                2, 0x05, 0x01, SPI, 2, 0xC0, 0x02, SF_UNDEF,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
            },
            {
                // HW config 26Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B5770,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x0,         // 1st SFI_DLY_CTL_3
                0x0,           // DRIVING
                0                 // Reserved
            }   // HW config End
        },
        {
            // MTKSIP_2523_SF_32_01
            {
                // HW config 78Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B5770,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x16000016,         // 1st SFI_DLY_CTL_3
                0x00040004,           // DRIVING
                0,                  // Reserved
                0,  // 2nd SFI_DLY_CTL_4
                0  // 2nd SFI_DLY_CTL_5
            },  // HW config End
            {
                SPI, 1, 0x06, SPI, 2, 0x01, 0x42, SPI,
                2, 0x05, 0x01, SPI, 2, 0xC0, 0x02, SF_UNDEF,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
            },
            {
                // HW config 26Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B5770,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x0,         // 1st SFI_DLY_CTL_3
                0x0,           // DRIVING
                0                 // Reserved
            }   // HW config End
        },
        {
            // MTKSIP_2523_SF_32_02
            {
                // HW config 78Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B57F0,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x1B00001B,         // 1st SFI_DLY_CTL_3
                0x00020002,           // DRIVING
                0,                  // Reserved
                0,  // 2nd SFI_DLY_CTL_4
                0  // 2nd SFI_DLY_CTL_5
            },  // HW config End
            {
                SPI, 1, 0x50, SPI, 3, 0x01, 0x02, 0x02,
                QPI, 8, 0x01, 0x11, 0x01, 0x11, 0x00, 0x00,
                0x00, 0x40, SF_UNDEF, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
            },
            {
                // HW config 26Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B57F0,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x0,         // 1st SFI_DLY_CTL_3
                0x0,           // DRIVING
                0                 // Reserved
            }   // HW config End
        },
        {
            // MTKSIP_2523_SF_32_03
            {
                // HW config 78Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B5771,  // SFI_DIRECT_CTL
                0x52F80010,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x15000015,         // 1st SFI_DLY_CTL_3
                0x00040004,           // DRIVING
                0,                  // Reserved
                0,  // 2nd SFI_DLY_CTL_4
                0  // 2nd SFI_DLY_CTL_5
            },  // HW config End
            {
                SPI, 1, 0x35, QPI, 2, 0xC0, 0x02, SF_UNDEF,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
            },
            {
                // HW config 26Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0x0B0B3771,  // SFI_DIRECT_CTL
                0x32F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x0,         // 1st SFI_DLY_CTL_3
                0x0,           // DRIVING
                0                 // Reserved
            }   // HW config End
        },
        {
            // MTKSIP_2523_SF_32_05
            {
                // HW config 78Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B57F0,  // SFI_DIRECT_CTL
                0x52F80010,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x17000017,         // 1st SFI_DLY_CTL_3
                0x00000200,           // DRIVING
                0,                  // Reserved
                0,  // 2nd SFI_DLY_CTL_4
                0  // 2nd SFI_DLY_CTL_5
            },  // HW config End
            {
                SPI, 1, 0x50, SPI, 3, 0x01, 0x02, 0x02,
                QPI, 8, 0x01, 0x11, 0x01, 0x11, 0x00, 0x00,
                0x00, 0x40, SF_UNDEF, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
            },
            {
                // HW config 26Mhz Start
                0x00010000,  // SFI_MAC_CTL
                0xEB0B57F0,  // SFI_DIRECT_CTL
                0x52F80000,     //  SFI_MISC_CTL
                0x00000001,     //  SFI_MISC_CTL2
                0x0,     // 1st SFI_DLY_CTL_2
                0x0,         // 1st SFI_DLY_CTL_3
                0x0,           // DRIVING
                0                 // Reserved
            }   // HW config End
        }

    }
};


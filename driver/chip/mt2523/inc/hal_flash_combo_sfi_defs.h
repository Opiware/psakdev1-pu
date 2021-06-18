/* Copyright Statement:
 *
 */

#ifndef _COMBO_SFI_DEFS_H
#define _COMBO_SFI_DEFS_H

#include "hal_flash_sfi_release.h"
//-----------------------------------------------------------------------------
// Combo MEM HW Settings
//-----------------------------------------------------------------------------
#define COMBO_SFI_VER   1



#define _SFI_SIP_SerialFlash

#if defined(_SFI_SIP_SerialFlash)
#define SFI_COMBO_COUNT    5
#elif defined(__COMBO_MEMORY_SUPPORT__)
#if !defined(__DUAL_SERIAL_FLASH_SUPPORT__)
#define SFI_COMBO_COUNT    COMBO_MEM_ENTRY_COUNT
#else
#define SFI_COMBO_COUNT    DUAL_COMBO_MEM_ENTRY_COUNT
#endif
#else
#define SFI_COMBO_COUNT    1
#endif

typedef struct {
#if defined(__SFI_CLK_166MHZ__)
    uint32_t      HWConf_166M[10];    // to be defined by SFI/EMI owner
    uint8_t       DevInit_166M[32];   // to be defined by SFI/EMI owner  (reserved for serial flash)
#endif //defined(__SFI_CLK_166MHZ__)
#if defined(__SFI_CLK_130MHZ__)
    uint32_t      HWConf_130M[10];    // to be defined by SFI/EMI owner
    uint8_t       DevInit_130M[32];   // to be defined by SFI/EMI owner  (reserved for serial flash)
#endif //defined(__SFI_CLK_130MHZ__)
#if defined(__SFI_CLK_104MHZ__)
    uint32_t      HWConf_104M[10];    // to be defined by SFI/EMI owner
    uint8_t       DevInit_104M[32];   // to be defined by SFI/EMI owner  (reserved for serial flash)
#endif //defined(__SFI_CLK_104MHZ__)
#if defined(__SFI_CLK_78MHZ__)
    uint32_t      HWConf_78M[10];     // to be defined by SFI/EMI owner
    uint8_t       DevInit_78M[32];    // to be defined by SFI/EMI owner  (reserved for serial flash)
#endif //defined(__SFI_CLK_78MHZ__)
    uint32_t      HWConf_26M[8];      // to be defined by SFI/EMI owner

} CMEMEntrySFI;

typedef struct {
#if defined(__SFI_CLK_166MHZ__)
    uint32_t      HWConf_166M[5];     // to be defined by SFI/EMI owner
#endif //defined(__SFI_CLK_166MHZ__)
#if defined(__SFI_CLK_130MHZ__)
    uint32_t      HWConf_130M[5];     // to be defined by SFI/EMI owner
#endif //defined(__SFI_CLK_130MHZ__)
#if defined(__SFI_CLK_104MHZ__)
    uint32_t      HWConf_104M[5];     // to be defined by SFI/EMI owner
#endif //defined(__SFI_CLK_104MHZ__)
#if defined(__SFI_CLK_78MHZ__)
    uint32_t      HWConf_78M[5];      // to be defined by SFI/EMI owner
#endif //defined(__SFI_CLK_78MHZ__)
    uint32_t      HWConf_26M[3];      // to be defined by SFI/EMI owner
} CMEMEntrySFI_DCM;


typedef struct {
    uint32_t      HWConf[16];         // to be defined by EMI owner
} CMEMEntryEMI;

typedef struct {
    char               m_identifier[16];   // MTK_COMBO_ID_INFO
    unsigned int       m_ver;
    unsigned int       Count;
    CMEMEntrySFI       List[SFI_COMBO_COUNT];  // to be defined by SFI/EMI owner
} CMEMEntrySFIList;

typedef struct {
    CMEMEntrySFI_DCM      List[SFI_COMBO_COUNT];  // to be defined by SFI/EMI owner
} CMEMEntrySFIList_dcm;

#endif


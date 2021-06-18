/* Copyright Statement:
 *
 */

#include "hal_flash.h"
#ifdef HAL_FLASH_MODULE_ENABLED
#include "memory_attribute.h"
#include "hal_flash_opt.h"
#include "hal_flash_cfi_internal.h"
#include "hal_flash_cfi.h"
#include "hal_flash_sf.h"
#include "hal_flash_custom_memorydevice.h"


extern uint32_t SaveAndSetIRQMask(void);
extern void RestoreIRQMask(uint32_t irq);
extern bool CMEM_CheckValidDeviceID(uint8_t *id);

//-----------------------------------------------------------------------------
/*!
  @brief
    Read NOR Flash ID

  @param[in] BaseAddr Pointer to the NOR Flash memory base address
  @param[out] flashid Array of FlashID, the maximum length is 4
  @retval
    Query result, byte aligned.

  @remarks
    Limited to the length return value (32 bits), the given length shall not exceed 4 (bytes)
    This function must be put in RAM
*/

ATTR_TEXT_IN_RAM void NOR_ReadID(const uint16_t CS, volatile FLASH_CELL *BaseAddr, uint16_t *flashid)
{
    uint32_t savedMask;

    // Read Serial Flash ID
    {
        uint8_t cmd, id[SF_FLASH_ID_LENGTH], i;

        cmd = SF_CMD_READ_ID_QPI;
        savedMask = SaveAndSetIRQMask();
        SFI_Dev_Command_Ext(CS, &cmd, id, 1, SF_FLASH_ID_LENGTH);
        RestoreIRQMask(savedMask);

        if (id[0] == 0x00 || id[0] == 0xFF || (CMEM_CheckValidDeviceID(id) == false)) {
            cmd = SF_CMD_READ_ID;
            savedMask = SaveAndSetIRQMask();
            SFI_Dev_Command_Ext(CS, &cmd, id, 1, SF_FLASH_ID_LENGTH);
            RestoreIRQMask(savedMask);
        }

        for (i = 0; i < SF_FLASH_ID_LENGTH; i++) {
            flashid[i] = id[i];
        }
    }
    return;
}

#endif //HAL_FLASH_MODULE_ENABLED


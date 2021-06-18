/* Copyright Statement:
 *
 */

#include "hal_wdt.h"
#if defined(HAL_WDT_MODULE_ENABLED)
#include "mt2523.h"
#include "hal_wdt_retention.h"



static uint8_t retention_flag_magic[6] = {0x2E, 0x4E, 0x6E, 0x8E, 0xCE, 0xEE};

void wdt_set_retention_flag(WDT_RETENTION_FLAG_USER_ID_T user_id, uint32_t register_number, uint32_t bit_offset, bool value)
{
    uint32_t register_value;

    if (user_id <= WDT_RETENTION_FLAG_USER_START || user_id >= WDT_RETENTION_FLAG_USER_END) {
        return;
    }
    if ((register_number >= WDT_RETENTION_FLAG_NUMBER) || (bit_offset >= WDT_RETENTION_FLAG_BITS)) {
        return;
    }

    /* read */
    register_value = WDT_RETENTION_FLAG_REGISTER->RETN_FLAG[register_number];

    /* modify */
    if (0 == value) {
        register_value &= ~(0x1 << bit_offset) ;
    } else {
        register_value |= (0x1 << bit_offset) ;
    }

    register_value &= 0x00FFFFFF;
    register_value |= (retention_flag_magic[register_number] << WDT_RETENTION_FLAG_MAGIC_BIT_OFFSET);

    /* write */
    WDT_RETENTION_FLAG_REGISTER->RETN_FLAG[register_number] = register_value;


}


void wdt_set_retention_data(WDT_RETENTION_DATA_USER_ID_T user_id, uint32_t register_number, uint32_t value)
{
    if (user_id <= WDT_RETENTION_DATA_USER_START || user_id >= WDT_RETENTION_DATA_USER_END) {
        return;
    }
    if (register_number >= WDT_RETENTION_DATA_NUMBER) {
        return;
    }
    WDT_RETENTION_DATA_REGISTER->RETN_DATA[register_number] = value;
}

int8_t wdt_read_retention_flag(uint32_t register_number, uint32_t bit_offset)
{
    if ((register_number >= WDT_RETENTION_FLAG_NUMBER) || (bit_offset >= WDT_RETENTION_FLAG_BITS)) {
        return -1;
    }

    return (WDT_RETENTION_FLAG_REGISTER->RETN_FLAG[register_number] >> bit_offset) & 0x1;
}

int8_t wdt_read_retention_data(uint32_t register_number)
{
    if (register_number >= WDT_RETENTION_DATA_NUMBER) {
        return -1;
    }

    return WDT_RETENTION_DATA_REGISTER->RETN_DATA[register_number];
}

#endif

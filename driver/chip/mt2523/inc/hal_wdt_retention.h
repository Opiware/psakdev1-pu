/* Copyright Statement:
 *
 */

#ifndef __WDT_RETENTION_H__
#define __WDT_RETENTION_H__

#include <stdint.h>
#include <stdbool.h>



#define __IO volatile
#define WDT_RETENTION_FLAG_NUMBER  (6)
#define WDT_RETENTION_FLAG_BITS    (12)
#define WDT_RETENTION_FLAG_MAGIC_BIT_OFFSET   (24)


#define WDT_RETENTION_DATA_NUMBER   (5)




typedef enum {
    WDT_RETENTION_FLAG_USER_START = 0xD0,
    WDT_RETENTION_FLAG_USER_BROM = 0xD1,
    WDT_RETENTION_FLAG_USER_BL = 0xD2,
    WDT_RETENTION_FLAG_FOTA_GNSS = 0xD3,
    WDT_RETENTION_FLAG_USER_WARM_BOOT = 0xD4,
    WDT_RETENTION_FLAG_USER_LOW_POWER = 0xD5,
    WDT_RETENTION_FLAG_USER_FLASH_TOOL = 0xD6,
    WDT_RETENTION_FLAG_USER_END = 0xD7,
} WDT_RETENTION_FLAG_USER_ID_T;

typedef enum {
    WDT_RETENTION_DATA_USER_START = 0xE0,
    WDT_RETENTION_DATA_USER_BROM = 0xE1,
    WDT_RETENTION_DATA_USER_BL = 0xE2,
    WDT_RETENTION_DATA_USER_FLASH_TOOL = 0xE3,
    WDT_RETENTION_DATA_USER_END = 0xE4,
} WDT_RETENTION_DATA_USER_ID_T;


typedef struct {
    __IO uint32_t RETN_FLAG[WDT_RETENTION_FLAG_NUMBER];         /* WDT MODE register */
} WDT_RETENTION_FLAG_T;

typedef struct {
    __IO uint32_t RETN_DATA[WDT_RETENTION_DATA_NUMBER];     /* WDT INTERVAL register */
} WDT_RETENTION_DATA_T;

#define WDT_RETENTION_FLAG_REGISTER  ((WDT_RETENTION_FLAG_T *)(RGU_BASE+0x0800))
#define WDT_RETENTION_DATA_REGISTER  ((WDT_RETENTION_DATA_T *)(RGU_BASE+0x0820))


/**
 * @brief
 * @param[in] register_number is the number of register. from 0 ~ 5
 * @param[in] bit_offset is the register bit offset you want to set. from 0 ~ 11
 * @param[in] value is the value you want to set. the value is 0 or 1.
 * @return */
void wdt_set_retention_flag(WDT_RETENTION_FLAG_USER_ID_T user_id, uint32_t register_number, uint32_t bit_offset, bool value);


/**
 * @brief
 * @param[in] register_number is the number of register. from 0 ~ 5
 * @param[in] value is the value you want to set. the value is a 32bit value.
 * @return */
void wdt_set_retention_data(WDT_RETENTION_DATA_USER_ID_T user_id, uint32_t register_number, uint32_t value);


/**
 * @brief
 * @param[in] register_number is the number of register. from 0 ~ 5
 * @param[in] bit_offset is the register bit offset you want to set. from 0 ~ 11
 * @return    return the bit value. the value is 0 or 1. if return -1, it means register_number is wrong. */
int8_t wdt_read_retention_flag(uint32_t register_number, uint32_t bit_offset);


/**
 * @brief
 * @param[in] register_number is the number of register. from 0 ~ 5
 * @return    return the bit value. the value is a 32bit value. if return -1, it means register_number is wrong. */
int8_t wdt_read_retention_data(uint32_t register_number);



#endif

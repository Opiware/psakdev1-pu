/* Copyright Statement:
 *
 */

#ifndef __BATTERY_COMMON_H__
#define __BATTERY_COMMON_H__

#include "hal_platform.h"

#include "hal_charger.h"
#include "battery_meter.h"
#include "battery_parameter.h"
#include "battery_management.h"
#include "syslog.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BMT_DEBUG_ENABLEx

/*****************************************************************************
 *  Pulse Charging State
 ****************************************************************************/
#define  CHR_PRE                        0x1000
#define  CHR_CC                         0x1001
#define  CHR_TOP_OFF                    0x1002
#define  CHR_BATFULL                    0x1003
#define  CHR_ERROR                      0x1004

#define BMT_EVENT_INIT              0
#define BMT_EVENT_TIMEOUT           1
#define BMT_EVENT_WAKE_UP_BATTERY   2
#define BMT_EVENT_RESUME            3

typedef struct bmt_cmd_event_t {
    uint32_t event;
} bmt_cmd_event_t;

typedef enum {
    PMU_STATUS_OK = 0,
    PMU_STATUS_FAIL = 1,
} PMU_STATUS;

typedef enum {
    BATTERY_AVG_CURRENT = 0,
    BATTERY_AVG_VOLT = 1,
    BATTERY_AVG_TEMP = 2,
    BATTERY_AVG_MAX
} BATTERY_AVG_ENUM;

typedef struct {
    bool bat_exist;
    bool bat_full;
    int32_t bat_charging_state;
    uint32_t bat_vol;
    bool bat_in_recharging_state;
    uint32_t Vsense;
    bool charger_exist;
    uint32_t charger_vol;
    int32_t ICharging;
    int32_t IBattery;
    int32_t temperature;
    uint32_t total_charging_time;
    uint32_t PRE_charging_time;
    uint32_t CC_charging_time;
    uint32_t TOPOFF_charging_time;
    uint32_t POSTFULL_charging_time;
    uint32_t charger_type;
    int32_t SOC;
    int32_t UI_SOC;
    int32_t UI_SOC2;
    uint32_t nPercent_ZCV;
    uint32_t ZCV;
    int32_t UI_SOC2_LEVEL;
} PMU_ChargerStruct;


typedef enum {
    TEMP_BELOW_NEG_10 = 0,
    TEMP_NEG_10_TO_POS_0,
    TEMP_POS_0_TO_POS_10,
    TEMP_POS_10_TO_POS_45,
    TEMP_POS_45_TO_POS_60,
    TEMP_ABOVE_POS_60
} temp_state_enum;

/*****************************************************************************
 *  Normal battery temperature state
 ****************************************************************************/
typedef enum {
    TEMP_POS_LOW = 0,
    TEMP_POS_NORMAL,
    TEMP_POS_HIGH
} batt_temp_state_enum;

/*****************************************************************************
 * Battery management
 ****************************************************************************/
typedef struct bmt_callback_context_t {
    bool callback_init;
    battery_management_callback_t func;
} bmt_callback_context_t;

extern void battery_driver_charging_algorithm(void);

extern bool battery_core_get_charger_status(void);

extern uint32_t battery_core_get_current_time_in_ms(void);
extern uint32_t battery_core_get_duration_time(BATTERY_TIME_ENUM duration_type);
extern void battery_core_update_time(uint32_t *pre_time, BATTERY_TIME_ENUM duration_type);


#ifdef __cplusplus
}
#endif

#endif /*__BATTERY_COMMON_H__*/


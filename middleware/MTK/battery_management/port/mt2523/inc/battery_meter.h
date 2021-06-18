/* Copyright Statement:
 *
 */

#ifndef __BATTERY_METER_H__
#define __BATTERY_METER_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "fuelgauge_interface.h"

struct battery_meter_table_custom_data {

    int32_t battery_profile_t0_size;
    BATTERY_PROFILE_STRUC battery_profile_t0[51];
    int32_t battery_profile_t1_size;
    BATTERY_PROFILE_STRUC battery_profile_t1[51];
    int32_t battery_profile_t2_size;
    BATTERY_PROFILE_STRUC battery_profile_t2[51];
    int32_t battery_profile_t3_size;
    BATTERY_PROFILE_STRUC battery_profile_t3[51];
    int32_t battery_profile_temperature_size;
    BATTERY_PROFILE_STRUC battery_profile_temperature[51];

    int32_t r_profile_t0_size;
    R_PROFILE_STRUC r_profile_t0[51];
    int32_t r_profile_t1_size;
    R_PROFILE_STRUC r_profile_t1[51];
    int32_t r_profile_t2_size;
    R_PROFILE_STRUC r_profile_t2[51];
    int32_t r_profile_t3_size;
    R_PROFILE_STRUC r_profile_t3[51];
    int32_t r_profile_temperature_size;
    R_PROFILE_STRUC r_profile_temperature[51];
};

struct battery_custom_data {
    /* cust_charging.h */

    /* Linear Charging Threshold */
    int32_t v_pre2cc_thres;
    int32_t v_cc2topoff_thres;
    int32_t recharging_voltage;
    int32_t charging_full_current;

    /* Charging Current Setting */
    int32_t usb_charger_current;
    int32_t ac_charger_current;
    int32_t non_std_ac_charger_current;
    int32_t charging_host_charger_current;

    /* High battery support */
    int32_t high_battery_voltage_support;

};


/* ============================================================ */
/* External function */
/* ============================================================ */
extern void battery_meter_init(void);
extern int32_t battery_meter_initial(void);
extern int32_t battery_meter_get_battery_nPercent_zcv(void);
extern int32_t battery_meter_get_battery_voltage(bool update);
extern int32_t battery_meter_get_charger_voltage(void);
extern int32_t battery_meter_get_battery_temperature(void);
extern int32_t battery_meter_get_charging_current(void);
extern int32_t battery_meter_get_battery_nPercent_UI_SOC(void);
extern int32_t battery_meter_sync_current_sense_offset(int32_t bat_i_sense_offset);
extern int32_t battery_meter_get_voltage_sense(void);
extern int32_t battery_meter_get_battery_zcv(void);
extern uint32_t battery_meter_get_dynamic_period(void);
#ifdef __cplusplus
}
#endif

#endif /*__BATTERY_METER_H__*/


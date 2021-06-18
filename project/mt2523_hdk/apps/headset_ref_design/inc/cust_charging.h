/* Copyright Statement:
 *
 */

#ifndef __CUST_CHARGING_H__
#define __CUST_CHARGING_H__


#ifdef __cplusplus
extern "C" {
#endif

#define CUST_R_SENSE            200     /* m ohm */

#define R_CHARGER_1             330     /* K ohm */
#define R_CHARGER_2             39      /* K ohm */

/* JEITA parameter */
/*#define CONFIG_MTK_JEITA_STANDARD_SUPPORT */
#define CUST_SOC_JEITA_SYNC_TIME        30
#define JEITA_RECHARGE_VOLTAGE          4110    /* for linear charging */
#define JEITA_TEMP_ABOVE_POS_60_CV_VOLTAGE          HAL_BATTERY_VOLT_04_1000_V
#define JEITA_TEMP_POS_45_TO_POS_60_CV_VOLTAGE      HAL_BATTERY_VOLT_04_1000_V
#define JEITA_TEMP_POS_10_TO_POS_45_CV_VOLTAGE      HAL_BATTERY_VOLT_04_2000_V
#define JEITA_TEMP_POS_0_TO_POS_10_CV_VOLTAGE       HAL_BATTERY_VOLT_04_1000_V
#define JEITA_TEMP_NEG_10_TO_POS_0_CV_VOLTAGE       HAL_BATTERY_VOLT_03_9000_V
#define JEITA_TEMP_BELOW_NEG_10_CV_VOLTAGE          HAL_BATTERY_VOLT_03_9000_V

/* For JEITA Linear Charging only */
#define JEITA_NEG_10_TO_POS_0_FULL_CURRENT                  120    /* mA */
#define JEITA_TEMP_POS_45_TO_POS_60_RECHARGE_VOLTAGE        4000
#define JEITA_TEMP_POS_10_TO_POS_45_RECHARGE_VOLTAGE        4100
#define JEITA_TEMP_POS_0_TO_POS_10_RECHARGE_VOLTAGE         4000
#define JEITA_TEMP_NEG_10_TO_POS_0_RECHARGE_VOLTAGE         3800
#define JEITA_TEMP_POS_45_TO_POS_60_CC2TOPOFF_THRESHOLD     4050
#define JEITA_TEMP_POS_10_TO_POS_45_CC2TOPOFF_THRESHOLD     4050
#define JEITA_TEMP_POS_0_TO_POS_10_CC2TOPOFF_THRESHOLD      4050
#define JEITA_TEMP_NEG_10_TO_POS_0_CC2TOPOFF_THRESHOLD      3850

/* Battery Temperature Protection */
#define MTK_TEMPERATURE_RECHARGE_SUPPORT
#define MAX_CHARGE_TEMPERATURE                              50
#define MAX_CHARGE_TEMPERATURE_MINUS_X_DEGREE               47
#define MIN_CHARGE_TEMPERATURE                              0
#define MIN_CHARGE_TEMPERATURE_PLUS_X_DEGREE                6
#define ERR_CHARGE_TEMPERATURE                              0xFF

#define BAT_LOW_TEMP_PROTECT_ENABLE

/*#define HIGH_BATTERY_VOLTAGE_SUPPORT */

#define V_CHARGER_ENABLE    1       /* 1:ON , 0:OFF */
#define V_CHARGER_MAX       6500    /* 6.5 V */
#define V_CHARGER_MIN       4400    /* 4.4 V */

/* Precise Tunning */
#define BATTERY_AVERAGE_DATA_NUMBER     3
#define BATTERY_AVERAGE_SIZE            20

#define V_0PERCENT_TRACKING             3450  /* 3450mV */


/* Linear Charging Threshold */
#define V_PRE2CC_THRES              3400    /* mV */
#define V_CC2TOPOFF_THRES           4100
#define RECHARGING_VOLTAGE          4110
#define CHARGING_FULL_CURRENT       35     /* mA */

/* Charging Current Setting */
#define USB_CHARGER_CURRENT                 HAL_CHARGE_CURRENT_100_MA       /* 100mA */
#define AC_CHARGER_CURRENT                  HAL_CHARGE_CURRENT_100_MA
#define NON_STD_AC_CHARGER_CURRENT          HAL_CHARGE_CURRENT_100_MA
#define CHARGING_HOST_CHARGER_CURRENT       HAL_CHARGE_CURRENT_100_MA

#ifdef __cplusplus
}
#endif

#endif /*__CUST_CHARGING_H__*/


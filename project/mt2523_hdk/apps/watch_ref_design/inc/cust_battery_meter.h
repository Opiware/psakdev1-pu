/* Copyright Statement:
 *
 */

#ifndef __CUST_BATTERY_METER_H__
#define __CUST_BATTERY_METER_H__


#ifdef __cplusplus
extern "C" {
#endif

#define SOC_BY_SW_FG

#define TEMPERATURE_T0             110
#define TEMPERATURE_T1             0
#define TEMPERATURE_T2             25
#define TEMPERATURE_T3             50
#define TEMPERATURE_T              255  /* This should be fixed, never change the value */

#define FG_METER_RESISTANCE     0

/* Qmax for battery  */
#define Q_MAX_POS_50    488
#define Q_MAX_POS_25    479
#define Q_MAX_POS_0     356
#define Q_MAX_NEG_10    293

#define Q_MAX_POS_50_H_CURRENT    483
#define Q_MAX_POS_25_H_CURRENT    466
#define Q_MAX_POS_0_H_CURRENT     131
#define Q_MAX_NEG_10_H_CURRENT    113


/* battery meter parameter */
#define CHANGE_TRACKING_POINT
#define CUST_TRACKING_POINT     0
#define AGING_TUNING_VALUE      100

#define OCV_BOARD_COMPESATE     0       /* mV */
#define CAR_TUNE_VALUE          100     /* 1.00 */

#define DIFFERENCE_HWOCV_RTC         30
#define DIFFERENCE_HWOCV_SWOCV       0
#define DIFFERENCE_SWOCV_RTC         10
#define MAX_SWOCV                    3

#define BATTERYPSEUDO100             90
#define BATTERYPSEUDO1               4

/*#define Q_MAX_BY_CURRENT*/            /* 7. Qmax varient by current loading. */
/*#define Q_MAX_BY_SYS*/                /* 8. Qmax varient by system drop voltage. */

/*#define SHUTDOWN_GAUGE0*/
#define SHUTDOWN_GAUGE1_XMINS
#define SHUTDOWN_GAUGE1_MINS         60

#define SHUTDOWN_SYSTEM_VOLTAGE      3000
#define CHARGE_TRACKING_TIME         60
#define DISCHARGE_TRACKING_TIME      10

#define RECHARGE_TOLERANCE           10

/* Dynamic change wake up period of battery thread when suspend*/
#define VBAT_NORMAL_WAKEUP           3600   /* 3.6V */
#define VBAT_LOW_POWER_WAKEUP        3500   /* 3.5v */
#define NORMAL_WAKEUP_PERIOD         2700   /* 45 * 60 = 45 min */
#define LOW_POWER_WAKEUP_PERIOD      300    /* 5 * 60 = 5 min */
#define CLOSE_POWEROFF_WAKEUP_PERIOD 30     /* 30 s */



#ifdef __cplusplus
}
#endif

#endif /*__CUST_BATTERY_METER_H__*/


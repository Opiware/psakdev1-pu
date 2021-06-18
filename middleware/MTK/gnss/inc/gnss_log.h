/* Copyright Statement:
 *
 */


#ifndef GNSS_LOG_H
#define GNSS_LOG_H

#include "FreeRTOS.h"
#include "task.h"

#define GNSS_DEBUG
#ifdef GNSS_DEBUG
#include "syslog.h"

#define GNSSLOGE(fmt,arg...)         do { LOG_E(GNSS_TAG, "[GNSS] ERR: " fmt, ##arg); } while(0)
#define GNSSLOGW(fmt,arg...)         do { LOG_W(GNSS_TAG, "[GNSS] WARR: " fmt, ##arg); } while(0)
#define GNSSLOGI(fmt,arg...)         do { LOG_I(GNSS_TAG ,"[GNSS] INFO: " fmt, ##arg); } while(0)
#define GNSSLOGD(fmt, args...)       do { LOG_I(GNSS_TAG, "[GNSS] DBG: " fmt, ##args); } while(0)

//#define GNSSLOGE(fmt,arg...)         do { taskENTER_CRITICAL(); LOG_E(GNSS_TAG, "[GNSS] ERR: " fmt, ##arg); taskEXIT_CRITICAL();} while(0)
//#define GNSSLOGW(fmt,arg...)         do { taskENTER_CRITICAL(); LOG_W(GNSS_TAG, "[GNSS] WARR: " fmt, ##arg); taskEXIT_CRITICAL();} while(0)
//#define GNSSLOGI(fmt,arg...)         do { taskENTER_CRITICAL(); LOG_I(GNSS_TAG ,"[GNSS] INFO: " fmt, ##arg); taskEXIT_CRITICAL();} while(0)
//#define GNSSLOGD(fmt, args...)       do { taskENTER_CRITICAL(); LOG_I(GNSS_TAG, "[GNSS] DBG: " fmt, ##args); taskEXIT_CRITICAL();} while(0)

#else
#if 1
#define GNSSLOGW(fmt, args...)    do { taskENTER_CRITICAL(); printf("[GNSS] WARR: " fmt, ##args); taskEXIT_CRITICAL();} while(0)
#define GNSSLOGE(fmt, args...)    do { taskENTER_CRITICAL(); printf("[GNSS] ERR: " fmt, ##args); taskEXIT_CRITICAL();} while(0)
#define GNSSLOGD(fmt, args...)    do { taskENTER_CRITICAL(); printf("[GNSS] DBG: " fmt, ##args); taskEXIT_CRITICAL();} while(0)
#define GNSSLOGI(fmt, args...)    do { taskENTER_CRITICAL(); printf("[GNSS] INFO: " fmt, ##args); taskEXIT_CRITICAL();} while(0)
#else
#define GNSSLOGW(fmt, args...) 
#define GNSSLOGE(fmt, args...) 
#define GNSSLOGD(fmt, args...) 
#define GNSSLOGI(fmt, args...) 
#endif

#endif
#endif /*GNSS_LOG_H*/


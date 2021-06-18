/* Copyright Statement:
 *
 */

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <gui/database/heart_rate_db.hpp>
#include <gui/common/CommonService.hpp>

#ifdef SIMULATOR
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
#else
#include "FreeRTOS.h"
#include "hal_rtc.h"
#endif /* SIMULATOR */

Model::Model() :
    modelListener(0),
    selectedMenuIndex(0)
{
}

void Model::tick()
{
    Time previousTime = currentTime;
    int heartRateData = 0;

#ifdef SIMULATOR
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    currentTime.hours = timenow.tm_hour;
    currentTime.minutes = timenow.tm_min;
    currentTime.seconds = timenow.tm_sec;
    currentTime.milliseconds = 0;
#else
    timeval timenow;
    gettimeofday(&timenow, NULL);

    currentTime.hours = (timenow.tv_sec / 60 / 60) % 24;
    currentTime.minutes = (timenow.tv_sec / 60) % 60;
    currentTime.seconds = timenow.tv_sec % 60;
    currentTime.milliseconds = timenow.tv_usec / 1000;
#endif /*_MSC_VER*/
#else
    hal_rtc_time_t rtc_time;
    hal_rtc_status_t ret = hal_rtc_get_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }
    currentTime.hours = rtc_time.rtc_hour;
    currentTime.minutes = rtc_time.rtc_min;
    currentTime.seconds = rtc_time.rtc_sec;
    currentTime.milliseconds = 0;
#endif /* SIMULATOR */

    if (currentTime.seconds != previousTime.seconds) {
        if (modelListener) {
            modelListener->timeUpdated(currentTime);
#ifdef SIMULATOR
            // Simulates the HeartRate data
            heartRateData = heartRateDataSZ[currentHeartDataIndex];
            modelListener->heartRateDataUpdated(heartRateData);
            ++currentHeartDataIndex;
            if (currentHeartDataIndex == FrequenceNum) {
                currentHeartDataIndex = 0;
            }
#else
            heartRateData = HeartRateCache::getHeartRateCacheInstance()->getHeartRateData();
            if (-1 != heartRateData) {
                // new data coming, need refresh UI
                modelListener->heartRateDataUpdated(heartRateData);
            }
#endif
        }
    }
}

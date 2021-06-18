/* Copyright Statement:
 *
 */

#include "heart_rate_db.hpp"

HeartRateCache *HeartRateCache::heartRateCache = NULL;

HeartRateCache::HeartRateCache():
    writeIndex(0),
    readIndex(0)
{
    //init heart rate database
    int index;
    for (index = 0; index < FrequenceNum; ++index) {
        heartRateData[index] = 0;
    }
}

HeartRateCache::HeartRateCache(const HeartRateCache &heartRateCache)
{
}

int HeartRateCache::getHeartRateData()
{
    int data = -1;
    if (writeIndex != readIndex) {
        data = heartRateData[readIndex];
        readIndex = (readIndex + 1) % FrequenceNum;
    }
    return data;
}

void HeartRateCache::addHeartRateData(int bmp)
{
    int tempIndex = (writeIndex + 1) % FrequenceNum;
    if (tempIndex != readIndex) {
        heartRateData[writeIndex] = bmp;
        writeIndex = tempIndex;
    }
}

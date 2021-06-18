/* Copyright Statement:
 *
 */

#ifndef HEART_RATE_DB_HPP
#define HEART_RATE_DB_HPP

#include <cstddef>

class HeartRateCache
{
private:
    HeartRateCache();
    HeartRateCache(const HeartRateCache &);
public:
    static HeartRateCache *getHeartRateCacheInstance()
    {
        if (NULL == heartRateCache) {
            heartRateCache = new HeartRateCache();
        }
        return heartRateCache;
    }

    void addHeartRateData(int bmp);
    int getHeartRateData();

public:
    static HeartRateCache *heartRateCache;
    static const int FrequenceNum = 80;

    int writeIndex;
    int readIndex;
    int heartRateData[FrequenceNum];
};

#endif /* HEART_RATE_DB_HPP */


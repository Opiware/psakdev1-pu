/* Copyright Statement:
 *
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/model/Time.hpp>
#include <gui/database/heart_rate_db.hpp>

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model. */
class Model
{
public:
    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener *listener)
    {
        modelListener = listener;
    }

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick();

    Time getCurrentTime() const
    {
        return currentTime;
    }

    void setSelectedMenuIndex(uint8_t index)
    {
        selectedMenuIndex = index;
    }
    uint8_t getSelectedMenuIndex() const
    {
        return selectedMenuIndex;
    }

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener *modelListener;
    Time currentTime;

    uint8_t selectedMenuIndex;

    static const int BaseHRData = 190;
#ifdef SIMULATOR
    static const int FrequenceNum = 80;
    static const int noHeartRateData = 1;
    int currentHeartDataIndex = 0;
    int heartRateDataSZ[FrequenceNum] = { 50, 60, 70, 80, 75, 90, 100, 120, 65, 80, 50, 60, 70, 80, 75, 90, 100, 120, 65, 80, 60, 72, 76, 79, 61, 70 };
    //int heartRateData[FrequenceNum] = { 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 140, 80, 80, 80, 80, 140, 80, 80, 80, 140, 80, 80, 140 };
#else
    HeartRateCache *heartRateCache;
#endif
};

#endif /* MODEL_HPP */

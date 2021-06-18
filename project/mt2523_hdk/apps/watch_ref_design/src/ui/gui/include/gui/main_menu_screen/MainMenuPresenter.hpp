/* Copyright Statement:
 *
 */

#ifndef MAIN_MENU_PRESENTER_HPP
#define MAIN_MENU_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class MainMenuView;

class MainMenuPresenter : public DemoPresenter
{
public:
    enum DemoID {
        CLOCK_FACE = 0,
        HEART_RATE,
        SETTINGS,
        MAX_DEMO_ID
    };

    static const int HeartRateLower = 0;
    static const int HeartRateUpper = 180;

    MainMenuPresenter(MainMenuView &v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void timeUpdated(Time time);
    virtual void heartRateDataUpdated(int data);

    virtual ~MainMenuPresenter() {};

    void demoSelected(DemoID id, uint8_t menuIndex);

    void setSelectedMenuIndex(uint8_t menuIndex);

private:
    MainMenuPresenter();

    MainMenuView &view;
};

#endif // MAIN_MENU_PRESENTER_HPP

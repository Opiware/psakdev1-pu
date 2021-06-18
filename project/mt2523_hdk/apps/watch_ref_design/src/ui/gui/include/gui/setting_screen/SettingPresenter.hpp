/* Copyright Statement:
 *
 */

#ifndef SETTING_PRESENTER_HPP
#define SETTING_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class SettingView;

/**
 * The Presenter for a template screen. In the MVP paradigm, the presenter acts upon
 * events from the model and the view. By deriving from ModelListener, the presenter
 * implements the interface which the model uses to inform the current presenter of
 * events and model state changes. The presenter also contains a reference to the
 * associated view, and uses this to update the view accordingly.
 * */
class SettingPresenter : public DemoPresenter
{
public:
    SettingPresenter(SettingView &v);

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

    virtual ~SettingPresenter() {};

    void menuSelected(uint8_t menuIndex);

private:
    SettingPresenter();

    SettingView &view;
};

#endif // SETTING_PRESENTER_HPP

/* Copyright Statement:
 *
 */

#include <gui/setting_screen/SettingPresenter.hpp>
#include <gui/setting_screen/SettingView.hpp>

SettingPresenter::SettingPresenter(SettingView &v) :
    DemoPresenter(v),
    view(v)
{
}

void SettingPresenter::activate()
{
}

void SettingPresenter::deactivate()
{
}

void SettingPresenter::menuSelected(uint8_t menuIndex)
{
    switch (menuIndex) {
        case 0:
            static_cast<FrontendApplication *>(Application::getInstance())->gotoSetTimeScreen();
            break;
        case 1:
            static_cast<FrontendApplication *>(Application::getInstance())->gotoSetDateScreen();
            break;
        case 2:
            static_cast<FrontendApplication *>(Application::getInstance())->gotoSetHeartRateScreen();
            break;
        default:
            break;
    }
}

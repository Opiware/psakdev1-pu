/* Copyright Statement:
 *
 */

#include <gui/common/DemoPresenter.hpp>

DemoPresenter::DemoPresenter(DemoViewInterface &view) :
    viewInterface(view)
{
}

void DemoPresenter::backOptionMenuSelected()
{
    static_cast<FrontendApplication *>(Application::getInstance())->backMainMenuScreen();
}

void DemoPresenter::backOptionSettingSelected()
{
    static_cast<FrontendApplication *>(Application::getInstance())->backSettingScreen();
}

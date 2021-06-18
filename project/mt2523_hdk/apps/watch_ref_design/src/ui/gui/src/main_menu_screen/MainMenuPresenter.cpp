/* Copyright Statement:
 *
 */

#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <gui/main_menu_screen/MainMenuView.hpp>

MainMenuPresenter::MainMenuPresenter(MainMenuView &v) :
    DemoPresenter(v),
    view(v)
{
}

void MainMenuPresenter::activate()
{
    view.setSelectedMenuIndex(model->getSelectedMenuIndex());
}

void MainMenuPresenter::deactivate()
{
}

void MainMenuPresenter::timeUpdated(Time time)
{
    view.handleTimeUpdated(time.hours, time.minutes, time.seconds);
}

void MainMenuPresenter::heartRateDataUpdated(int data)
{
    int physicalData = data;
    int logicalTotalVal = HeartRateUpper - HeartRateLower;
    int logicalShowData = 0;
    float factor = (float)((data - HeartRateLower) * 1.0 / logicalTotalVal);
    logicalShowData = (int)(HAL::DISPLAY_HEIGHT * factor);
    logicalShowData += logicalTotalVal / view.getGraphRowNum();
    view.handleHeartRateDataUpdated(physicalData, logicalShowData);
}

void MainMenuPresenter::demoSelected(DemoID id, uint8_t menuIndex)
{
    model->setSelectedMenuIndex(menuIndex);
    switch (id) {
        case SETTINGS:
            static_cast<FrontendApplication *>(Application::getInstance())->gotoSettingScreen();
            break;
        default:
            break;
    }
}

void MainMenuPresenter::setSelectedMenuIndex(uint8_t menuIndex)
{
    model->setSelectedMenuIndex(menuIndex);
}

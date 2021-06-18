/* Copyright Statement:
 *
 */

#include <gui/setting_screen/SetTimeView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/CommonUI.hpp>
#include <gui/common/CommonService.hpp>

#ifdef SIMULATOR
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
#else
#include "FreeRTOS.h"
#include "hal_rtc.h"
#endif

SetTimeView::SetTimeView() :
    DemoView<SetTimePresenter>(),
    onSaveAndGotoSettingButtonClicked(this, &SetTimeView::saveAndGotoSettingClickedHandler)
{
    // Setup background
    background.setBitmap(Bitmap(BITMAP_TIMEPICKER_MAIN_BACKGROUND_INT_ID));
    background.setXY(0, 0);
    add(background);

    // Add title
    titleTxt.setTypedText(TypedText(T_SET_TIME_TITLE));
    titleTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    titleTxt.setXY(116, 5);
    add(titleTxt);

    timePicker.setPosition(0, CommonUI::TITLE_HEIGHT, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - CommonUI::TITLE_HEIGHT);
    timePicker.setVisible(false);
    add(timePicker);

    gotoSettingButton.setBitmaps(Bitmap(BITMAP_ICON_BACK_INT_ID), Bitmap(BITMAP_ICON_BACK_INT_ID));
    gotoSettingButton.setXY(10, 5);
    add(gotoSettingButton);

    saveAndGotoSettingButton.setBitmaps(Bitmap(BITMAP_ICON_SAVE_INT_ID), Bitmap(BITMAP_ICON_SAVE_INT_ID));
    saveAndGotoSettingButton.setXY(280, 5);
    saveAndGotoSettingButton.setAction(onSaveAndGotoSettingButtonClicked);
    add(saveAndGotoSettingButton);
}

SetTimeView::~SetTimeView()
{
}

void SetTimeView::setupScreen()
{
    // Set the chosen control visible
    timePicker.setVisible(true);
    timePicker.invalidate();
    timePicker.reset();

#ifdef SIMULATOR
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    // Set start values before animation
    timePicker.setHour(timenow.tm_hour, 0, EasingEquations::backEaseInOut);
    timePicker.setMinute(timenow.tm_min, 0, EasingEquations::backEaseInOut);

    // Start animation to a specific date
    timePicker.setHour(timenow.tm_hour, 40, EasingEquations::backEaseInOut);
    timePicker.setMinute(timenow.tm_min, 42, EasingEquations::backEaseInOut);
#else
    hal_rtc_time_t rtc_time;
    hal_rtc_status_t ret = hal_rtc_get_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }

    // Set start values before animation
    timePicker.setHour(rtc_time.rtc_hour, 0, EasingEquations::backEaseInOut);
    timePicker.setMinute(rtc_time.rtc_min, 0, EasingEquations::backEaseInOut);

    // Start animation to a specific date
    timePicker.setHour(rtc_time.rtc_hour, 40, EasingEquations::backEaseInOut);
    timePicker.setMinute(rtc_time.rtc_min, 42, EasingEquations::backEaseInOut);
#endif
}

void SetTimeView::tearDownScreen()
{
}

void SetTimeView::handleKeyEvent(uint8_t key)
{
#ifdef SIMULATOR
    SYSTEMTIME sm;
    GetLocalTime(&sm);
    sm.wHour = timePicker.getHour();
    sm.wMinute = timePicker.getMinute();
    SetLocalTime(&sm);
#else
    hal_rtc_time_t rtc_time;
    hal_rtc_status_t ret = hal_rtc_get_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }
    rtc_time.rtc_hour = timePicker.getHour();
    rtc_time.rtc_min = timePicker.getMinute();
    ret = hal_rtc_set_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }
#endif

    if (CommonService::isBacklight() == true) {
        DemoView::handleKeyEvent(key);
        return;
    }

    DemoView::handleKeyEvent(key);

    presenter->backOptionSettingSelected();
}

void SetTimeView::saveAndGotoSettingClickedHandler(const AbstractButton &button)
{
    handleKeyEvent(0);
}

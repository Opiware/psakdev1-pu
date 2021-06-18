/* Copyright Statement:
 *
 */

#include <gui/setting_screen/SetDateView.hpp>
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

SetDateView::SetDateView() :
    DemoView<SetDatePresenter>(),
    onSaveAndGotoSettingButtonClicked(this, &SetDateView::saveAndGotoSettingClickedHandler)
{
    // Setup background
    background.setBitmap(Bitmap(BITMAP_DATEPICKER_MAIN_BACKGROUND_INT_ID));
    background.setXY(0, 0);
    add(background);

    // Add title
    titleTxt.setTypedText(TypedText(T_SET_DATE_TITLE));
    titleTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    titleTxt.setXY(118, 5);
    add(titleTxt);

    datePicker.setPosition(0, CommonUI::TITLE_HEIGHT, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - CommonUI::TITLE_HEIGHT);
    datePicker.setVisible(false);
    add(datePicker);

    gotoSettingButton.setBitmaps(Bitmap(BITMAP_ICON_BACK_INT_ID), Bitmap(BITMAP_ICON_BACK_INT_ID));
    gotoSettingButton.setXY(10, 5);
    add(gotoSettingButton);

    saveAndGotoSettingButton.setBitmaps(Bitmap(BITMAP_ICON_SAVE_INT_ID), Bitmap(BITMAP_ICON_SAVE_INT_ID));
    saveAndGotoSettingButton.setXY(280, 5);
    saveAndGotoSettingButton.setAction(onSaveAndGotoSettingButtonClicked);
    add(saveAndGotoSettingButton);
}

SetDateView::~SetDateView()
{
}

void SetDateView::setupScreen()
{
    // Set the chosen control visible
    datePicker.setVisible(true);
    datePicker.invalidate();
    datePicker.reset();

#ifdef SIMULATOR
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    // Set start values before animation
    datePicker.setDay(timenow.tm_mday - 1, 0, EasingEquations::backEaseInOut);
    datePicker.setMonth(timenow.tm_mon, 0, EasingEquations::backEaseInOut);
    datePicker.setYear(timenow.tm_year - 112, 0, EasingEquations::backEaseInOut);

    // Start animation to a specific date
    datePicker.setDay(timenow.tm_mday - 1, 40, EasingEquations::backEaseInOut);
    datePicker.setMonth(timenow.tm_mon, 42, EasingEquations::backEaseInOut);
    datePicker.setYear(timenow.tm_year - 112, 38, EasingEquations::backEaseInOut);
#else
    hal_rtc_time_t rtc_time;
    hal_rtc_status_t ret = hal_rtc_get_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }

    // Set start values before animation
    datePicker.setDay(rtc_time.rtc_day - 1, 0, EasingEquations::backEaseInOut);
    datePicker.setMonth(rtc_time.rtc_mon - 1, 0, EasingEquations::backEaseInOut);
    datePicker.setYear(rtc_time.rtc_year, 0, EasingEquations::backEaseInOut);

    // Start animation to a specific date
    datePicker.setDay(rtc_time.rtc_day - 1, 40, EasingEquations::backEaseInOut);
    datePicker.setMonth(rtc_time.rtc_mon - 1, 42, EasingEquations::backEaseInOut);
    datePicker.setYear(rtc_time.rtc_year, 38, EasingEquations::backEaseInOut);
#endif
}

void SetDateView::tearDownScreen()
{
}

void SetDateView::handleKeyEvent(uint8_t key)
{
#ifdef SIMULATOR
    SYSTEMTIME sm;
    GetLocalTime(&sm);
    sm.wYear = 2012 + datePicker.getYear();
    sm.wMonth = 1 + datePicker.getMonth();
    sm.wDay = 1 + datePicker.getDay();
    SetLocalTime(&sm);
#else
    hal_rtc_time_t rtc_time;
    hal_rtc_status_t ret = hal_rtc_get_time(&rtc_time);
    if (HAL_RTC_STATUS_OK != ret) {
        configASSERT(0);
        return;
    }
    rtc_time.rtc_year = datePicker.getYear();
    rtc_time.rtc_mon = datePicker.getMonth() + 1;
    rtc_time.rtc_day = datePicker.getDay() + 1;
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

void SetDateView::saveAndGotoSettingClickedHandler(const AbstractButton &button)
{
    handleKeyEvent(0);
}

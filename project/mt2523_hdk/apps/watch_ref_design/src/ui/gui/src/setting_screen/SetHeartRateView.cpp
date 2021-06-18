/* Copyright Statement:
 *
 */

#include <gui/setting_screen/SetHeartRateView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/CommonUI.hpp>
#include <gui/common/CommonService.hpp>

SetHeartRateView::SetHeartRateView() :
    DemoView<SetHeartRatePresenter>(),
    onState(CommonService::getHeartRateStatus()),
    onToggleButtonClicked(this, &SetHeartRateView::toggleButtonClickedHandler)
{
    // Setup background
    background.setColor(Color::getColorFrom24BitRGB(0x35, 0x36, 0x30));
    background.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    add(background);

    // Add title
    titleTxt.setTypedText(TypedText(T_HEART_RATE_TITLE));
    titleTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    titleTxt.setXY(106, 5);
    add(titleTxt);

    if (onState) {
        buttonTxt.setTypedText(TypedText(T_ON_TEXT));
    } else {
        buttonTxt.setTypedText(TypedText(T_OFF_TEXT));
    }
    buttonTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    buttonTxt.setXY(28, 65);
    add(buttonTxt);

    if (onState) {
        button.setBitmaps(Bitmap(BITMAP_SWITCH_ON_INT_ID), Bitmap(BITMAP_SWITCH_OFF_INT_ID));
    } else {
        button.setBitmaps(Bitmap(BITMAP_SWITCH_OFF_INT_ID), Bitmap(BITMAP_SWITCH_ON_INT_ID));
    }
    button.setAction(onToggleButtonClicked);
    button.setXY(172, 60);
    add(button);

    gotoSettingButton.setBitmaps(Bitmap(BITMAP_ICON_BACK_INT_ID), Bitmap(BITMAP_ICON_BACK_INT_ID));
    gotoSettingButton.setXY(10, 5);
    add(gotoSettingButton);
}

SetHeartRateView::~SetHeartRateView()
{
}

void SetHeartRateView::setupScreen()
{
}

void SetHeartRateView::tearDownScreen()
{
}

void SetHeartRateView::handleKeyEvent(uint8_t key)
{
    if (CommonService::isBacklight() == true) {
        DemoView::handleKeyEvent(key);
        return;
    }

    DemoView::handleKeyEvent(key);

    presenter->backOptionSettingSelected();
}

void SetHeartRateView::toggleButtonClickedHandler(const AbstractButton &button)
{
    onState = !onState;
    CommonService::setHeartRateStatus(onState);
    if (onState) {
        buttonTxt.setTypedText(TypedText(T_ON_TEXT));
    } else {
        buttonTxt.setTypedText(TypedText(T_OFF_TEXT));
    }
    buttonTxt.invalidate();
}

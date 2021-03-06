/* Copyright Statement:
 *
 */

#include <gui/setting_screen/SettingView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CommonUI.hpp>
#include <gui/common/CommonService.hpp>
#include <touchgfx/Color.hpp>

void SettingView::setupScreen()
{
    // Setup background
    background.setColor(Color::getColorFrom24BitRGB(0x35, 0x36, 0x30));
    background.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);

    // Add title
    titleTxt.setTypedText(TypedText(T_SETTINGS_TITLE));
    titleTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    titleTxt.setXY(119, 5);

    // Initialize list elements
    listElements[0].setupListElement(0, Bitmap(BITMAP_LIST_ELEMENT_0_INT_ID), TypedText(T_SET_TIME_TEXT));
    listElements[1].setupListElement(1, Bitmap(BITMAP_LIST_ELEMENT_1_INT_ID), TypedText(T_SET_DATE_TEXT));
    listElements[2].setupListElement(2, Bitmap(BITMAP_LIST_ELEMENT_2_INT_ID), TypedText(T_HEART_RATE_TEXT));

    for (uint8_t i = 0; i < numberOfListElements; ++i)
    {
        listElements[i].setAction(listElementClickedCallback);
        list.add(listElements[i]);
    }

    // Position and set the size of the scrollable container.
    // The width is the area is the list element width plus some extra
    // for space between element and scrollbar
    scrollCnt.setPosition(0, CommonUI::TITLE_HEIGHT + 5, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - CommonUI::TITLE_HEIGHT - 5);
    scrollCnt.add(list);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(background);
    add(titleTxt);
    add(scrollCnt);

    gotoMenuButton.setBitmaps(Bitmap(BITMAP_ICON_BACK_INT_ID), Bitmap(BITMAP_ICON_BACK_INT_ID));
    gotoMenuButton.setXY(10, 5);
    add(gotoMenuButton);
}

void SettingView::tearDownScreen()
{
}

void SettingView::handleKeyEvent(uint8_t key)
{
    if (CommonService::isBacklight() == true) {
        DemoView::handleKeyEvent(key);
        return;
    }

    DemoView::handleKeyEvent(key);

    presenter->backOptionMenuSelected();
}

void SettingView::listElementClicked(MenuListElement &element)
{
    presenter->menuSelected(element.getMenuIndex());
}

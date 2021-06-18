/* Copyright Statement:
 *
 */

#include <gui/setting_screen/MenuListElement.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/CommonUI.hpp>

MenuListElement::MenuListElement()
    : Container()
{
    clickAbort = false;
}

void MenuListElement::setupListElement(uint8_t index, const Bitmap &bmp, TypedText t)
{
    menuIndex = index;

    // Setup background
    imgBackground.setBitmap(bmp);
    imgBackground.setXY(8, 0);

    // Setup text
    listTxt.setTypedText(t);
    listTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    listTxt.setXY(88, 21);

    // Setup MenuListElement dimensions
    setHeight(imgBackground.getHeight() + 8);
    setWidth(imgBackground.getWidth() + 16);

    add(imgBackground);
    add(listTxt);

    setTouchable(true);
}

void MenuListElement::handleClickEvent(const ClickEvent &evt)
{
    // Inform the view of the event
    if (viewCallback->isValid() && evt.getType() == ClickEvent::RELEASED) {
        if (clickAbort == false) {
            viewCallback->execute(*this);
        } else {
            clickAbort = false;
        }
    }
}

void MenuListElement::handleDragEvent(const DragEvent &evt)
{
    if (abs(evt.getDeltaY()) > 0) {
        clickAbort = true;
    }
}

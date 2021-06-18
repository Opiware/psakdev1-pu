/* Copyright Statement:
 *
 */

#ifndef MENU_LIST_ELEMENT_HPP
#define MENU_LIST_ELEMENT_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/Bitmap.hpp>

using namespace touchgfx;

class SettingView;

/**
 * MenuListElement is the representation of each entry in our list.
 * The list element contains an image and a button. */
class MenuListElement : public Container
{
public:
    MenuListElement();

    /**
     * Initialize this containers widgets
     */
    void setupListElement(uint8_t index, const Bitmap &bmp, TypedText t);

    uint8_t getMenuIndex() const
    {
        return menuIndex;
    }

    /**
     * Setup the view callback
     */
    void setAction(GenericCallback< MenuListElement & > &callback)
    {
        viewCallback = &callback;
    }

    /**
     * Handle click events
     */
    virtual void handleClickEvent(const ClickEvent &evt);

    /**
    * Handle drag events
    */
    virtual void handleDragEvent(const DragEvent &evt);

private:
    uint8_t menuIndex;
    Image imgBackground;
    TextArea listTxt;
    bool clickAbort;

    /**
     * Callback that that notifies the creator of the list element of an event
     */
    GenericCallback< MenuListElement & > *viewCallback;
};

#endif /* MENU_LIST_ELEMENT_HPP */

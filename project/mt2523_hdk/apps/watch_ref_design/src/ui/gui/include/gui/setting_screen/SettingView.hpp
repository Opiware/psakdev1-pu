/* Copyright Statement:
 *
 */

#ifndef SETTING_VIEW_HPP
#define SETTING_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>

#include <gui/setting_screen/SettingPresenter.hpp>
#include <gui/setting_screen/MenuListElement.hpp>

/**
 * The View for a template screen. In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically. */
class SettingView : public DemoView<SettingPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    SettingView()
        : listElementClickedCallback(this, &SettingView::listElementClicked)
    {
    }

    virtual ~SettingView() {}

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen();

    virtual void handleKeyEvent(uint8_t key);

    /**
     * Handler of list element clicks.
     */
    void listElementClicked(MenuListElement &element);

private:
    static const int numberOfListElements = 3;

    Box background;
    TextArea titleTxt;
    ScrollableContainer scrollCnt;
    ListLayout list;

    MenuListElement listElements[numberOfListElements];

    // Callback that is assigned to each list element
    Callback<SettingView, MenuListElement &> listElementClickedCallback;
};

#endif // SETTING_VIEW_HPP

/* Copyright Statement:
 *
 */

#ifndef DEMO_VIEW_HPP
#define DEMO_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/common/DemoViewInterface.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/CommonService.hpp>

using namespace touchgfx;

template <class T>
class DemoView : public View<T>, public DemoViewInterface
{
public:
    DemoView() :
        onGotoMenuButtonClicked(this, &DemoView::gotoMenuClickedHandler),
        onGotoSettingButtonClicked(this, &DemoView::gotoSettingClickedHandler)
    {
        gotoMenuButton.setAction(onGotoMenuButtonClicked);
        gotoSettingButton.setAction(onGotoSettingButtonClicked);
    }

    virtual void handleClickEvent(const ClickEvent &evt)
    {
        View<T>::handleClickEvent(evt);

        CommonService::turnOnBacklight();
    }

    virtual void handleKeyEvent(uint8_t key)
    {
        View<T>::handleKeyEvent(key);

        CommonService::turnOnBacklight();
    }

protected:
    Button gotoMenuButton;
    Button gotoSettingButton;

    Callback<DemoView, const AbstractButton &> onGotoMenuButtonClicked;
    Callback<DemoView, const AbstractButton &> onGotoSettingButtonClicked;

    void gotoMenuClickedHandler(const AbstractButton &button)
    {
        View<T>::presenter->backOptionMenuSelected();
    }

    void gotoSettingClickedHandler(const AbstractButton &button)
    {
        View<T>::presenter->backOptionSettingSelected();
    }
};

#endif // DEMO_VIEW_HPP

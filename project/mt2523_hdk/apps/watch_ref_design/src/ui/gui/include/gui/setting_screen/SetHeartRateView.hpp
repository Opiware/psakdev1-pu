/* Copyright Statement:
 *
 */

#ifndef SET_HEART_RATE_VIEW_HPP
#define SET_HEART_RATE_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/setting_screen/SetHeartRatePresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>

class SetHeartRateView : public DemoView<SetHeartRatePresenter>
{
public:
    SetHeartRateView();
    virtual ~SetHeartRateView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleKeyEvent(uint8_t key);

private:
    Box background;
    TextArea titleTxt;
    TextArea buttonTxt;
    ToggleButton button;

    bool onState;

    Callback<SetHeartRateView, const AbstractButton &> onToggleButtonClicked;

    void toggleButtonClickedHandler(const AbstractButton &button);
};

#endif // SET_HEART_RATE_VIEW_HPP

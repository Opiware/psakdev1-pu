/* Copyright Statement:
 *
 */

#ifndef SET_TIME_VIEW_HPP
#define SET_TIME_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/setting_screen/SetTimePresenter.hpp>
#include <gui/setting_screen/TimePicker.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class SetTimeView : public DemoView<SetTimePresenter>
{
public:
    SetTimeView();
    virtual ~SetTimeView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleKeyEvent(uint8_t key);

    void saveAndGotoSettingClickedHandler(const AbstractButton &button);

private:
    TimePicker timePicker;
    TextArea titleTxt;
    Image background;

    Button saveAndGotoSettingButton;

    Callback<SetTimeView, const AbstractButton &> onSaveAndGotoSettingButtonClicked;
};

#endif // SET_TIME_VIEW_HPP

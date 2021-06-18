/* Copyright Statement:
 *
 */

#ifndef SET_DATE_VIEW_HPP
#define SET_DATE_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/setting_screen/SetDatePresenter.hpp>
#include <gui/setting_screen/DatePicker.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class SetDateView : public DemoView<SetDatePresenter>
{
public:
    SetDateView();
    virtual ~SetDateView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleKeyEvent(uint8_t key);

    void saveAndGotoSettingClickedHandler(const AbstractButton &button);

private:
    DatePicker datePicker;
    TextArea titleTxt;
    Image background;

    Button saveAndGotoSettingButton;

    Callback<SetDateView, const AbstractButton &> onSaveAndGotoSettingButtonClicked;
};

#endif // SET_DATE_VIEW_HPP

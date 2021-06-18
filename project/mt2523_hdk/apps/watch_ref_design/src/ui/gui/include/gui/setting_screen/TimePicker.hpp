/* Copyright Statement:
 *
 */

#ifndef TIME_PICKER_HPP
#define TIME_PICKER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/setting_screen/WheelSelector.hpp>
#include <gui/setting_screen/WheelSelectorExtra.hpp>

using namespace touchgfx;

/**
 * @class TimePicker
 *
 * @brief A time picker.
 *        Container with an hour and minute scrollable wheel.
 *
 * @see Container */
class TimePicker : public Container
{
public:
    TimePicker();
    virtual ~TimePicker();

    void setHour(int index, int duration, EasingEquation equation);
    int getHour();

    void setMinute(int index, int duration, EasingEquation equation);
    int getMinute();

    void reset();

protected:
    Image shadowOverlay;
    Image glassOverlay;

    WheelSelector hours;
    WheelSelector minutes;

    Callback<TimePicker, const WheelSelector &, const int &> onSelectedElementChanged;
    void selectedElementChangedHandler(const WheelSelector &wheel, const int &index);
};


#endif /* TIME_PICKER_HPP */

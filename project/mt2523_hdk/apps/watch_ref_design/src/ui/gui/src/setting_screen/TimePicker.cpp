/* Copyright Statement:
 *
 */

#include <gui/setting_screen/TimePicker.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CommonUI.hpp>

TimePicker::TimePicker() :
    onSelectedElementChanged(this, &TimePicker::selectedElementChangedHandler)
{
    colortype normalTextColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);
    colortype selectedTextColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);
    colortype selectedBackgroundColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);

#ifdef SET_DATETIME_USE_FONT_24
    hours.setXY(68, 5);
    hours.setup(32, 270, 0, 120, T_DATEPICKER_HOURS);
    hours.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 120, 32);
#else
    hours.setXY(68, 40);
    hours.setup(32, 200, 0, 80, T_DATEPICKER_HOURS);
    hours.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 80, 32);
#endif
    hours.setElementSelectedCallback(onSelectedElementChanged);
    add(hours);

#ifdef SET_DATETIME_USE_FONT_24
    minutes.setXY(220, 5);
    minutes.setup(32, 270, 0, 120, T_DATEPICKER_MINUTES);
    minutes.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 120, 32);
#else
    minutes.setXY(220, 40);
    minutes.setup(32, 200, 0, 80, T_DATEPICKER_MINUTES);
    minutes.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 80, 32);
#endif
    minutes.setElementSelectedCallback(onSelectedElementChanged);
    add(minutes);

    shadowOverlay.setBitmap(Bitmap(BITMAP_TIMEPICKER_SHADOW_OVERLAY_INT_ID));
    shadowOverlay.setXY(0, 0);
    add(shadowOverlay);

    glassOverlay.setBitmap(Bitmap(BITMAP_TIMEPICKER_GLASS_OVERLAY_INT_ID));
    glassOverlay.setXY(8, 105);
    add(glassOverlay);
}

TimePicker::~TimePicker()
{
}

void TimePicker::setHour(int index, int duration, EasingEquation equation)
{
    hours.setSelectedIndex(index, duration, equation);
}

int TimePicker::getHour()
{
    return hours.getSelectedIndex();
}

void TimePicker::setMinute(int index, int duration, EasingEquation equation)
{
    minutes.setSelectedIndex(index, duration, equation);
}

int TimePicker::getMinute()
{
    return minutes.getSelectedIndex();
}

void TimePicker::reset()
{
    hours.reset();
    minutes.reset();
}

void TimePicker::selectedElementChangedHandler(const WheelSelector &wheel, const int &index)
{
}

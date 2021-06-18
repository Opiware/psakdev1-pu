/* Copyright Statement:
 *
 */

#include <gui/setting_screen/DatePicker.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CommonUI.hpp>

DatePicker::DatePicker() :
    onSelectedElementChanged(this, &DatePicker::selectedElementChangedHandler)
{
    colortype normalTextColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);
    colortype selectedTextColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);
    colortype selectedBackgroundColor = Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF);

#ifdef SET_DATETIME_USE_FONT_24
    days.setXY(32, 5);
    days.setupDatePickerWheelDay(32, 270, 0, 120, T_DATEPICKER_DAY_28, T_DATEPICKER_DAY_29, T_DATEPICKER_DAY_30, T_DATEPICKER_DAY_31);
    days.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 120, 32);
#else
    days.setXY(32, 40);
    days.setupDatePickerWheelDay(32, 200, 0, 80, T_DATEPICKER_DAY_28, T_DATEPICKER_DAY_29, T_DATEPICKER_DAY_30, T_DATEPICKER_DAY_31);
    days.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 80, 32);
#endif
    add(days);

#ifdef SET_DATETIME_USE_FONT_24
    months.setXY(113, 5);
    months.setup(58, 270, 0, 120, T_DATEPICKER_MONTHS);
    months.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 120, 32);
#else
    months.setXY(113, 40);
    months.setup(58, 200, 0, 80, T_DATEPICKER_MONTHS);
    months.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 80, 32);
#endif
    months.setElementSelectedCallback(onSelectedElementChanged);
    add(months);

#ifdef SET_DATETIME_USE_FONT_24
    years.setXY(222, 5);
    years.setup(64, 270, 0, 120, T_DATEPICKER_YEARS);
    years.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 120, 32);
#else
    years.setXY(222, 40);
    years.setup(64, 200, 0, 80, T_DATEPICKER_YEARS);
    years.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 80, 32);
#endif
    years.setElementSelectedCallback(onSelectedElementChanged);
    add(years);

    shadowOverlay.setBitmap(Bitmap(BITMAP_DATEPICKER_SHADOW_OVERLAY_INT_ID));
    shadowOverlay.setXY(0, 0);
    add(shadowOverlay);

    glassOverlay.setBitmap(Bitmap(BITMAP_DATEPICKER_GLASS_OVERLAY_INT_ID));
    glassOverlay.setXY(8, 105);
    add(glassOverlay);
}

DatePicker::~DatePicker()
{
}

void DatePicker::setDay(int index, int duration, EasingEquation equation)
{
    days.setSelectedIndex(index, duration, equation);
}

int DatePicker::getDay()
{
    return days.getSelectedIndex();
}

void DatePicker::setMonth(int index, int duration, EasingEquation equation)
{
    months.setSelectedIndex(index, duration, equation);
}

int DatePicker::getMonth()
{
    return months.getSelectedIndex();
}

void DatePicker::setYear(int index, int duration, EasingEquation equation)
{
    years.setSelectedIndex(index, duration, equation);
}

int DatePicker::getYear()
{
    return years.getSelectedIndex();
}

void DatePicker::reset()
{
    days.reset();
    months.reset();
    years.reset();
}

void DatePicker::selectedElementChangedHandler(const WheelSelector &wheel, const int &index)
{
    // Adjust the number of days in the selected month/year
    int numberOfDaysInMonth = getNumberOfDays(months.getSelectedIndex() + 1, START_YEAR + years.getSelectedIndex());

    if (numberOfDaysInMonth == 28) {
        days.fadeExtraText(0, 0, 16);
        days.fadeExtraText(1, 0, 16);
        days.fadeExtraText(2, 0, 16);
        if (days.getSelectedIndex() > 27) {
            days.setSelectedIndex(27, 20);
        }
    } else if (numberOfDaysInMonth == 29) {
        days.fadeExtraText(0, 255, 16);
        days.fadeExtraText(1, 0, 16);
        days.fadeExtraText(2, 0, 16);
        if (days.getSelectedIndex() > 28) {
            days.setSelectedIndex(28, 20);
        }
    } else if (numberOfDaysInMonth == 30) {
        days.fadeExtraText(0, 255, 16);
        days.fadeExtraText(1, 255, 16);
        days.fadeExtraText(2, 0, 16);
        if (days.getSelectedIndex() > 29) {
            days.setSelectedIndex(29, 20);
        }
    } else {
        days.fadeExtraText(0, 255, 16);
        days.fadeExtraText(1, 255, 16);
        days.fadeExtraText(2, 255, 16);
    }
}

uint16_t DatePicker::getNumberOfDays(uint16_t month, uint16_t year)
{
    uint16_t result = 0;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        result = 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        result = 30;
    } else if (month == 2) {
        result = 28;
        if (year % 400 == 0) {
            result++;
        } else if (year % 100 == 0) {
        } else if (year % 4 == 0) {
            result++;
        }
    }
    return result;
}

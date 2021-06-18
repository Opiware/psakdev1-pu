/* Copyright Statement:
 *
 */

#ifndef MT2523ITOUCHCONTROLLER_HPP
#define MT2523ITOUCHCONTROLLER_HPP

#include <platform/driver/touch/TouchController.hpp>

namespace touchgfx
{
class mt2523TouchController: public TouchController
{
    virtual void init();
    virtual bool sampleTouch(int32_t& x, int32_t& y);
};
}

#endif // MT2523ITOUCHCONTROLLER_HPP


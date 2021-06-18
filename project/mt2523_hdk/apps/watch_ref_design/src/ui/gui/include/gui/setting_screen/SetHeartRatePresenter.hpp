/* Copyright Statement:
 *
 */

#ifndef SET_HEART_RATE_PRESENTER_HPP
#define SET_HEART_RATE_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class SetHeartRateView;

class SetHeartRatePresenter : public DemoPresenter
{
public:
    SetHeartRatePresenter(SetHeartRateView &v);
    virtual ~SetHeartRatePresenter();

    virtual void activate();
    virtual void deactivate();

private:
    SetHeartRatePresenter();

    SetHeartRateView &view;
};

#endif // SET_HEART_RATE_PRESENTER_HPP

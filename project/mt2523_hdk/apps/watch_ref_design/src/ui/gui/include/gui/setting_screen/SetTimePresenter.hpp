/* Copyright Statement:
 *
 */

#ifndef SET_TIME_PRESENTER_HPP
#define SET_TIME_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class SetTimeView;

class SetTimePresenter : public DemoPresenter
{
public:
    SetTimePresenter(SetTimeView &v);
    virtual ~SetTimePresenter();

    virtual void activate();
    virtual void deactivate();

private:
    SetTimePresenter();

    SetTimeView &view;
};

#endif // SET_TIME_PRESENTER_HPP

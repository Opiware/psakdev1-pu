/* Copyright Statement:
 *
 */

#ifndef SET_DATE_PRESENTER_HPP
#define SET_DATE_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class SetDateView;

class SetDatePresenter : public DemoPresenter
{
public:
    SetDatePresenter(SetDateView &v);
    virtual ~SetDatePresenter();

    virtual void activate();
    virtual void deactivate();

private:
    SetDatePresenter();

    SetDateView &view;
};

#endif // SET_DATE_PRESENTER_HPP

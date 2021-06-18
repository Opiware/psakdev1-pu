/* Copyright Statement:
 *
 */

#include <new>
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <gui/main_menu_screen/MainMenuView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <gui/setting_screen/SettingView.hpp>
#include <gui/setting_screen/SettingPresenter.hpp>
#include <gui/setting_screen/SetTimeView.hpp>
#include <gui/setting_screen/SetTimePresenter.hpp>
#include <gui/setting_screen/SetDateView.hpp>
#include <gui/setting_screen/SetDatePresenter.hpp>
#include <gui/setting_screen/SetHeartRateView.hpp>
#include <gui/setting_screen/SetHeartRatePresenter.hpp>

FrontendApplication::FrontendApplication(Model &m, FrontendHeap &heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::gotoMainMenuScreenNoTransition()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuScreenNoTransitionImpl()
{
    makeTransition< MainMenuView, MainMenuPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainMenuScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuScreenImpl()
{
    makeTransition< MainMenuView, MainMenuPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::backMainMenuScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::backMainMenuScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::backMainMenuScreenImpl()
{
    makeTransition< MainMenuView, MainMenuPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSettingScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSettingScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSettingScreenImpl()
{
    makeTransition< SettingView, SettingPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::backSettingScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::backSettingScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::backSettingScreenImpl()
{
    makeTransition< SettingView, SettingPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSetTimeScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSetTimeScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSetTimeScreenImpl()
{
    makeTransition< SetTimeView, SetTimePresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSetDateScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSetDateScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSetDateScreenImpl()
{
    makeTransition< SetDateView, SetDatePresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSetHeartRateScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSetHeartRateScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSetHeartRateScreenImpl()
{
    makeTransition< SetHeartRateView, SetHeartRatePresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

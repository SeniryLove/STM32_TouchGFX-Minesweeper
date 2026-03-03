#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void Button_Pressed_0();
    virtual void Button_Pressed_1();
    virtual void Button_Pressed_2();
    virtual void Button_Pressed_3();
    virtual void Button_Pressed_4();
    virtual void Button_Pressed_5();
    virtual void Button_Pressed_6();
    virtual void Button_Pressed_7();
    virtual void Button_Pressed_8();
    virtual void Button_Pressed_9();
    virtual void Button_Pressed_C();
    virtual void Button_Pressed_E();
    virtual void AppendNumber(int num);
protected:
    int mineNumber = 5;
};

#endif // SCREEN1VIEW_HPP

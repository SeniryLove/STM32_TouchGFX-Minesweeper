#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <stdlib.h>

extern uint32_t RandNumber[99];
extern bool isReading;

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void sweepMine(int row,int col);
    virtual bool isMine(int row,int col);
    virtual bool isAroundMine(int row,int col);
    virtual void getRandom();
private:
    touchgfx::Callback<Screen2View, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);
protected:
    touchgfx::BoxWithBorderButtonStyle<touchgfx::ClickButtonTrigger> button[8][15];
    touchgfx::BoxWithBorder backgroundBox[8][15];
    touchgfx::ScalableImage image[8][15];
    touchgfx::TextAreaWithOneWildcard aroundBump[8][15];
    touchgfx::TextAreaWithOneWildcard result;
    touchgfx::BoxWithBorder resultBox;
    static const uint16_t TEXTAREA_SIZE = 3;
    static const uint16_t RESULT_TEXT_SIZE = 5;
    touchgfx::Unicode::UnicodeChar aroundBumpText[8][15][TEXTAREA_SIZE];
    touchgfx::Unicode::UnicodeChar resultText[RESULT_TEXT_SIZE];
    bool isBump[8][15];
    bool isPressed[8][15];
    int aroundBumpNumber[8][15];
    int*randomNumber;
    int mineNumber;
    int randNumber;
    bool isExist;
    int tickCount = 0;
    int pressPosX = 0;
    int pressPosY = 0;
    bool Bumped = false;
    bool Win = false;
    int secCount = 0;
    int minCount = 0;
};

#endif // SCREEN2VIEW_HPP

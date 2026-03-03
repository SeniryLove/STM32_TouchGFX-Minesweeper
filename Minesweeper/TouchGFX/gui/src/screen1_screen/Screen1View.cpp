#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
	if(presenter->getMineNumber() > 5)
	{
		mineNumber = presenter->getMineNumber();
		Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%02d",mineNumber);
		textArea1.invalidate();
	}
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::AppendNumber(int num)
{
	switch(num)
	{
		case 10:
		{
			mineNumber = 0;
		}break;
		case 11:
		{
			if(mineNumber >= 5)
			{
				presenter->saveMineNumber(mineNumber);
				application().gotoScreen2ScreenWipeTransitionSouth();
			}
		}break;
		default:
		{
			mineNumber = ((mineNumber * 10) + num)%100;
		}break;
	}

	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%02d",mineNumber);
	textArea1.invalidate();
}

void Screen1View::Button_Pressed_0()
{
	AppendNumber(0);
}
void Screen1View::Button_Pressed_1()
{
	AppendNumber(1);
}
void Screen1View::Button_Pressed_2()
{
	AppendNumber(2);
}
void Screen1View::Button_Pressed_3()
{
	AppendNumber(3);
}
void Screen1View::Button_Pressed_4()
{
	AppendNumber(4);
}
void Screen1View::Button_Pressed_5()
{
	AppendNumber(5);
}
void Screen1View::Button_Pressed_6()
{
	AppendNumber(6);
}
void Screen1View::Button_Pressed_7()
{
	AppendNumber(7);
}
void Screen1View::Button_Pressed_8()
{
	AppendNumber(8);
}
void Screen1View::Button_Pressed_9()
{
	AppendNumber(9);
}
void Screen1View::Button_Pressed_C()
{
	AppendNumber(10);
}
void Screen1View::Button_Pressed_E()
{
	AppendNumber(11);
}

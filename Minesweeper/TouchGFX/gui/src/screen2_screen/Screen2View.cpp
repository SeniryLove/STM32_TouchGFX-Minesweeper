#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View():flexButtonCallback(this, &Screen2View::flexButtonCallbackHandler)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<15;j++)
		{
			backgroundBox[i][j].setPosition(30+28*j,40+28*i,28,28);
			backgroundBox[i][j].setColor(touchgfx::Color::getColorFromRGB(0, 56, 122));
			backgroundBox[i][j].setBorderColor(touchgfx::Color::getColorFromRGB(0, 51, 102));
			backgroundBox[i][j].setBorderSize(2);
			add(backgroundBox[i][j]);
			resultBox.setBorderSize(2);
			resultBox.setPosition(240-25,136-14,50,28);
			resultBox.setColor(touchgfx::Color::getColorFromRGB(122, 122, 122));
			resultBox.setBorderColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			resultBox.setBorderSize(2);
			result.setPosition(240-25,136-14,50,28);
			result.setColor(touchgfx::Color::getColorFromRGB(255,255,255));
			result.setLinespacing(0);
			result.setTypedText(TypedText(0));
			aroundBump[i][j].setPosition(30+28*j,40+28*i,28,28);
			aroundBump[i][j].setColor(touchgfx::Color::getColorFromRGB(255,255,255));
			aroundBump[i][j].setLinespacing(0);
			aroundBump[i][j].setTypedText(TypedText(0));
			image[i][j].setBitmap(touchgfx::Bitmap(BITMAP_STARBURSTSTREAM_ICON_ID));
			image[i][j].setPosition(30+28*j,40+28*i,28,28);
			button[i][j].setBoxWithBorderPosition(0,0,28,28);
			button[i][j].setBorderSize(2);
			button[i][j].setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
			button[i][j].setPosition(30+28*j,40+28*i,28,28);
			button[i][j].setAction(flexButtonCallback);
			add(button[i][j]);
		}
	}
}

void Screen2View::handleTickEvent()
{
	if(!Bumped && !Win)
	{
		if(tickCount >= 60)
		{
			tickCount = 0;
			if(secCount >= 60)
			{
				secCount = 0;
				minCount++;
			}
			else
			{
				secCount++;
			}
			Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%02d:%02d", minCount,secCount);
			textArea2.invalidate();
		}
		else
		{
			tickCount++;
		}
	}
}

void Screen2View::getRandom()
{
	isReading = true;
	for(int i=0;i<mineNumber;i++)
	{
		*(randomNumber + i) = RandNumber[i];
	}
	isReading = false;
}

void Screen2View::setupScreen()
{
	mineNumber = presenter->getMineNumber();
	tickCount = 0;
	secCount = 0;
	minCount = 0;
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%02d", mineNumber);
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%02d:%02d", minCount,secCount);
	textArea1.invalidate();
	textArea2.invalidate();
	Bumped = false;
	if(mineNumber > -1)
	{
		randomNumber = (int*)malloc(sizeof(int) * mineNumber);
		for(int i=0;i<mineNumber;i++)
		{
			*(randomNumber + i) = -1;
		}
		getRandom();
		for(int i=0;i<mineNumber;i++)
		{
			remove(button[*(randomNumber + i)/15][*(randomNumber + i)%15]);
			add(image[*(randomNumber + i)/15][*(randomNumber + i)%15]);
			add(button[*(randomNumber + i)/15][*(randomNumber + i)%15]);
		}
		for(int i=0;i<120;i++)
		{
			isBump[i/15][i%15] = false;
			for(int j=0;j<mineNumber;j++)
			{
				if(i == *(randomNumber + j))
				{
					isBump[i/15][i%15] = true;
					break;
				}
			}
		}
		for(int i=0;i<120;i++)
		{
			if(!isBump[i/15][i%15])
			{
				aroundBumpNumber[i/15][i%15] = 0;
				for(int n=-1;n<=1;n++)
				{
					for(int m=-1;m<=1;m++)
					{
						if((m!=0 || n!=0) && (i/15+n)>=0 && (i/15+n) < 8 && (i%15+m) >= 0 && (i%15+m) < 15)
						{
							if(isBump[i/15+n][i%15+m])
							{
								aroundBumpNumber[i/15][i%15]++;
							}
						}
					}
				}
				if(aroundBumpNumber[i/15][i%15])
				{
					Unicode::snprintf(aroundBumpText[i/15][i%15],TEXTAREA_SIZE, "%1d", aroundBumpNumber[i/15][i%15]);
					aroundBump[i/15][i%15].setWildcard(aroundBumpText[i/15][i%15]);
					remove(button[i/15][i%15]);
					add(aroundBump[i/15][i%15]);
					add(button[i/15][i%15]);
					aroundBump[i/15][i%15].invalidate();
				}
			}
		}
	}
	Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
	free(randomNumber);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<15;j++)
		{
			isBump[i][j] = false;
			isPressed[i][j] = false;
		}
	}
	mineNumber = 0;
	randNumber = 0;
	isExist = false;
	tickCount = 0;
	pressPosX = 0;
	pressPosY = 0;
	Bumped = false;
	Win = false;
	secCount = 0;
	minCount = 0;
	tickCount = 0;
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::sweepMine(int row,int col)
{
	if(row < 0 || row >=8 || col < 0 || col >= 15)
	{
		return;
	}
	else if(isMine(row,col))
	{
		if(row == pressPosX && col == pressPosY)
		{
			Bumped = true;
			Unicode::snprintf(resultText, RESULT_TEXT_SIZE, "Fail");
			result.setWildcard(resultText);
			add(resultBox);
			add(result);
			result.invalidate();
			for(int i=0;i<mineNumber;i++)
			{
				remove(button[*(randomNumber + i)/15][*(randomNumber + i)%15]);
				Screen2View::invalidate();
			}
		}
		else
		{
			return;
		}
	}
	else if(isAroundMine(row,col))
	{
		remove(button[row][col]);
		Screen2View::invalidate();
		isPressed[row][col] = true;
		return;
	}
	else
	{
		if(!isPressed[row][col])
		{
			remove(button[row][col]);
			Screen2View::invalidate();
			isPressed[row][col] = true;
			sweepMine(row-1,col);
			sweepMine(row+1,col);
			sweepMine(row,col-1);
			sweepMine(row,col+1);
			sweepMine(row-1,col-1);
			sweepMine(row+1,col+1);
			sweepMine(row-1,col+1);
			sweepMine(row+1,col-1);
		}
		else
		{
			return;
		}
	}
}

bool Screen2View::isMine(int row,int col)
{
	bool isExist = false;
	for(int i=0;i<mineNumber;i++)
	{
		if(row == *(randomNumber + i) / 15 && col == *(randomNumber + i)%15)
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

bool Screen2View::isAroundMine(int row,int col)
{
	return aroundBumpNumber[row][col] > 0;
}

void Screen2View::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<15;j++)
		{
			if ((&src == &button[i][j]) && !Bumped && !Win)
			{
				pressPosX = i;
				pressPosY = j;
				sweepMine(i,j);
				bool allClean = true;
				for(int k=0;k<120;k++)
				{
					if(!isPressed[k/15][k%15])
					{
						if(!isBump[k/15][k%15])
						{
							allClean = false;
							break;
						}
					}
				}
				if(allClean)
				{
					Win = true;
					Unicode::snprintf(resultText, RESULT_TEXT_SIZE, "Win");
					result.setWildcard(resultText);
					add(resultBox);
					add(result);
					result.invalidate();
				}
			}
		}
	}
}

#include "MovingButton.h"
#include "header.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
MovingButton::MovingButton(efylw5Engine* ptrEngine, int iMapX, int iMapY)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{
	moved = false;
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;


	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	xDecrement = 0;
	yDecrement = 0;
	xDecrementWord = 0;
	yDecrementWord = 0;

	fontSize = 25;
	setVisible(true);
}

MovingButton::~MovingButton(void)
{
}

void MovingButton::virtDraw()
{
	if (!isVisible())
		return;

	char buf[128];
	sprintf(buf, "CREDITS!!!!!");
	FontManager fmanager;
	fmanager.loadFonts();
	ptrEngine->drawForegroundRectangle(600 - xDecrement , 600 - yDecrement , 750 , 650 , 0x0000FF);
	ptrEngine->drawForegroundString(600 - xDecrementWord, 610 - yDecrementWord, buf, 0x000000, fmanager.getFont("Cornerstone Regular.ttf", fontSize));
	redrawDisplay();
}

void MovingButton::virtDoUpdate(int iCurrentTime)
{
	if (!moved && (ptrEngine->getCurrentMouseX() >= 600 && ptrEngine->getCurrentMouseX() <= 750) && (ptrEngine->getCurrentMouseY() >= 600 && ptrEngine->getCurrentMouseY() <= 650))
	{
		moved = true;
		xDecrement -= 40;
		yDecrement -= 40;
		xDecrementWord -= 60;
		yDecrementWord -= 30;
		fontSize -= 15;
		redrawDisplay();

	}
}



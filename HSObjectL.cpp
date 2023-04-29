#include "HSObjectL.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"


HSObjectL::HSObjectL(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{

	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;


	setAnimationStartX(startX);
	setAnimationStartY(startY);
	setAnimationEndX(endX);
	setAnimationEndY(endY);
	setVisible(true);
	vis = true;

}

HSObjectL::~HSObjectL(void)
{
}

/**
	Class: HSObjectL
	Function: virtDraw()
	Description: This is used to call drawEffect if vis is true
*/
void HSObjectL::virtDraw()
{
	if (vis) {
		drawEffect();
	}
}

/**
	Class: HSObjectL
	Function: virtDoUpdate()
	Param: int iCurrentTime
	Description: This is used to setup movement using the MovementPosition
				 class. If it detects r is being clicked, which means going back
				 to the main menu, it will store the value false into vis, which
				 will effectly terminates the effects.
*/
void HSObjectL::virtDoUpdate(int iCurrentTime)
{
	if (ptrEngine->isKeyPressed(SDLK_r)) {
		vis = false;
		return;
	}
	if (mp.hasMovementFinished(iCurrentTime))
	{
		mp.setup(getAnimationStartX(), getAnimationStartY(), getAnimationEndX(), getAnimationEndY(), iCurrentTime, iCurrentTime + 500);
	}

	else {
		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();
	}
	redrawDisplay();
}

/**
	Class: HSObjectL
	Function: drawEffect()
	Description: This will be called by virtDraw() when vis is true.
				 It will create a tunnelish like effect on the left side
				 of the table
*/
void HSObjectL::drawEffect()
{
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY - 10, m_iCurrentScreenX + 100, m_iCurrentScreenY + 50, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 70, m_iCurrentScreenX + 100, m_iCurrentScreenY + 110, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 150, m_iCurrentScreenX + 100, m_iCurrentScreenY + 170, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 220, m_iCurrentScreenX + 100, m_iCurrentScreenY + 220, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 290, m_iCurrentScreenX + 100, m_iCurrentScreenY + 270, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 360, m_iCurrentScreenX + 100, m_iCurrentScreenY + 320, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 430, m_iCurrentScreenX + 100, m_iCurrentScreenY + 380, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 500, m_iCurrentScreenX + 100, m_iCurrentScreenY + 430, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 570, m_iCurrentScreenX + 100, m_iCurrentScreenY + 490, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 640, m_iCurrentScreenX + 100, m_iCurrentScreenY + 540, 0x00FF00, 10);
}

#include "HSObjectR.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

HSObjectR::HSObjectR(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY)
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

HSObjectR::~HSObjectR(void)
{
}

/**
	Class: HSObjectR
	Function: virtDraw()
	Description: This is used to call drawEffect if vis is true
*/
void HSObjectR::virtDraw()
{
	if (vis) {
		drawEffect();
	}
}

/**
	Class: HSObjectR
	Function: virtDoUpdate()
	Param: int iCurrentTime
	Description: This is used to setup movement using the MovementPosition
				 class. If it detects r is being clicked, which means going back
				 to the main menu, it will store the value false into vis, which
				 will effectly terminates the effects.
*/
void HSObjectR::virtDoUpdate(int iCurrentTime)
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
	Class: HSObjectR
	Function: drawEffect()
	Description: This will be called by virtDraw() when vis is true.
				 It will create a tunnelish like effect on the right side
				 of the table
*/
void HSObjectR::drawEffect()
{
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 60, m_iCurrentScreenX + 100, m_iCurrentScreenY + 0, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 120, m_iCurrentScreenX + 100, m_iCurrentScreenY + 80, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 180, m_iCurrentScreenX + 100, m_iCurrentScreenY + 140, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 240, m_iCurrentScreenX + 100, m_iCurrentScreenY + 220, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 300, m_iCurrentScreenX + 100, m_iCurrentScreenY + 320, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 360, m_iCurrentScreenX + 100, m_iCurrentScreenY + 410, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 420, m_iCurrentScreenX + 100, m_iCurrentScreenY + 490, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 480, m_iCurrentScreenX + 100, m_iCurrentScreenY + 560, 0x00FF00, 10);
	ptrEngine->drawForegroundThickLine(m_iCurrentScreenX - 10, m_iCurrentScreenY + 540, m_iCurrentScreenX + 100, m_iCurrentScreenY + 630, 0x00FF00, 10);
}




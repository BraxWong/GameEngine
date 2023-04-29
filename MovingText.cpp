#include "MovingText.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

MovingText::MovingText(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{
	strVec = { "OH MY GOD " + ptrEngine->getName() + " !!!!", ptrEngine->getName() + " IS SOOOO GOOD!!!!", 
		ptrEngine->getName() + " IS HIM!!!!", "I SEE THE DAWG IN " + ptrEngine->getName() + "!!!!" };
	
	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;


	setAnimationStartX(startX);
	setAnimationStartY(startY);
	setAnimationEndX(endX);
	setAnimationEndY(endY);

	setVisible(true);
}

MovingText::~MovingText(void)
{
}

/**
	Class: MovingText
	Function: virtDraw()
	Description: This is used to display the elements within strvec on the screen.
*/

void MovingText::virtDraw()
{
	if (vis)
	{
		
		char buf[124];
		for (std::string s : strVec)
		{
			int ran = rand() % colorVec.size();
			sprintf(buf, s.c_str());
			ptrEngine->drawForegroundString(m_iCurrentScreenX, m_iCurrentScreenY, buf, colorVec[ran], NULL);
			m_iCurrentScreenX -= 100;
			m_iCurrentScreenY -= 100;
		}
		
	}
}

/**
	Class: MovingText
	Function: virtDoUpdate()
	Description: This is used to commence the movement of the string
			     using the MovementPosition object.
*/
void MovingText::virtDoUpdate(int iCurrentTime)
{

	if (ptrEngine->isKeyPressed(SDLK_r)) {
		vis = false;
		return;
	}
	if (mp.hasMovementFinished(iCurrentTime))
	{
		mp.setup(0, 300, 1300, 300, iCurrentTime, iCurrentTime + 1500);
	}
	else {
		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();
	}
	redrawDisplay();
	
}



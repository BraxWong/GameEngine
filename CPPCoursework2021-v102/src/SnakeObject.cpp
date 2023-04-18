#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

SnakeObject::SnakeObject(efylw5Engine* ptrEngine, int iMapX, int iMapY)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
	, collision(false)
{

	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;


	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;


	setVisible(true);
}

SnakeObject::~SnakeObject(void)
{

}


void SnakeObject::virtDraw()
{
	if (!isVisible() || be->isPaused())
		return;


	int iSize = 10;

	if (collision) {

		collision = false;
		char buf[128];
		sprintf(buf, "CONTACT!");
		ptrEngine->drawForegroundString(m_iCurrentScreenX + 100, m_iCurrentScreenY, buf, 0x00ffff, NULL);
		redrawDisplay();
	}

	ptrEngine->drawForegroundRectangle(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, 0x00ffff);
	redrawDisplay();

}

void SnakeObject::virtDoUpdate(int iCurrentTime)
{
	// Do not update if it should not be visible or program is paused
	if (!isVisible() || be->isPaused())
		return;

	DisplayableObject* pObject;

	//Searching for the rectangle and other objects by iterating the engine's getDisplayableObject()
	for (int iObjectId = 0; (pObject = ptrEngine->getDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		if (pObject == this)
			continue;
		if (pObject == nullptr)
			continue;

		int iSize = 10;



		if (CollisionDetection::checkRectangles(pObject->getDrawingRegionLeft() - iSize + 10, pObject->getDrawingRegionRight() + iSize - 10,
			pObject->getDrawingRegionTop() - iSize + 10, pObject->getDrawingRegionBottom() + iSize - 10,
			m_iCurrentScreenX - iSize, m_iCurrentScreenX + iSize,
			m_iCurrentScreenY - iSize, m_iCurrentScreenY + iSize))
		{

			//Setting collision true will activate virtDraw() if(collision) statement
			collision = true;
			redrawDisplay();

			return;

		}

	}
	//Checks whether the movement of the rectangle has finished. If it has, it will restart the movement
	//using movementPosition class
	if (mp.hasMovementFinished(iCurrentTime))
	{


		mp.setup(rand() % 400, rand() % 400, rand() % 400, rand() % 400, iCurrentTime, iCurrentTime + 3400);

	}

	//Calculating the position of the rectangle using movementPosition::calculate()
	//Then setting m_iCurrentScreenX and m_iCurrentScreenY with the current location
	else {

		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();

	}

	redrawDisplay();
}

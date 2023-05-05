#include "BlackTargets.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"

BlackTargets::BlackTargets(efylw5Engine* ptrEngine, Timer* timer, int iMapX, int iMapY, int difficulty, int shape)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
	, timer(timer)
{
	setShape(shape);
	setDifficulty(difficulty);
	setSpeed();

	hit = false;
	pointLock = false;
	setMovementSettings();

	bounceUp = true;
	bounceDown = false;

	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;


	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	setVisible(true);

}

BlackTargets::~BlackTargets(void)
{

}
void BlackTargets::setMovementSettings()
{
	movementSettings = { rand() % 1300, rand() % 800, rand() % 4 };
}

void BlackTargets::virtKeyDown(int iKeyCode)
{

}

void BlackTargets::setMovement(int iCurrentTime)
{
	if (bounceUp) {

		//left to right
		if (movementSettings[2] == 0)
		{
			mp.setup(0, movementSettings[1], movementSettings[0], movementSettings[1], iCurrentTime, iCurrentTime + getSpeed());
		}
		//right to left
		else if (movementSettings[2] == 1)
		{
			mp.setup(1300, movementSettings[1], movementSettings[0], movementSettings[1], iCurrentTime, iCurrentTime + getSpeed());
		}
		//Down to Up
		else if (movementSettings[2] == 2)
		{
			mp.setup(movementSettings[0], 800, movementSettings[0], movementSettings[1], iCurrentTime, iCurrentTime + getSpeed());
		}
		//Up to Down
		else
		{
			mp.setup(movementSettings[0], 0, movementSettings[0], movementSettings[1], iCurrentTime, iCurrentTime + getSpeed());
		}
		bounceUp = false;
	}
	else {
		mp.reverse();
		bounceUp = true;

	}
}

void BlackTargets::setSpeed()
{
	//EASY SPEED = 6400
	if (getDifficulty() == 1)
		speed = 6400;
	//MEDIUM SPEED = 5400
	if (getDifficulty() == 2)
		speed = 5400;
	//HARD SPEED = 4400
	if (getDifficulty() == 3)
		speed = 4400;
}

void BlackTargets::printCurrentLocation()
{
	std::cout << "Left: " << getDrawingRegionLeft() << " Bottom: " << getDrawingRegionBottom() << " Top: " << getDrawingRegionTop() << " Right: " << getDrawingRegionRight() << "\n";
}


void BlackTargets::virtDraw()
{

	if (!isVisible() || timer->getTimesUp()|| hit)
		return;

	int iSize = 10;
	if (getShape() == 1)
	{
		ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, 0x000000);
	}
	else
	{
		ptrEngine->drawForegroundRectangle(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, 0x000000);
	}
	
	//Handle "Collision between mouse coordinates and the target's location
	if (!ptrEngine->getMouseLifted()) {

		if (getDrawingRegionRight() - 40 > ptrEngine->getMouseXClickedDown() && ptrEngine->getMouseXClickedDown() > getDrawingRegionLeft())
		{
			if (getDrawingRegionBottom() - 40 > ptrEngine->getMouseYClickedDown() && ptrEngine->getMouseYClickedDown() > getDrawingRegionTop())
			{
				hit = true;

				if (!pointLock)
				{
					ptrEngine->setPoint(ptrEngine->getPoint()  - 20);
					hit = true;
					pointLock = true;
				}
			}
		}
		else
		{
			std::cout << "MISS\n";
		}
	}
	else {
		pointLock = false;
	}
	redrawDisplay();

}

void BlackTargets::virtDoUpdate(int iCurrentTime)
{

	// Do not update if it should not be visible or program is paused
	if (!isVisible() || ptrEngine->isPaused())
		return;



	//Movement has completed without user hitting the target
	if (mp.hasMovementFinished(iCurrentTime))
	{
		setMovementSettings();
		setMovement(iCurrentTime);
	}
	//Movement is still on going
	else {
		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();
	}

	redrawDisplay();
}
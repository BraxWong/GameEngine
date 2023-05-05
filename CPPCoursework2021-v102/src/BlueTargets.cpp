#include "BlueTargets.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"

BlueTargets::BlueTargets(efylw5Engine* ptrEngine, Timer* timer, int iMapX, int iMapY, int color, int difficulty, int shape)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
	, timer(timer)
{

	setShape(shape);
	setColor(color);
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

BlueTargets::~BlueTargets(void)
{

}
void BlueTargets::setMovementSettings()
{
	movementSettings = { rand() % 1300, rand() % 800, rand() % 4 };
}

void BlueTargets::setColor(int c)
{
	if (c == 1)
	{
		color = 0x964B00;
	}
	else if (c == 2)
	{
		color = 0xFFE5B4;
	}
	else if (c == 3)
	{
		color = 0x704214;
	}
	else
	{
		color = 0x0000FF;
	}
}

void BlueTargets::setSpeed()
{
	//EASY SPEED = 5400
	if (getDifficulty() == 1)
		speed = 5400;
	//MEDIUM SPEED = 4400
	if (getDifficulty() == 2)
		speed = 4400;
	//HARD SPEED = 3400
	if (getDifficulty() == 3)
		speed = 3400;
}

void BlueTargets::virtKeyDown(int iKeyCode)
{

}

void BlueTargets::setMovement(int iCurrentTime)
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

void BlueTargets::printCurrentLocation()
{
	std::cout << "Left: " << getDrawingRegionLeft() << " Bottom: " << getDrawingRegionBottom() << " Top: " << getDrawingRegionTop() << " Right: " << getDrawingRegionRight() << "\n";
}


void BlueTargets::virtDraw()
{
	if (!isVisible() || timer->getTimesUp() || hit)
		return;

	int iSize = 10;
	if (getShape() == 1)
	{
		ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, color);
	}
	else
	{
		ptrEngine->drawForegroundRectangle(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, color);
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
					ptrEngine->setPoint(ptrEngine->getPoint() + 20);
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

void BlueTargets::virtDoUpdate(int iCurrentTime)
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

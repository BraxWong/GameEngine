#include "Targets.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

Targets::Targets(efylw5Engine* ptrEngine, int iMapX, int iMapY)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
{

	setEndX(rand() % 1300);
	setEndY(rand() % 800);
	setIDir(rand() % 4);

	bounceUp = true;
	bounceDown = false;
	points = 0;
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;


	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	setVisible(true);
}

Targets::~Targets(void)
{

}
void Targets::virtKeyDown(int iKeyCode)
{

}

void Targets::printCurrentLocation()
{
	std::cout << "Left: " << getDrawingRegionLeft() << " Bottom: " << getDrawingRegionBottom() << " Top: " << getDrawingRegionTop() << " Right: " << getDrawingRegionRight() << "\n";
}


void Targets::virtDraw()
{

	if (!isVisible())
		return;

	

	int iSize = 10;

	ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, 0x00FF00);
	ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize + 100, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1 + 100, m_iCurrentScreenY + iSize - 1, 0x00FF00);
	ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize + 200, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1 + 200, m_iCurrentScreenY + iSize - 1, 0x00FF00);
	ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize + 200, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1 + 200, m_iCurrentScreenY + iSize - 1, 0x00FF00);

	if (ptrEngine->getCurrentState()->getState() == 3) {

		static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		static std::chrono::steady_clock::time_point end = start + std::chrono::seconds(300);

		char buf[128];
		sprintf(buf, std::to_string(getPoints()).c_str());
		ptrEngine->drawForegroundString(200, 0, buf, 0x00ffff, NULL);

		if (std::chrono::steady_clock::now() < end) {
			char time[128];
			auto remaining = std::chrono::duration_cast<std::chrono::seconds>(end - std::chrono::steady_clock::now());
			int minutes = remaining.count() / 60;
			int seconds = remaining.count() % 60;
			sprintf(time, "%d:%02d", minutes, seconds);
			ptrEngine->drawForegroundString(1240, 0, time, 0x00ffff, NULL);
		}
		else {
			//To the losingState since the player has lost
			if (getPoints() <= 5) {
				setVisible(false);
				ptrEngine->lockAndSetupBackground();
				redrawDisplay();
				ptrEngine->setCurrentState(new losingState());
				ptrEngine->setState(5);

			}
			//To the winningState since the player has won
			else
			{
				setVisible(false);
				ptrEngine->lockAndSetupBackground();
				redrawDisplay();
				ptrEngine->setCurrentState(new winningState());
				ptrEngine->setState(4);
			}

		}
	}
	redrawDisplay();

}

void Targets::virtDoUpdate(int iCurrentTime)
{

	// Do not update if it should not be visible or program is paused
	if (!isVisible() || ptrEngine->isPaused())
		return;

	//Make sure to only check for this when the state

	
	std::cout << "X: " << endX << "Y: " << endY << " iDir: " << iDir << "\n";
	if (mp.hasMovementFinished(iCurrentTime))
	{
		if (bounceUp) {

			//left to right
			if (iDir == 0)
			{
				mp.setup(0, endY, endX, endY, iCurrentTime, iCurrentTime + 1400);
			}
			//right to left
			else if (iDir == 1)
			{
				mp.setup(1300, endY, endX, endY, iCurrentTime, iCurrentTime + 1400);
			}
			//Down to Up
			else if (iDir == 2)
			{
				mp.setup(endX, 800, endX, endY, iCurrentTime, iCurrentTime + 1400);
			}
			//Up to Down
			else
			{
				mp.setup(endX, 0, endX, endY, iCurrentTime, iCurrentTime + 1400);
			}
			bounceUp = false;
			bounceDown = true;
		}
		else {
			mp.reverse();
			bounceUp = true;
			bounceDown = false;
			setEndX(rand() % 1300);
			setEndY(rand() % 800);
			setIDir(rand() % 4);
		}
	}

	else {
		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();
	}

	redrawDisplay();
}


#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"
#include "HSObjectL.h"

FoodObject::FoodObject(efylw5Engine* ptrEngine, int iMapX, int iMapY, int X1, int X2, int Y1, int Y2)
	: DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{
	setX1(X1);
	setX2(X2);
	setY1(Y1);
	setY2(Y2);

	collision = false;



	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	setVisible(true);
}

FoodObject::~FoodObject(void)
{
}

void FoodObject::virtDraw()
{

	if (!isVisible())
		return;


	int iSize = 10;

	if (collision) {
		collision = false;
		setVisible(false);
		redrawDisplay();
	}


	ptrEngine->drawForegroundOval(getX1(), getY1(), getX2(), getY2(), 0xFF0000);
	std::cout << "Current Food Position: " << getDrawingRegionLeft() << " " << getDrawingRegionRight() << " " << getDrawingRegionTop() << " " << getDrawingRegionBottom() << "\n";
	redrawDisplay();

}

void FoodObject::virtDoUpdate(int iCurrentTime)
{
	// Do not update if it should not be visible or program is paused
	if (!isVisible() || ptrEngine->isPaused())
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

		if (CollisionDetection::checkCircles(pObject->getXCentre(), pObject->getYCentre(), m_iCurrentScreenX, m_iCurrentScreenY, iSize + iSize))
		{

			//Setting collision true will activate virtDraw() if(collision) statement
			collision = true;
			redrawDisplay();
			return;

		}

		//Calculating the position of the rectangle using movementPosition::calculate()
		//Then setting m_iCurrentScreenX and m_iCurrentScreenY with the current location
		else {

			mp.calculate(iCurrentTime);
			m_iCurrentScreenX = mp.getX();
			m_iCurrentScreenY = mp.getY();

		}
	}
	redrawDisplay();

}

SnakeHead::SnakeHead(efylw5Engine * ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY, FoodObject* Fo)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
{
	fo = Fo;
	m_iDir = 1;
	m_iMapX = iMapX;
	m_iMapY = iMapY;

	bodyCount = 0;

	gameOver = false;
	collision = false;
	point = 0;
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;
	
	
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	
	
	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	animationStartX = startX;
	animationStartY = startY; 
	
	animationEndX = endX;
	animationEndY = endY;
	
	setVisible(true);
}

SnakeHead::~SnakeHead(void)
{

}

void SnakeHead::appendPointsToFile()
{
	std::ofstream os;
	os.open("Points.txt", std::ios::app);
	os << getPoint() << "\n";
	os.close();
}

void SnakeHead::virtKeyDown(int iKeyCode)
{

}

void SnakeHead::printCurrentLocation()
{
	std::cout << "Left: " << getDrawingRegionLeft() << " Bottom: " << getDrawingRegionBottom() << " Top: " << getDrawingRegionTop() << " Right: " << getDrawingRegionRight() << "\n";
}

std::vector<int> SnakeHead::appendNewBody()
{
	int left = getDrawingRegionLeft();
	int top = getDrawingRegionTop();
	int bottom = getDrawingRegionBottom();
	std::vector<int> coords;
	coords.push_back(left);
	coords.push_back(top);
	coords.push_back(bottom);
	return coords;
}



void SnakeHead::virtDraw()
{

	if (!isVisible())
		return;


	int iSize = 10;
	

	if (collision) {

		collision = false;
		char buf[128];
		sprintf(buf, "CONTACT!");
		ptrEngine->drawForegroundString(m_iCurrentScreenX + 100, m_iCurrentScreenY, buf, 0x00ffff, NULL);
		redrawDisplay();
	}

	ptrEngine->drawForegroundOval(m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize, m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1, 0x00FF00);

	if (ptrEngine->getCurrentState()->getState() == 3) {
		static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		static std::chrono::steady_clock::time_point end = start + std::chrono::seconds(300);

		char buf[128];
		sprintf(buf, std::to_string(getPoint()).c_str());
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
			if (getPoint() <= 5) {
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

void SnakeHead::movementSetup(int iDir, int iCurrentTime)
{

	//Up
	if (iDir == 0) {
		mp.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX, m_iCurrentScreenY - 800, iCurrentTime, iCurrentTime + 3400);
	}
	//Right
	else if (iDir == 1) {
		mp.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + 1300, m_iCurrentScreenY, iCurrentTime, iCurrentTime + 5400);
	}
	//Down
	else if (iDir == 2)
	{
		mp.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX, m_iCurrentScreenY + 800, iCurrentTime, iCurrentTime + 3400);
	}
	//Left
	else
	{
		mp.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX - 1300, m_iCurrentScreenY, iCurrentTime, iCurrentTime + 5400);
	}
	
}
void SnakeHead::virtDoUpdate(int iCurrentTime)
{

	// Do not update if it should not be visible or program is paused
	if (!isVisible() || ptrEngine->isPaused())
		return;

	//Make sure to only check for this when the state
	if (ptrEngine->getCurrentState()->getState() == 3) {
		FoodObject* fo = getFoodObject();
		printCurrentLocation();
		if (getDrawingRegionLeft() != 1525 && getDrawingRegionBottom() != 1640 && getDrawingRegionTop() != 1540 && getDrawingRegionRight() != 1625) {
			//Colliding with the border. Game Over
			if (getDrawingRegionLeft() <= -20 || getDrawingRegionBottom() > 875 || getDrawingRegionTop() <= -20 || getDrawingRegionRight() > 1365)
			{
				setGameOver(true);
				setVisible(false);
				ptrEngine->lockAndSetupBackground();
				redrawDisplay();
				ptrEngine->setCurrentState(new losingState());
				ptrEngine->setState(5);
			}
		}
	}

	
	

	if (mp.hasMovementFinished(iCurrentTime))
	{
		//Make sure the movement does not restart if it is not moved
		if (ptrEngine->getCurrentState()->getState() == 3) {
			mp.setup(getAnimationStartX(), getAnimationStartY(), getAnimationStartX() + 1300, getAnimationEndY(), iCurrentTime, iCurrentTime + 5400);
		}
		else {
			mp.setup(getAnimationStartX(), getAnimationStartY(), getAnimationStartX(), getAnimationEndY(), iCurrentTime, iCurrentTime + 5400);
		}
	}

	else {

		mp.calculate(iCurrentTime);
		m_iCurrentScreenX = mp.getX();
		m_iCurrentScreenY = mp.getY();

		//Make sure that the snake object can only be controlled during the runningState
		if (ptrEngine->getCurrentState()->getState() == 3) {

			//Make sure that when the snake is going in one direction, it can't go to the other direction directly.
			if (ptrEngine->isKeyPressed(SDLK_UP) && m_iDir != 2) 
			{
				std::cout << "Up\n";
				m_iDir = 0;
				movementSetup(m_iDir, iCurrentTime);
			}
			if (ptrEngine->isKeyPressed(SDLK_RIGHT) && m_iDir != 3) 
			{
				std::cout << "Right\n";
				m_iDir = 1;
				movementSetup(m_iDir, iCurrentTime);
			}
			if (ptrEngine->isKeyPressed(SDLK_DOWN) && m_iDir != 0)
			{
				std::cout << "Down\n";
				m_iDir = 2;
				movementSetup(m_iDir, iCurrentTime);
			}
			if (ptrEngine->isKeyPressed(SDLK_LEFT) && m_iDir != 1)
			{
				std::cout << "Left\n";
				m_iDir = 3;
				movementSetup(m_iDir, iCurrentTime);
			}
		}

	}

	redrawDisplay();
}

SnakeBody::SnakeBody(efylw5Engine* ptrEngine, SnakeHead* sh, int iMapX, int iMapY, int startX, int startY, int endX, int endY, int bn)
	: DisplayableObject(ptrEngine)
	, ptrEngine(ptrEngine)
{
	setBodyNum(bn);
	snakeHead = sh;
	m_iDir = snakeHead->getIDir();
	m_iMapX = iMapX;
	m_iMapY = iMapY;

	collision = false;

	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;


	m_iDrawWidth = 100;
	m_iDrawHeight = 100;


	m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iCurrentScreenY = iMapY * 50 + 25 + 40;


	setVisible(true);
}

SnakeBody::~SnakeBody(void)
{
}

void SnakeBody::virtDraw()
{
	if (!isVisible())
		return;

	if (snakeHead->getGameOver()) {
		setVisible(false);
	}
	else {
		std::vector<int> coords = snakeHead->appendNewBody();
		if (snakeHead->getBodyCount() != 0)
		{
			std::cout << snakeHead->getBodyCount() << "\n";

		}
		setSnakeBodyMovement(coords[0],coords[1],coords[0],coords[2]);
		std::cout << "Snake Body Num: 1 Left: " << coords[0] << " Top: " << coords[1] << " Right: " << coords[0] << " Bottom: " << coords[2] << "\n";
		//The first body part
		if (snakeHead->getBodyCount() == 0) {
			snakeHead->setBodyCount(snakeHead->getBodyCount() + 1);
		}
		else 
		{
			//Get snakebody vector
			std::vector<SnakeBody*> sc = snakeHead->getSnakeBodyCoords();
			//Iterate through the vector
			for (int i = 1; i < sc.size(); ++i) {
				std::vector<int> t = getCurrentLocation();
				setSnakeBodyMovement(t[0], t[1], t[0], t[2]);
				//std::cout << "Snake Body Num: " << i + 1<< "Left: " << tmp->getDrawingRegionLeft() << " Top: " << tmp->getDrawingRegionTop() << " Left: " << tmp->getDrawingRegionRight() << " Bottom: " << tmp->getDrawingRegionBottom() << "\n";
			}
		}
	}
	redrawDisplay();
}

void SnakeBody::virtDoUpdate(int iCurrentTime)
{

}

/**
	Class: SnakeBody
	Function: setcurrentLocation()
	Param: int left, int right, int top, int bottom
	Description: setters for currentLeft, currentRight, currentTop, and currentBottom member variables
*/
void SnakeBody::setcurrentLocation(int left, int right, int top, int bottom)
{
	currentLeft = left;
	currentRight = right;
	currentTop = top;
	currentBottom = bottom;
}

void SnakeBody::printCurrentLocation()
{

}

/**
	Class: SnakeBody
	Function: setSnakeBodyMovement()
	Param: int left, int right, int top, int bottom
	Description: Allows the snakebody to move according to the snakeHead iDir variable.
				 Then it will draw the snakeBody object accordingly and setting the 
				 currentLocation with the arguments being passed in.
*/
void SnakeBody::setSnakeBodyMovement(int left, int top, int right, int bottom)
{
	//Up
	if (snakeHead->getIDir() == 0) {
		ptrEngine->drawForegroundOval(left + 15, top + 33, right + 34, bottom - 48, 0xFF0000);
		setcurrentLocation(left, top, right, bottom);
	}
	//Right
	else if (snakeHead->getIDir() == 1) {
		ptrEngine->drawForegroundOval(left + 1, top + 15, right + 20, bottom - 66, 0xFF0000);
		setcurrentLocation(left, top, right, bottom);
	}
	//Down
	else if (snakeHead->getIDir() == 2) {
		ptrEngine->drawForegroundOval(left + 15, top - 2, right + 34, bottom - 83, 0xFF0000);
		setcurrentLocation(left, top, right, bottom);
	}
	//Left
	else if (snakeHead->getIDir() == 3) {
		ptrEngine->drawForegroundOval(left + 30, top + 15, right + 49, bottom - 66, 0xFF0000);
		setcurrentLocation(left, top, right, bottom);
	}
}

/**
	Class: SnakeBody
	Function: getCurrentLocation()
	Description: Getter function for currentLeft, currentTop, currentRight, and currentBottom
				 member variables. They will be stored in the vector of int and returned.
	Return: std::vector<int> location
*/
std::vector<int> SnakeBody::getCurrentLocation()
{
	std::vector<int> location;
	location.push_back(currentLeft);
	location.push_back(currentTop);
	location.push_back(currentRight);
	location.push_back(currentBottom);
	return location;
}


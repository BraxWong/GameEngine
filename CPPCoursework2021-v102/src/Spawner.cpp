#include "Spawner.h"

Spawner::Spawner(efylw5Engine* ptrEngine, Timer* timer, int color10, int color20, int color100 , int difficulty, int shape)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine), 
	timer(timer)
{
	setColor10(color10);
	setColor20(color20);
	setColor100(color100);
	setDifficulty(difficulty);
	setShape(shape);
}

Spawner::~Spawner(void)
{
}


/**
	Class: Spawner
	Function: virtDraw()
	Description: This will draw the current score to the screen 
*/
void Spawner::virtDraw()
{
	if (ptrEngine->getCurrentState()->getState() != 3)
		return;
	char buf[128];
	sprintf(buf, std::to_string(ptrEngine->getPoint()).c_str());
	ptrEngine->drawForegroundString(210, 0, buf, 0x00ffff, NULL);
}

/**
	Class: Spawner
	Function: virtDoUpdate()
	Param: int iCurrentTime
	Description: This will append the targets object to the array.
				 It will check whether chanceOfSpawning() is returning true,
				 if so, append the object to the array and said object will be
				 drawn to the screen.
*/
void Spawner::virtDoUpdate(int iCurrentTime)
{
	if (ptrEngine->isPaused())
		return;

	if (chanceOfSpawning(0))
	{
		ptrEngine->appendObjectToArray(new RedTargets(ptrEngine, timer, 30, 30,getColor10(), getDifficulty(), getShape()));
		ptrEngine->appendObjectToArray(new BlackTargets(ptrEngine, timer, 30, 30,getDifficulty(), getShape()));
	}
	if (chanceOfSpawning(1))
	{
		ptrEngine->appendObjectToArray(new BlueTargets(ptrEngine, timer, 30, 30,getColor20(), getDifficulty(), getShape()));
	}
	if (chanceOfSpawning(2))
	{
		ptrEngine->appendObjectToArray(new GoldTargets(ptrEngine, timer, 30, 30,getColor100(), getDifficulty(), getShape()));
	}
}

/**
	Class: Spawner
	Function: chanceOfSpawning()
	Param: int color (The color of the target)
	Description: This function will be called from virtDoUpdate() which
				 determines whether an object should be added to the array.
				 Since this function will be called once per frame, the variable 
				 num has to be big to prevent objects cluttering the screen.
*/
template <class T>
bool Spawner::chanceOfSpawning(T color)
{
	int num = 0;
	//RED or BLACK
	if (color == 0 || color == 3) {
		num = 500;
	}
	//BLUE
	else if (color == 1) {
		num = 600;
	}
	//GOLD
	else if (color == 2)
	{
		num = 700;
	}

	if (rand() % num < 5)
		return true;
	return false;

}

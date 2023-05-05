#include "Timer.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

Timer::Timer(efylw5Engine* ptrEngine, int second)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{
	ptrEngine->setPoint(0);
	ptrEngine->clearHiddenMessage();
	start = std::chrono::steady_clock::now();
	appended = false;
	setSecond(second);
	timesUp = false;
	setVisible(true);
}

Timer::~Timer(void)
{

}
/**
	Class: Timer
	Function: appendPointsToFile()
	Description: This function will be called from virtDraw when the countdown has
				 gone down to 0. It will write the current score to Points.txt file.
*/
void Timer::appendPointsToFile()
{
	appended = true;
	std::ofstream os;
	os.open("Points.txt", std::ios::app);
	os << ptrEngine->getPoint() << "\n";
	os.close();
}

/**
	Class: Timer
	Function: virtDraw()
	Description: This will draw the countdown timer as a string on screen.
				 When the time is up, it will first write the current score 
				 to Points.txt file. Then setting timesUp to true. Then it will
				 check for win condition and do the transition accordingly.
*/
void Timer::virtDraw()
{
	if (ptrEngine->isPaused())
		return;

	std::chrono::steady_clock::time_point end = start + std::chrono::seconds(getSecond());
	if (std::chrono::steady_clock::now() < end) {
		char time[128];
		auto remaining = std::chrono::duration_cast<std::chrono::seconds>(end - std::chrono::steady_clock::now());
		int minutes = remaining.count() / 60;
		int seconds = remaining.count() % 60;
		sprintf(time, "%d:%02d", minutes, seconds);
		ptrEngine->drawForegroundString(1240, 0, time, 0x00ffff, NULL);

	}
	else {
		if(!timesUp)
			appendPointsToFile();
		timesUp = true;
		if (ptrEngine->getPoint() <= 500) {
			setVisible(false);
			ptrEngine->setHiddenMessage("");
			ptrEngine->setCurrentState(new losingState());
			ptrEngine->setState(5);
			ptrEngine->lockAndSetupBackground();
			redrawDisplay();
		}
		//To the winningState since the player has won
		else
		{
			setVisible(false);
			ptrEngine->appendObjectToArray(new MovingButton(ptrEngine, 30, 30));
			ptrEngine->lockAndSetupBackground();
			ptrEngine->setCurrentState(new winningState(ptrEngine));
			ptrEngine->setState(4);
			ptrEngine->lockAndSetupBackground();
			redrawDisplay();
		}
	}
}

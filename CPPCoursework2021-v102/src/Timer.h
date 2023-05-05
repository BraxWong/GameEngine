#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
#include <chrono>
#include <fstream>
class efylw5Engine;

class Timer:
	public DisplayableObject
{
public:
	Timer(efylw5Engine* ptrEngine, int second);
	~Timer(void);
	inline void setTimesUp(bool time) { timesUp = time; }
	inline void setSecond(int s) { second = s; }
	inline bool getTimesUp() { return timesUp; }
	void appendPointsToFile();
	void virtDraw() override;
	inline int getSecond() { return second; }
	inline bool getAppended() { return appended; }
private:
	
	bool timesUp, appended;
	efylw5Engine* ptrEngine;
	int second;
	std::chrono::steady_clock::time_point start;

};


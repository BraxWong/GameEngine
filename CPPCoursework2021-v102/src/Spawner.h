#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "efylw5Engine.h"
#include "BlackTargets.h"
#include "RedTargets.h"
#include "BlueTargets.h"
#include "GoldTargets.h"
#include "Timer.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


class Spawner:
	public DisplayableObject
{
public:
	Spawner(efylw5Engine* ptrEngine, Timer* timer, int color10, int color20, int color100, int difficulty, int shape);
	~Spawner(void);
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	template<class T>
	bool chanceOfSpawning(T color);
	inline void setColor10(int c10) { color10 = c10; }
	inline void setColor20(int c20) { color20 = c20; }
	inline void setColor100(int c100) { color100 = c100; }
	inline void setDifficulty(int d) { difficulty = d; }
	inline void setShape(int s) { shape = s; }

 	inline int getColor10() { return color10; }
	inline int getColor20() { return color20; }
	inline int getColor100() { return color100; }
	inline int getDifficulty() { return difficulty; }
	inline int getShape() { return shape; }
private:
	efylw5Engine* ptrEngine;
	Timer* timer;
	int difficulty, color10, color20, color100, shape;
};


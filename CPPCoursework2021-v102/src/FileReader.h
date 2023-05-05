#pragma once
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>
class FileReader
{
public:
	inline void setCrosshairColor(std::string crossColor) { crosshairColor = crossColor; }
	inline void setCrosshairSize(std::string size) { crosshairSize = size; }
	inline void setTargetShapes(std::string shape) { targetShapes = shape; }
	inline void setColor10(std::string color) { color10 = color; }
	inline void setColor20(std::string color) { color20 = color; }
	inline void setColor100(std::string color) { color100 = color; }
	inline void setDifficulty(std::string d) { difficulty = d; }
	inline void setTimeLimit(std::string time) { timeLimit = time; }

	void parseUserConfig();

	unsigned int getCrosshairColor();
	inline int getCrosshairSize() { int size = stoi(crosshairSize); if (size < 5 || size > 15) { return 10; }  return size; }
	inline int getTargetShapes() { int shape = stoi(targetShapes); if (shape != 1 && shape != 2) { return 1; } return shape;}
	inline int getColor10() { return stoi(color10); }
	inline int getColor20() { return stoi(color20); }
	inline int getColor100() { return stoi(color100); }
	inline int getDifficulty() {int d = stoi(difficulty); if (d != 1 && d != 2 && d != 3) { return 1; } return d;}
	inline int getTimeLimit() {int s = stoi(timeLimit); if (s < 5 || s > 500) { return 300; } return s;}

private:
	std::string crosshairColor, crosshairSize, targetShapes, color10, color20, color100, difficulty, timeLimit;
};


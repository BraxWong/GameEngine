#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 

class efylw5Engine;

class Targets :
    public DisplayableObject
{
public:
    Targets(efylw5Engine* ptrEngine, int iMapX, int iMapY);
    ~Targets(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void setPoints(int point) { points = point; }
    void setEndX(int x) { endX = x; }
    void setEndY(int y) { endY = y; }
    void setIDir(int dir) { iDir = dir; }

    void virtKeyDown(int iKeyCode);
    void printCurrentLocation();
    int getPoints() { return points; }
    int getEndX() { return endX; }
    int getEndY() { return endY; }
  

    int count = 0;
private:
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    int points, endX, endY, iDir;
    bool bounceUp, bounceDown;
};

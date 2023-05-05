#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
#include "Timer.h"
class efylw5Engine;

class BlackTargets :
    public DisplayableObject
{
public:
    BlackTargets(efylw5Engine* ptrEngine, Timer* timer, int iMapX, int iMapY, int difficulty, int shape);
    ~BlackTargets(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void setMovementSettings();
    inline void setHit(bool t) { hit = t; }
    inline void setDifficulty(int d) { difficulty = d; }
    inline void setShape(int s) { shape = s; }
    void virtKeyDown(int iKeyCode);
    void setMovement(int iCurrentTime);
    void setSpeed();

    void printCurrentLocation();
    inline bool setHit() { return hit; }
    inline int getDifficulty() { return difficulty; }
    inline int getShape() { return shape; }
    inline int getSpeed() { return speed; }
    int count = 0;
private:
    std::vector<int> movementSettings;
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool bounceUp, bounceDown, pointLock, hit;
    Timer* timer;
    int difficulty, shape, speed;
};


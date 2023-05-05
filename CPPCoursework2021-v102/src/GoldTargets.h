#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
#include "Timer.h"
class efylw5Engine;

class GoldTargets :
    public DisplayableObject
{
public:
    GoldTargets(efylw5Engine* ptrEngine, Timer* timer, int iMapX, int iMapY, int color, int difficulty, int shape);
    ~GoldTargets(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void setMovementSettings();
    inline void setHit(bool t) { hit = t; }
    void setColor(int c);
    inline void setDifficulty(int d) { difficulty = d; }
    inline void setShape(int s) { shape = s; }
    void setSpeed();

    void virtKeyDown(int iKeyCode);
    void setMovement(int iCurrentTime);
    void printCurrentLocation();
    inline bool setHit() { return hit; }
    inline unsigned int getColor() { return color; }
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
    unsigned int color;
};


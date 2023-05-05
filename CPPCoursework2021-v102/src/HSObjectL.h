#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 

class efylw5Engine;

class HSObjectL :
    public DisplayableObject
{
public:

    HSObjectL(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY);
    ~HSObjectL(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    inline void setAnimationStartX(int x) { animationStartX = x; }
    inline void setAnimationStartY(int y) { animationStartY = y; }
    inline void setAnimationEndX(int x) { animationEndX = x; }
    inline void setAnimationEndY(int y) { animationEndY = y; }

    inline int getAnimationStartX() { return animationStartX; }
    inline int getAnimationStartY() { return animationStartY; }
    inline int getAnimationEndX() { return animationEndX; }
    inline int getAnimationEndY() { return animationEndY; }

    void drawEffect();
private:

    int animationStartX, animationStartY, animationEndX, animationEndY;
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool vis;

};


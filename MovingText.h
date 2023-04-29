#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
#include <cstdlib>

class efylw5Engine;

class MovingText :
    public DisplayableObject
{
public:

    MovingText(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY);
    ~MovingText(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    void setAnimationStartX(int x) { animationStartX = x; }
    void setAnimationStartY(int y) { animationStartY = y; }
    void setAnimationEndX(int x) { animationEndX = x; }
    void setAnimationEndY(int y) { animationEndY = y; }

    int getAnimationStartX() { return animationStartX; }
    int getAnimationStartY() { return animationStartY; }
    int getAnimationEndX() { return animationEndX; }
    int getAnimationEndY() { return animationEndY; }
    std::vector<std::string> getText() { return strVec; }

private:

    int animationStartX, animationStartY, animationEndX, animationEndY;
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool vis;
    std::vector<std::string> strVec;
    std::vector<unsigned int> colorVec = { 0xcb3d48,0xe9d9c0,0xa4aac6,0xa49ebc,0xa68ec1,0xad95b9,0xa6a1cc,0xebaf00,0x01e2f6,0x86ffcb };

};



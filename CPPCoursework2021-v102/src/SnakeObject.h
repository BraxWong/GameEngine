#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
class efylw5Engine;

class SnakeObject :
    public DisplayableObject
{
public:
    SnakeObject(efylw5Engine* ptrEngine, int iMapX, int iMapY);
    ~SnakeObject(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    BaseEngine* be = new BaseEngine();
private:
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool collision;
};


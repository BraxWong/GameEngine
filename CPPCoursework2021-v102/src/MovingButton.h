#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "FontManager.h"
class efylw5Engine;

class MovingButton :
    public DisplayableObject
{
public:
    MovingButton(efylw5Engine* ptrEngine, int iMapX, int iMapY);
    ~MovingButton(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    int count = 0;
private:
    int xDecrement, yDecrement, fontSize, xDecrementWord, yDecrementWord;
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool moved;
};


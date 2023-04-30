#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "DrawingSurface.h" 
#include <cstdlib>

class efylw5Engine;

class HitMarker :
    public DisplayableObject
{
public:

    HitMarker(efylw5Engine* ptrEngine, int x, int y);
    ~HitMarker(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

   
    void setClickX(int x) { clickX = x; }
    void setClickY(int y) { clickY = y; }

   
    int getClickX() { return clickX; }
    int getClickY() { return clickY; }


private:

    int clickX, clickY;
    efylw5Engine* ptrEngine;
    bool vis;
    std::vector<unsigned int> colorVec = { 0xcb3d48,0xe9d9c0,0xa4aac6,0xa49ebc,0xa68ec1,0xad95b9,0xa6a1cc,0xebaf00,0x01e2f6,0x86ffcb };
};



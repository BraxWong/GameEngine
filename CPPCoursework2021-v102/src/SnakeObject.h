#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "DrawingSurface.h" 
#include <chrono>
#include <iostream>

class efylw5Engine;
class SnakeHead;

class SnakeBody :
    public DisplayableObject
{
public:
    SnakeBody(efylw5Engine* ptrEngine, SnakeHead* sh, int iMapX, int iMapY, int startX, int startY, int endX, int endY, int bn);
    ~SnakeBody(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    void setcurrentLocation(int left, int right, int top, int bottom);
    void setBodyNum(int bn) { bodyNum = bn; }
    void printCurrentLocation();
    void setSnakeBodyMovement(int left, int top, int right, int bottom);
    std::vector<int> getCurrentLocation();
    int getBodyNum() { return bodyNum; }

    int count = 0;
    bool vectorLock = false;

private:

    efylw5Engine* ptrEngine;
    MovementPosition mp;
    SnakeHead* snakeHead;
    bool collision;
    int currentLeft, currentRight, currentTop, currentBottom, m_iMapX, m_iMapY, m_iDir;
    int bodyNum;
};

class FoodObject :
    public DisplayableObject
{
public:
    FoodObject(efylw5Engine* ptrEngine, int iMapX, int iMapY, int X1, int X2, int Y1, int Y2);
    ~FoodObject(void);
    void setCollision(bool var) { collision = var; }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    bool getCollision() { return collision; }

    BaseEngine* be = new BaseEngine();
    int count = 0;
    void setX1(int x) { X1 = x; }
    void setX2(int x) { X2 = x; }
    void setY1(int y) { Y1 = y; }
    void setY2(int y) { Y2 = y; }

    int getX1() { return X1; }
    int getX2() { return X2; }
    int getY1() { return Y1; }
    int getY2() { return Y2; }

private:
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool collision;
    int X1, X2, Y1, Y2;
};

class SnakeHead :
    public DisplayableObject
{
public:
    SnakeHead(efylw5Engine* ptrEngine, int iMapX, int iMapY, int startX, int startY, int endX, int endY, FoodObject* Fo);
    ~SnakeHead(void);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    void setAnimationStartX(int x) { animationStartX = x; }
    void setAnimationStartY(int y) { animationStartY = y; }
    void setAnimationEndX(int x) { animationEndX = x; }
    void setAnimationEndY(int y) { animationEndY = y; }
    void setPoint(int pt) { point = pt; }
    void setGameOver(bool var) { gameOver = var; }
    void appendPointsToFile();
    void virtKeyDown(int iKeyCode);
    void printCurrentLocation();
    void setSnakeBodyCoords(std::vector<SnakeBody*> sc) { snakeBodyCoords = sc; }
    void setBodyCount(int bc) { bodyCount = bc; }
    void setFoodObject(FoodObject* FO) { fo = FO; }
    std::vector<int> appendNewBody();

    int getAnimationStartX() { return animationStartX; }
    int getAnimationStartY() { return animationStartY; }
    int getAnimationEndX() { return animationEndX; }
    int getAnimationEndY() { return animationEndY; }
    int getPoint() { return point; }
    int getIDir() { return m_iDir; }
    int getBodyCount() { return bodyCount; }
    bool getGameOver() { return gameOver; }
    FoodObject* getFoodObject() { return fo; }
    std::vector<SnakeBody*> getSnakeBodyCoords() { return snakeBodyCoords; }
  
    int count = 0;
    
  

    void movementSetup(int iDir, int iCurrentTime);
private:
    bool gameOver;
    efylw5Engine* ptrEngine;
    MovementPosition mp;
    bool collision;
    int animationStartX, animationStartY, animationEndX, animationEndY, point, m_iMapX, m_iMapY,m_iDir, bodyCount;
    std::vector<SnakeBody*> snakeBodyCoords;
    FoodObject* fo;
};







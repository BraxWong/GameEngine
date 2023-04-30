#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "States.h"
#include "SnakeObject.h"
#include "HSObjectL.h"
#include "HSObjectR.h"
#include "MovingText.h"
#include "Targets.h"
#include <fstream>

#define STARTUP 1;
#define PAUSE 2;
#define RUNNING 3;
#define WIN 4;
#define LOSE 5;

class efylw5Engine :
    public BaseEngine
{
public:

    //When the engine starts, it will be at the STARTUP state
    efylw5Engine()
    {
            point = 0;
            mouseLifted = NULL;
            state = STARTUP;
            returnToTutorial = true;
            returnToGame = true;
            clickX = 0;
            clickY = 0;
            so = NULL;

    }

    ~efylw5Engine()
    {

        free(currentState);

    }
    int getPoint() { return point; }

    int getClickX() { return clickX; }

    int getClickY() { return clickY; }

    int getState() { return state; }

    void setState(int num) { state = num; }

    void setReturnToTutorial(bool var) { returnToTutorial = var; }

    void setReturnToGame(bool var) { returnToGame = var; }

    void setName(std::string n) { name += n; }

    void setPoint(int pt) { point = pt; }

    void deleteName();

    void virtSetupBackgroundBuffer();

    void setClickX(int x) { clickX = x; }

    void setClickY(int y) { clickY = y; }

    //void setSnakeHead(SnakeHead* sh) { so = sh; }

    States* getCurrentState() { return currentState; }

    void setCurrentState(States* state) { currentState = state; }

    void virtKeyDown(int iKeyCode);

    void virtMouseDown(int iButton, int iX, int iY);

    void virtMouseUp(int iButton, int iX, int iY);

    void addPlayerName();

    States* currentState = new startingState(this);

    void virtDrawStringsUnderneath();

    void virtDrawStringsOnTop();

    void drawTable();

    //read a file that contains all the score. Use a sorting helper function,
    //then pull out the top 5 scores
    void populateTable();

    int virtInitialiseObjects();

    bool getReturnToTutorial() { return returnToTutorial; }

    bool getReturnToGame() { return returnToGame; }

    bool getMouseLifted() { return mouseLifted; }

    SnakeHead* getSnakeObject() { return so; }

    std::string getName() { return name; }

private:
    int clickX, clickY;
    int state, point;
    bool returnToTutorial, returnToGame, mouseLifted;
    SnakeHead* so;
    std::string name;
};



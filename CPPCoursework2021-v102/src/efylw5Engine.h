#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "States.h"
#include "SnakeObject.h"

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
        state = STARTUP;
    }

    ~efylw5Engine()
    {

        free(currentState);

    }

    int getState() { return state; }

    void setState(int num) { state = num; }

    void virtSetupBackgroundBuffer();

    States* getCurrentState() { return currentState; }

    void setCurrentState(States* state) { currentState = state; }

    void virtKeyDown(int iKeyCode);

    States* currentState = new startingState();

    void virtDrawStringsUnderneath();

    void virtDrawStringsOnTop();

    int virtInitialiseObjects();

private:
    int state;
};


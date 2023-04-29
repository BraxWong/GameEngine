#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "States.h"
#include "SnakeObject.h"
#include "HSObjectL.h"
#include "HSObjectR.h"
#include "MovingText.h"
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
        state = STARTUP;
        returnToTutorial = true;
        returnToGame = true;

    }

    ~efylw5Engine()
    {

        free(currentState);

    }

    int getState() { return state; }

    void setState(int num) { state = num; }

    void setReturnToTutorial(bool var) { returnToTutorial = var; }

    void setReturnToGame(bool var) { returnToGame = var; }

    void setName(std::string n) { name += n; }

    void deleteName();

    void virtSetupBackgroundBuffer();

    void setSnakeHead(SnakeHead* sh) { so = sh; }

    States* getCurrentState() { return currentState; }

    void setCurrentState(States* state) { currentState = state; }

    void virtKeyDown(int iKeyCode);

    void addPlayerName();

    States* currentState = new highscoreState(this);

    void virtDrawStringsUnderneath();

    void virtDrawStringsOnTop();

    void drawTable();

    void setUpForegroundEffectHS();

    //read a file that contains all the score. Use a sorting helper function,
    //then pull out the top 5 scores
    void populateTable();

    int virtInitialiseObjects();

    bool getReturnToTutorial() { return returnToTutorial; }

    bool getReturnToGame() { return returnToGame; }

    SnakeHead* getSnakeObject() { return so; }

    std::string getName() { return name; }

private:
    int state;
    bool returnToTutorial, returnToGame;
    SnakeHead* so;
    std::string name;
};


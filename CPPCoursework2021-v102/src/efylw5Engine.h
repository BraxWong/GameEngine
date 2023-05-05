#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "States.h"
#include "SnakeObject.h"
#include "HSObjectL.h"
#include "HSObjectR.h"
#include "MovingText.h"
#include "Spawner.h"
#include "Timer.h"
#include "FileReader.h"
#include "ExampleFilterPointClasses.h"
#include "FontManager.h"
#include "MovingButton.h"
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
        : zooming(0, 0, this), 
      scrolling(0, 0, &zooming)
    {
        setOffset(0);
        fr.parseUserConfig();
        setPoint(0);
        mouseLifted = true;
        state = STARTUP;
        returnToTutorial = true;
        returnToGame = true;
        clickX = 0;
        clickY = 0;
        so = NULL;
        setState(4);
    }

    ~efylw5Engine()
    {

        free(currentState);

    }
    inline int getPoint() { return point; }

    inline int getClickX() { return clickX; }

    inline int getClickY() { return clickY; }

    inline int getState() { return state; }

    inline void setState(int num) { state = num; }

    inline void setReturnToTutorial(bool var) { returnToTutorial = var; }

    inline void setReturnToGame(bool var) { returnToGame = var; }

    inline void setName(std::string n) { name += n; }

    inline void setHiddenMessage(std::string m) { hiddenMessage += m; }

    inline void setPoint(int pt) { point = pt; }

    void deleteName();

    void deleteHiddenMessage();

    void virtSetupBackgroundBuffer();

    inline void setClickX(int x) { clickX = x; }

    inline void setClickY(int y) { clickY = y; }

    inline States* getCurrentState() { return currentState; }

    inline void setCurrentState(States* state) { currentState = state; }

    inline void setOffset(int o) { m_iOffset = o; }

    void virtKeyDown(int iKeyCode);

    void virtMouseDown(int iButton, int iX, int iY);

    void virtMouseUp(int iButton, int iX, int iY);

    void addPlayerName();

    States* currentState = new startingState(this);

    void virtDrawStringsUnderneath();

    void virtDrawStringsOnTop();

    void virtCleanUp();

    void copyAllBackgroundBuffer() override;

    void virtMainLoopDoBeforeUpdate() override;

    virtual void virtMouseWheel(int x, int y, int which, int timestamp) override;

    void drawTable();

    void populateTable();

    void drawCredit();

    int virtInitialiseObjects();

    inline int getOffset() { return m_iOffset; }

    inline bool getReturnToTutorial() { return returnToTutorial; }

    inline bool getReturnToGame() { return returnToGame; }

    inline bool getMouseLifted() { return mouseLifted; }

    inline SnakeHead* getSnakeObject() { return so; }

    inline std::string getName() { return name; }

    inline std::string getHiddenMessage() { return hiddenMessage; }

    int virtInitialise() override;

    inline void clearHiddenMessage() { hiddenMessage.clear(); }

private:
    int clickX, clickY, m_iOffset;
    int state, point;
    bool returnToTutorial, returnToGame, mouseLifted;
    SnakeHead* so;
    std::string name, hiddenMessage;
    FileReader fr;
    Timer* timer;
    FilterPointsScaling zooming;
    FilterPointsTranslation scrolling;
};



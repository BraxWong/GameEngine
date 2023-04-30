#pragma once
#include "header.h"
#include "SnakeObject.h"
#include <vector>
#include <unordered_map>

class States
{
public:

    void setCoordX(std::vector<int> num) { coordX = num; }

    void setCoordY(std::vector<int> num) { coordY = num; }

    void setStr(std::vector<char*> s) { str = s; }

    void setImageURL(std::string URL) { imageURL = URL; }
;
    void setState(int s) { state = s; }

    virtual void setBackground();

    void setEngine(efylw5Engine* e) { ptrEngine = e; }

    std::vector<int> getCoordX() { return coordX; }

    std::vector<int> getCoordY() { return coordY; }

    std::vector<char*> getStr() { return str; }

    std::string getImageURL() { return imageURL; }

    virtual std::vector<std::pair<std::string, int>>  getScores();

    virtual std::vector<std::pair<std::string,int>> sortScores(std::vector<std::pair<std::string, int>> map);

    efylw5Engine* getEngine() { return ptrEngine; }

    int getState() { return state; }
    
    template <class T>
    void freeVector(std::vector<T> &v) 
    {
        v.clear();
        v.shrink_to_fit();
    }

    template <>
    void freeVector(std::vector<char*>& v)
    {
        for (auto ptr : v)
        {
            delete[] ptr;
        }
        v.clear();
        v.shrink_to_fit();
    }

private:
    std::vector<int> coordX;
    std::vector<int> coordY;
    std::vector<char*> str;
    std::string imageURL;
    int state = 0;
    efylw5Engine* ptrEngine = NULL;
};

class startingState : public States
{
public:
    startingState(efylw5Engine* e)
    {
        setEngine(e);
        std::vector<int> x = { 475, 510 };
        std::vector<int> y = {250, 450};
        std::vector<char*> s = {"Welcome to Sharp Shooter!", "Press Enter to Start!"};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Image1.jpg");
        setState(1);
    }

    ~startingState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }

    void setBackground() override;
private:
    int state = 1;

};

class tutorialState : public States
{
public:
    tutorialState()
    {
        std::vector<int> x = { 375, 125, 345, 30, 270, 330, 430 };
        std::vector<int> y = { 100, 750, 225, 150, 400,500, 600 };
        std::vector<char*> s = { "Here is the tutorial before you start.", "If you want to leave the game. Press the ESC button on your keyboard.", "You will have 5 minutes to play the game." 
            ,"If you can reach a certain amount of points.You will win!If not, you will lose.ENJOY!","Click on the target that shows up on the screen.", "Red(+10), Blue(+20),Gold (+100),Black(-20)", "Press the spacebar to begin."};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Rules.jpg");
        setState(2);
    }
    ~tutorialState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }
    void setBackground() override;
    
private:
    int state = 2;
};
class pausingState : public States
{
public:

};

class runningState : public States
{
public:
    runningState(efylw5Engine* ptrEngine):
        ptrEngine(ptrEngine)
    {
        std::vector<int> x = { 0, 1140 };
        std::vector<int> y = { 0, 0};
        std::vector<char*> s = { "Player Score: ", "Timer:" };
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("gameBackground.jpg");
        setState(3);

    }

    ~runningState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }
    void setBackground() override;


private:
    efylw5Engine* ptrEngine;
    int state = 3;
};

class winningState : public States
{
public:

    winningState()
    {
        std::vector<int> x = { 0, 1165 };
        std::vector<int> y = { 0, 0 };
        std::vector<char*> s = { "Your Score is:  ", "Timer:" };
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Rules.jpg");
        setState(4);
    }

    ~winningState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }
    void setBackground() override;
private:
    int state = 4;
};

class losingState : public States
{
public:
    losingState()
    {
        std::vector<int> x = { 0, 1165 };
        std::vector<int> y = { 0, 0 };
        std::vector<char*> s = { "Your Score is: ", "Timer:" };
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Rules.jpg");
        setState(5);
    }

    ~losingState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }
    void setBackground() override;
private:
    int state = 5;
};

class highscoreState : public States
{
public:


    //Obtain the records from populateTable(), then sort the records,
    //then return the top 5 scores
    std::vector<std::pair<std::string, int>> getScores() override;

    std::vector<std::pair<std::string, int>> sortScores(std::vector<std::pair<std::string, int>> map) override;

    highscoreState(efylw5Engine* ptrEngine) :
        e(ptrEngine)
    {
        std::vector<int> x = { 553, 470, 790, 400 };
        std::vector<int> y = { 100, 200, 200, 700 };
        std::vector<char*> s = {"HighScore Table", "Player", "Score", "Press R to go back to the main menu"};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setState(6);
    }
   
    ~highscoreState() {

    }


private:
    efylw5Engine* e;
    int state = 6;
};


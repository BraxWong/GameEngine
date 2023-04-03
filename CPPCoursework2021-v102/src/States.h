#pragma once
#include "header.h"
#include <vector>
class States
{
public:

    void setCoordX(std::vector<int> num) { coordX = num; }

    void setCoordY(std::vector<int> num) { coordY = num; }

    void setStr(std::vector<char*> s) { str = s; }

    std::vector<int> getCoordX() { return coordX; }

    std::vector<int> getCoordY() { return coordY; }

    std::vector<char*> getStr() { return str; }

private:
    std::vector<int> coordX;
    std::vector<int> coordY;
    std::vector<char*> str;
};

class startingState : public States
{
public:
    startingState() 
    {

        std::vector<int> x = { 850, 250 };
        std::vector<int> y = {750, 250};
        std::vector<char*> s = {"Welcome to Snake Game!", "IDK"};
        setCoordX(x);
        setCoordY(y);
        setStr(s);

    }
    
};

class pausingState : public States
{
public:

};

class runningState : public States
{
public:

};

class winningState : public States
{
public:

};

class losingState : public States
{
public:

};


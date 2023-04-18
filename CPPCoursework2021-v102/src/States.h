#pragma once
#include "header.h"
#include <vector>
class States
{
public:

    void setCoordX(std::vector<int> num) { coordX = num; }

    void setCoordY(std::vector<int> num) { coordY = num; }

    void setStr(std::vector<char*> s) { str = s; }

    void setImageURL(std::string URL) { imageURL = URL; }

    void setChangeImage(bool var) { changeImage = var; }

    std::vector<int> getCoordX() { return coordX; }

    std::vector<int> getCoordY() { return coordY; }

    std::vector<char*> getStr() { return str; }

    std::string getImageURL() { return imageURL; }

    bool getChangeImage() { return changeImage; }
    
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
    bool changeImage;
};

class startingState : public States
{
public:
    startingState() 
    {

        std::vector<int> x = { 475, 485 };
        std::vector<int> y = {250, 450};
        std::vector<char*> s = {"Welcome to Snake Game!", "Press Enter to Start!"};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Image1.jpg");
        setChangeImage(false);

    }

    ~startingState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }
    
};

class tutorialState : public States
{
public:
    tutorialState()
    {
        std::vector<int> x = { 375, 125, 345, 30, 430 };
        std::vector<int> y = { 100, 750, 325, 150, 600 };
        std::vector<char*> s = { "Here is the tutorial before you start.", "If you want to leave the game. Press the ESC button on your keyboard.", "You will have 5 minutes to play the game." 
            ,"If you can reach a certain amount of points.You will win!If not, you will lose.ENJOY!", "Press the spacebar to begin."};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setImageURL("Rules.jpg");
        setChangeImage(false);
    }
    ~tutorialState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }

    
private:
};
class pausingState : public States
{
public:

};

class runningState : public States
{
public:
    runningState()
    {
        std::vector<int> x = { 475 };
        std::vector<int> y = { 250 };
        std::vector<char*> s = { "Player Score: ", "Timer: "};
        setCoordX(x);
        setCoordY(y);
        setStr(s);
        setChangeImage(false);
    }

    ~runningState()
    {
        freeVector(getCoordX());
        freeVector(getCoordY());
        freeVector(getStr());
    }

};

class winningState : public States
{
public:

};

class losingState : public States
{
public:

};


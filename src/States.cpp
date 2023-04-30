#include "header.h"
#include "States.h"
#include "SimpleImage.h"
#include "efylw5Engine.h"
#include "BaseEngine.h"


std::vector<std::pair<std::string, int>> highscoreState::getScores()
{
    std::vector<std::pair<std::string, int>> map;
    std::ifstream s1("Points.txt"), s2("Player.txt");
    std::string line1, line2;
    while (std::getline(s1, line1) && std::getline(s2,line2)) {
        map.emplace_back(line2, std::stoi(line1));
    }
    s1.close();
    s2.close();
    return sortScores(map);
}


std::vector<std::pair<std::string, int>> highscoreState::sortScores(std::vector<std::pair<std::string, int>> map)
{
    std::sort(map.begin(), map.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return map;
}




void startingState::setBackground() 
{
    std::cout << "Still running\n";
    efylw5Engine* ptrEngine = getEngine();
    SimpleImage image = ImageManager::loadImage(getImageURL(), true);
    image.renderImage(ptrEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
    ptrEngine->lockForegroundForDrawing();
    ptrEngine->drawForegroundRectangle(550,650,750,700,0xFFFFFF);
    ptrEngine->unlockForegroundForDrawing();
}

void States::setBackground()
{
}

std::vector<std::pair<std::string, int>> States::getScores()
{
    return std::vector<std::pair<std::string, int>>();
}

std::vector<std::pair<std::string, int>> States::sortScores(std::vector<std::pair<std::string, int>> map)
{
    return std::vector<std::pair<std::string, int>>();
}



void losingState::setBackground()
{
    efylw5Engine* ptrEngine = getEngine();
    SimpleImage image = ImageManager::loadImage(this->getImageURL(), true);
    image.renderImage(ptrEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
    ptrEngine->drawBackgroundLine(20, 10, 40, 20, 0xeae7db);
}

void winningState::setBackground()
{
    efylw5Engine* ptrEngine = getEngine();
    SimpleImage image = ImageManager::loadImage(getImageURL(), true);
    image.renderImage(ptrEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
    ptrEngine->drawBackgroundLine(20, 10, 40, 20, 0xeae7db);
}

void runningState::setBackground()
{
    efylw5Engine* ptrEngine = getEngine();
    SimpleImage image = ImageManager::loadImage(getImageURL(), true);
    image.renderImage(ptrEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
    ptrEngine->drawBackgroundLine(20, 10, 40, 20, 0xeae7db);
}

void tutorialState::setBackground()
{
    efylw5Engine* ptrEngine = getEngine();
    SimpleImage image = ImageManager::loadImage(getImageURL(), true);
    image.renderImage(ptrEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
    ptrEngine->drawBackgroundLine(20, 10, 40, 20, 0xeae7db);
}

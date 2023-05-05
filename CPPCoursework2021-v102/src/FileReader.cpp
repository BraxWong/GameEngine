#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <string>
/**
    Class: FileReader
    Function: parseUserConfig()
    Description: This will create an ifstream object and open the PlayerSettings.txt file.
                 Then it will attempt to read the file line by line and store the relevant 
                 information to the FileReader class. Then closing the ifstream object 
                 at the end.
*/
void FileReader::parseUserConfig()
{
    std::ifstream inputFile("PlayerSettings.txt");
    std::string line;

    while (std::getline(inputFile, line)) {
        size_t colonIndex = line.find(':');
        std::string valueStr = line.substr(colonIndex + 1);
        std::string value = valueStr;

        if (line.find("Crosshair Color") != std::string::npos) {
            setCrosshairColor(value);
        }
        else if (line.find("Crosshair Size") != std::string::npos) {
            setCrosshairSize(value);
        }
        else if (line.find("Target Shapes") != std::string::npos) {
            setTargetShapes(value);
        }
        else if (line.find("10 Points Target Color") != std::string::npos) {
            setColor10(value);
        }
        else if (line.find("20 Points Target Color") != std::string::npos) {
            setColor20(value);
        }
        else if (line.find("100 Points Target Color") != std::string::npos) {
            setColor100(value);
        }
        else if (line.find("Difficulty") != std::string::npos) {
            setDifficulty(value);
        }
        else if (line.find("Time Limits") != std::string::npos) {
            setTimeLimit(value);
        }
    }
    inputFile.close();
}

/**
    Class: FileReader
    Function: getCrosshairColor()
    Description: This is used in the efylw5Engine class.This will first convert the 
                 crosshairColor member variable from string to an integer. 
                 Then it will determine which color it represents.
                 1 == White, 2 == Red, 3 == Purple, 4 == Orange
    Return: The color hex code
*/
unsigned int FileReader::getCrosshairColor()
{
    int color = stoi(crosshairColor);
    if (color == 1)
    {
        return 0xFFFFFF;
    }
    else if (color == 2)
    {
        return 0xFF0000;
    }
    else if (color == 3)
    {
        return 0xA020F0;
    }
    else 
    {
        return 0xFFA500;
    }
}

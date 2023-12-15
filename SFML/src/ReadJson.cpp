#include "stdafx.h"
#include <fstream>
#include <string>
void ReadJson(int* imapW, int* imapH, int* iHillsCount, float* iVegDensity)
{
    std::ifstream json;//файловый поток
    json.open("Settings.json");//открытие файла
    if (!json.is_open()) //проверка на существование
    {
        std::cout << "File not found!" << std::endl;
        return;
    }
    std::string str;
    std::getline(json, str);
    std::getline(json, str);
    
    std::getline(json, str);
    auto slashPosition = str.find_first_of(':'); 
    str.erase(str.begin(), str.begin() + slashPosition+1);
    str.pop_back();
    *imapW = std::stoi(str);

    std::getline(json, str);
    slashPosition = str.find_first_of(':');
    str.erase(str.begin(), str.begin() + slashPosition + 1);
    str.pop_back();
    *imapH = std::stoi(str);

    std::getline(json, str);
    slashPosition = str.find_first_of(':');
    str.erase(str.begin(), str.begin() + slashPosition + 1);
    str.pop_back();
    *iHillsCount = std::stoi(str);

    std::getline(json, str);
    slashPosition = str.find_first_of(':');
    str.erase(str.begin(), str.begin() + slashPosition + 1);
    *iVegDensity = std::stof(str);

}
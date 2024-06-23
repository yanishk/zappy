/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** ParsesModelConfig
*/

#include "ParsesModelConfig.hpp"
#include "Utils.hpp"

void Zappy::ParsesModelConfig::parseSizeModel(std::string &line)
{
    std::string modelSize = "Size=";

    if (line.compare(0, modelSize.length(), modelSize) == 0) {
        line.erase(0, modelSize.length());
        float size = std::stof(line.c_str());
        _sizeList.push_back(size);
    }
}

void Zappy::ParsesModelConfig::parsePathModel(std::string &line)
{
    std::string modelPath = "Path=";
    std::pair<std::pair<std::string, float>, int> tmpPair;

    if (line.compare(0, modelPath.length(), modelPath) == 0) {
        line.erase(0, modelPath.length());
        tmpPair.first.first = line;
        _pathList.push_back(line);
    }
}

void Zappy::ParsesModelConfig::parseTypeModel(std::string &line)
{
    std::string modelType = "Type=";

    if (line.compare(0, modelType.length(), modelType) == 0) {
        line.erase(0, modelType.length());
        if (line == ITEM) {
            _typeList.push_back(Item);
        } else if (line == ISLAND) {
            _typeList.push_back(Island);
        } else if (line == PLAYER) {
            _typeList.push_back(Player);
        } else if (line == EGG) {
            _typeList.push_back(Egg);
        } else if (line == SKYM) {
            _typeList.push_back(SkyM);
        } else
            throw ErrorHandling("Bad config file");
    }
}

ZappyModel Zappy::ParsesModelConfig::parsesFile(std::string path)
{
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        parsePathModel(line);
        parseSizeModel(line);
        parseTypeModel(line);
    }
    for (std::size_t i = 0; i < _pathList.size(); i++) {
        std::pair<std::pair<std::string, float>, int> tmpPair;
        tmpPair.first.first = _pathList[i];
        tmpPair.first.second = _sizeList[i];
        tmpPair.second = _typeList[i];
        _parsedInfo.push_back(tmpPair);
    }
    return _parsedInfo;
}
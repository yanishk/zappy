/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** ParsesModelConfig
*/

#include "ParsesModelConfig.hpp"
#include "Utils.hpp"

void ParsesModelConfig::parseSizeModel(std::string &line)
{
    std::string modelSize = "Size=";

    if (line.compare(0, modelSize.length(), modelSize) == 0) {
        line.erase(0, modelSize.length());
        float size = std::stof(line.c_str());
        _sizeList.push_back(size);
    }
}

void ParsesModelConfig::parsePathModel(std::string &line)
{
    std::string modelPath = "Path=";
    std::pair<std::pair<std::string, float>, int> tmpPair;

    if (line.compare(0, modelPath.length(), modelPath) == 0) {
        line.erase(0, modelPath.length());
        tmpPair.first.first = line;
        _pathList.push_back(line);
    }
}

void ParsesModelConfig::parseTypeModel(std::string &line)
{
    std::string modelType = "Type=";

    if (line.compare(0, modelType.length(), modelType) == 0) {
        line.erase(0, modelType.length());
        if (line == "Item") {
            _typeList.push_back(Item);
        }
        else if (line == "Island") {
            _typeList.push_back(Island);
        }
        else if (line == "Player") {
            _typeList.push_back(Player);
        }
        else
            throw ErrorHandling("Bad config file");
    }
}

std::vector<std::pair<std::pair<std::string, float>, int>> ParsesModelConfig::parsesFile(std::string path)
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
        tmpPair.first.first = _pathList.at(i);
        tmpPair.first.second = _sizeList.at(i);
        tmpPair.second = _typeList.at(i);
        _parsedInfo.push_back(tmpPair);
    }
    return _parsedInfo;
}
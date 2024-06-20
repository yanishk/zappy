/*
** EPITECH PROJECT, 2024
** Island file
** File description:
** Zappy proj
*/

#include "Island.hpp"

void Island::render()
{
    DrawModel(_islandModel, _islandPosition, _islandSize, WHITE);
}

void Island::fillModel(std::pair<Model, float> model)
{
    _islandModel = model.first;
    _islandSize = model.second;
}

void Island::setIslandPos(Vector3 pos)
{
    _islandPosition = pos;
}

AllIsland::AllIsland(CommandManager &cmd) : _cmd(cmd)
{

}

void AllIsland::setAllIsland(std::pair<Model, float> model)
{
    if (!_cmd.getCommandAt(MSZ_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(MSZ_CMD, 0);

        std::pair<int, int> mapSize;
        mapSize.first = std::atoi(cmd.front().c_str());
        mapSize.second = std::atoi(cmd[1].c_str());
        float posX = 0;
        float posY = 0;
        _allIsland.clear();
        for (int i = 0; i < mapSize.first; i++) {
            posY = 0;
            posX += spaceBetwenIsland;
            for (int j = 0; j <mapSize.second; j++) {
                Island tmpIsland;
                _allIsland.push_back(tmpIsland);
                model.first.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0,
                    DEG2RAD*(std::rand() % 360), DEG2RAD*0});
                _allIsland.back().fillModel(model);
                _allIsland.back().setIslandPos((Vector3) {posX, -4, posY});
                posY += spaceBetwenIsland;
            }
        }
        _cmd.eraseFirstCmdInMap(MSZ_CMD);
    }
}

void AllIsland::renderAll(void)
{
    for (auto &i : _allIsland) {
        i.render();
    }
}

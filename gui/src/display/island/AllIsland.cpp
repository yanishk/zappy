/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllIsland
*/

#include "AllIsland.hpp"

Zappy::AllIsland::AllIsland(Zappy::CommandManager &cmd) : _cmd(cmd)
{

}

void Zappy::AllIsland::setAllElements(std::vector<std::pair<Model, float>> model)
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
            for (int j = 0; j < mapSize.second; j++) {
                Island tmpIsland;
                std::size_t modelIndex = rand() % model.size();
                _allIsland.push_back(tmpIsland);
                model[modelIndex].first.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0,
                    DEG2RAD*(std::rand() % CIRCUMFERENCE), DEG2RAD*0});
                _allIsland.back().setModel(model[modelIndex]);
                _allIsland.back().setIslandPos((Vector3) {posX, ISLAND_ALTITUDE, posY});
                posY += spaceBetwenIsland;
            }
        }
        _cmd.eraseFirstCmdInMap(MSZ_CMD);
    }
}

void Zappy::AllIsland::renderAllElements(void)
{
    for (auto &i : _allIsland) {
        i.render();
    }
}

std::size_t Zappy::AllIsland::getTotalNbrElements(void)
{
    return _allIsland.size();
}

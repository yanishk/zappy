/*
** EPITECH PROJECT, 2024
** AllEggs file
** File description:
** Zappy proj
*/

#include "Eggs.hpp"

void AllEggs::loadEggModel(std::pair<Model, float> modelPair)
{
    _model = modelPair.first;
    _size = modelPair.second;
}

void AllEggs::addEggToIsland(Vector3 position, int eggID)
{
    Egg tmpEgg(position);

    tmpEgg._eggModel = _model;
    tmpEgg._eggID = eggID;
    tmpEgg.RngRotate = std::rand() % (210 - 159 + 1) + 159;
    tmpEgg._eggModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * 100, DEG2RAD
        * tmpEgg.RngRotate, DEG2RAD * 0});
    _allEggs.push_back(tmpEgg);
}

void AllEggs::removeEggFromIsland(int eggID)
{
    for (auto it = _allEggs.begin(); it != _allEggs.end(); ++it) {
        if (it->_eggID == eggID) {
            _allEggs.erase(it);
            break;
        }
    }
}

Vector3 AllEggs::getEggRealPos(int eggID)
{
    for (auto &i: _allEggs) {
        if (i._eggID == eggID) {
            return i._realPos;
        }
    }
    return {};
}

void AllEggs::drawEgg()
{
    for (auto &i: _allEggs) {
        DrawModel(i._eggModel , i.getPosition(), 0.3, WHITE);
    }
}

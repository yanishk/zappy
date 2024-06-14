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
    tmpEgg._eggModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * 90, DEG2RAD
        * (std::rand() % 360), DEG2RAD * 0});
    _allEggs.push_back(tmpEgg);
}

void AllEggs::removeEggFromIsland(int eggID)
{
    for (std::size_t i = 0; i < _allEggs.size(); i++) {
        if (_allEggs.at(i)._eggID == eggID) {
            _allEggs.erase(_allEggs.begin() + i);
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

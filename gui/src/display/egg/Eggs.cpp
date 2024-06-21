/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include <unordered_map>

#include "Eggs.hpp"

Vector3 Egg::get3DEggPos()
{
    return _egg3DPosition;
}

void Egg::render()
{
    DrawModel(_eggModel, get3DEggPos(), _eggSize, WHITE);
}

void Egg::fillModel(std::pair<Model, float> model)
{
    _eggModel = model.first;
    _eggSize = model.second;
    float rngRotate = std::rand() % (210 - 159 + 1) + 159;
    float tiltAngle = (std::rand() % 40) + 80;
    _eggModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * tiltAngle, DEG2RAD * rngRotate, DEG2RAD * 0});
}

void Egg::setEggPosAndID(Vector2 pos, int eggId)
{
    _eggID = eggId;
    _eggRealPos = pos;
    _egg3DPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, 1.0, pos.y * spaceBetwenIsland};
    _egg3DPosition.x += -2 + (std::rand() % 4);
    _egg3DPosition.z += -2 + (std::rand() % 4);
}

Vector2 Egg::getEggRealPos()
{
    return _eggRealPos;
}

int Egg::getEggId()
{
    return _eggID;
}

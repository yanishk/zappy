/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include <unordered_map>

#include "Eggs.hpp"

Vector3 Zappy::Egg::get3DEggPos()
{
    return _egg3DPosition;
}

void Zappy::Egg::render()
{
    DrawModel(_eggModel, get3DEggPos(), _eggSize, WHITE);
}

void Zappy::Egg::setModel(std::pair<Model, float> model)
{
    _eggModel = model.first;
    _eggSize = model.second;
    float rngRotate = std::rand() % ROTATE_RAND_RANGE;
    float tiltAngle = (std::rand() % 40) + DEFAULT_EGG_INCLIN;
    _eggModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * tiltAngle, DEG2RAD * rngRotate, DEG2RAD * 0});
}

void Zappy::Egg::setEggPosAndID(Vector2 pos, int eggId)
{
    _eggID = eggId;
    _eggRealPos = pos;
    _egg3DPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, 1.0, pos.y * spaceBetwenIsland};
    _egg3DPosition.x += -2 + (std::rand() % 4);
    _egg3DPosition.z += -2 + (std::rand() % 4);
}

Vector2 Zappy::Egg::getEggRealPos()
{
    return _eggRealPos;
}

int Zappy::Egg::getEggId()
{
    return _eggID;
}

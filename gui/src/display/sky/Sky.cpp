/*
** EPITECH PROJECT, 2024
** Sky file
** File description:
** zappy proj
*/

#include "Sky.hpp"

void Sky::render()
{
    DrawModel(_skyModel, _skyPosition, SKY_SIZE, WHITE);
}

void Sky::setModel(std::pair<Model, float> model)
{
    _skyModel = model.first;
    _skySize = model.second;
}

void Sky::setSkyPos(Vector3 pos)
{
    _skyPosition = Utils::setVector3(pos.x, 0, pos.z);
}

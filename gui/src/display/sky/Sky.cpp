/*
** EPITECH PROJECT, 2024
** Sky file
** File description:
** zappy proj
*/

#include "Sky.hpp"

void Zappy::Sky::render()
{
    DrawModel(_skyModel, _skyPosition, SKY_SIZE, WHITE);
}

void Zappy::Sky::setModel(std::pair<Model, float> model)
{
    _skyModel = model.first;
    _skySize = model.second;
}

void Zappy::Sky::setSkyPos(Vector3 pos)
{
    _skyPosition = Zappy::Utils::Vec3(pos.x, 0, pos.z);
}

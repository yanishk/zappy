/*
** EPITECH PROJECT, 2024
** Island file
** File description:
** Zappy proj
*/

#include "Island.hpp"

void Zappy::Island::render()
{
    DrawModel(_islandModel, _islandPosition, _islandSize, WHITE);
}

void Zappy::Island::setModel(std::pair<Model, float> model)
{
    _islandModel = model.first;
    _islandSize = model.second;
}

void Zappy::Island::setIslandPos(Vector3 pos)
{
    _islandPosition = pos;
}

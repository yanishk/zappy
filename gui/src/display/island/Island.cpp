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

void Island::setModel(std::pair<Model, float> model)
{
    _islandModel = model.first;
    _islandSize = model.second;
}

void Island::setIslandPos(Vector3 pos)
{
    _islandPosition = pos;
}

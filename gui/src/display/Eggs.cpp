/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include "Eggs.hpp"

Egg::Egg(Vector3 position)
{
    _playerHight = 1.1;
    _realPos = position;
    _eggPosition = (Vector3){(position.x + 1) * spaceBetwenIsland, 1.1, position.z * spaceBetwenIsland};
    _eggPosition.x += -2 + (std::rand() % 4);
    _eggPosition.z += -2 + (std::rand() % 4);
}

Vector3 Egg::getPosition()
{
    return _eggPosition;
}

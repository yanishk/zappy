/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ressources
*/

#include "Ressources.hpp"

bool Zappy::Ressources::addRessources(const std::string &ressource, int value)
{
    _ressources[ressource] += value;
    return true;
}
const std::string &Zappy::Ressources::indexToRessource(int index)
{
    switch (index) {
        case Food:
            return FOOD;
        case Linemate:
            return LINEMATE;
        case Deraumere:
            return DERAUMERE;
        case Sibur:
            return SIBUR;
        case Mendiane:
            return MENDIANE;
        case Phiras:
            return PHIRAS;
        case Thystame:
            return THYSTAME;
        default:
            return "none";
    }

    return "none";
}

std::vector<int> Zappy::Ressources::getAllValueRessources()
{
    return {
        _ressources[FOOD],
        _ressources[LINEMATE],
        _ressources[DERAUMERE],
        _ressources[SIBUR],
        _ressources[MENDIANE],
        _ressources[PHIRAS],
        _ressources[THYSTAME]
    };
}


bool Zappy::Ressources::removeRessources(const std::string &ressource, int value)
{
    if (_ressources[ressource] >= value) {
        _ressources[ressource] -= value;
        return true;
    }
    return false;
}

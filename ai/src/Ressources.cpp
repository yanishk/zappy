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

bool Zappy::Ressources::updateRessources(const std::string &ressource, int value)
{
    bool isExisting = false;

    for (const auto &i:_ressources) {
        if (i.first == ressource) {
            isExisting = true;
        }
    }

    if (!isExisting) {
        return false;
    }

    _ressources[ressource] = value;
    return true;
}

std::string Zappy::Ressources::indexToRessource(int index)
{
    switch (index) {
        case Food:
            return std::string(FOOD);
        case Linemate:
            return std::string(LINEMATE);
        case Deraumere:
            return std::string(DERAUMERE);
        case Sibur:
            return std::string(SIBUR);
        case Mendiane:
            return std::string(MENDIANE);
        case Phiras:
            return std::string(PHIRAS);
        case Thystame:
            return std::string(THYSTAME);
        default:
            return std::string("none");
    }

    return std::string("none");
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

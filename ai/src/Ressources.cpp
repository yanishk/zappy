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

bool Zappy::Ressources::removeRessources(const std::string &ressource, int value)
{
    if (_ressources[ressource] >= value) {
        _ressources[ressource] -= value;
        return true;
    }
    return false;
}

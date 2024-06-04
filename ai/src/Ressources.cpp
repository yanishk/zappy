/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ressources
*/

#include "Ressources.hpp"

void Zappy::Ressources::addRessources(const std::string &ressource, int value)
{
    _ressources[ressource] += value;
}

void Zappy::Ressources::removeRessources(const std::string &ressource, int value)
{
    if (_ressources[ressource] >= value) {
        _ressources[ressource] -= value;
    }
}

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

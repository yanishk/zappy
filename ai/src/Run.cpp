/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Run
*/

#include <iostream>

#include "AI/IAi.hpp"
#include "Run.hpp"

bool Zappy::run(const std::string &name, const std::string &port, const std::string &home) 
{
    Network::Network network(port, name, home);
    std::unique_ptr<IAi> ai = Zappy::getAI(network);

    if (ai == nullptr) {
        return false;
    }

    return ai.get()->run(network);
}

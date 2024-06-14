/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Team.hpp"
#include "AI/Queen.hpp"

bool Zappy::Queen::run()
{
    initialize();

    while (true) {

        std::cout << "Queen test forward\n";
        if (!this->forward()) {
            std::cout << "Queen can't go forward\n";
        }

    }

    return true;
}

bool Zappy::Queen::initialize()
{
    const std::size_t value = connectNumber();

    for (std::size_t i = 0; i < value; ++i) {
        Queen(_network.getPort(), _name);
    }

    if (!fork()) {
        std::cout << "Queen can't forked\n";
    }
    std::cout << "Queen forked\n";

    return true;
}

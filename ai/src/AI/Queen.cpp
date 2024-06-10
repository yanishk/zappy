/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "AI/Queen.hpp"

int Zappy::Queen::run()
{
    if (_level == INITIALIZE_MODE) {
        return initialize();
    }

    return EXIT_SUCCESS;
}

bool Zappy::Queen::initialize()
{
    const std::size_t maxPlayers = connectNumber();
    std::cerr << "mp: " << maxPlayers << "\n";
    for (std::size_t i = 0; i < maxPlayers; i++) {
        std::cerr << "ici\n";
        Zappy::Queen queen(_network.getPort(), _name);
    }

    _level = FIRST_LEVEL;

    return true;
}

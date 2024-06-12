/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Team.hpp"
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
    Zappy::Team &team = Zappy::Team::getTeam(GET);

    for (std::size_t i = 0; i < maxPlayers; i++) {
        Zappy::Queen queen(_network.getPort(), team.getName());
    }

    _level = FIRST_LEVEL;

    return true;
}

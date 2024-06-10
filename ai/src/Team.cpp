/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Team
*/

#include "Team.hpp"

Zappy::Team &Zappy::Team::getTeam(TeamOptions options)
{
    static Zappy::Team team(options._name, options._port, std::move(options._queen));

    return team;
}

int Zappy::Team::run()
{
    while (true) {
        for (auto &player : _players) {
            player.get()->run();
        }
    }

    return EXIT_SUCCESS;
}

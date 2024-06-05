/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Team
*/

#include "Team.hpp"

int Zappy::Team::run()
{
    while (true) {
        for (auto &player : _players) {
            player.get()->run();
        }
    }

    return EXIT_SUCCESS;
}

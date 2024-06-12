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

const std::string &Zappy::Team::getName()
{
    return _name;
}

int Zappy::Team::run()
{
    while (true) {

        for (std::size_t i = 0; i < _players.size(); ++i) {

            if (!_players[i].get()->run()) {
                _players.erase(_players.begin() + i);                
            }

        }

    }

    return EXIT_SUCCESS;
}
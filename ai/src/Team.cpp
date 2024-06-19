/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Team
*/

#include "AI/Searcher.hpp"
#include "Team.hpp"

Zappy::Team &Zappy::Team::getTeam(TeamOptions options)
{
    static Zappy::Team team(options._name, options._port);

    return team;
}

const std::string &Zappy::Team::getName()
{
    return _name;
}

int Zappy::Team::run()
{
    _players.push_back(std::make_unique<Queen>(_port, _name));

    return EXIT_SUCCESS;
}

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
    static Zappy::Team team(options._name, options._port, options._home);

    return team;
}

const std::string &Zappy::Team::getName()
{
    return _name;
}

int Zappy::Team::run()
{
    _players.push_back(std::make_unique<Searcher>(_port, _name, Order(1, Ressources(1, 0, 0, 0, 0, 0))));

    return EXIT_SUCCESS;
}

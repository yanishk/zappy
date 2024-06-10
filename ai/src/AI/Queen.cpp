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

    if (_wait) {
        _wait -= 1;
        return EXIT_SUCCESS;
    }

    if (_network.getInfoFromServer() == DEAD) {
        return ERROR;
    }

    while (_ressources.getRessource(FOOD) < CRITICAL_FOOD) {
        _actions.push_back(Eat);
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

bool Zappy::Queen::executeAction()
{
    if (_actions.empty()) {
        return false;
    }

    if (_actions.front() == Look) {

    }

    if (_actions.front() == Eat) {

    }

    if (_actions.front() == Elevation) {

    }

    if (_actions.front() == Fork) {

    }

    _actions.erase(_actions.begin());

    return true;
}
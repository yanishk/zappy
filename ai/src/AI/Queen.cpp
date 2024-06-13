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
    if (_level == INITIALIZE_MODE) {
        return initialize();
    }

    if (!this->forward()) {
        std::cerr << "Queen can't move forward\n";
    }

    return true;
}

bool Zappy::Queen::initialize()
{

    _level = FIRST_LEVEL;

    return true;
}

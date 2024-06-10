/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#include "AI/Quentin.hpp"

int Zappy::Quentin::run()
{
    if (_wait) {
        _wait -= 1;
        return EXIT_SUCCESS;
    }

    if (_nbRefills > LAST_REFILL && _ressources.getRessource(FOOD) == LAST_FOOD) {
        _actions.push_back(Fork);
        return EXIT_SUCCESS;
    }

    if (_ressources.getRessource(FOOD)) {
        _actions.push_back(Drop);
    }

    executeAction();

    return EXIT_SUCCESS;
}

bool Zappy::Quentin::executeAction()
{
    if (_actions.empty()) {
        return false;
    }

    if (_actions.front() == Drop) {
        setObject(FOOD);
    }

    if (_actions.front() == Fork) {
        // --- On doit fork un nouveau Quentin avec (_nbRefills - 1) en paramètres --- //
    }

    _actions.erase(_actions.begin());

    return true;
}

/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#include "AI/Quentin.hpp"
#include "Team.hpp"

int Zappy::Quentin::run()
{
    if (_wait) {
        _wait -= 1;
        return EXIT_SUCCESS;
    }

    if (_network.getInfoFromServer() == DEAD) {
        return ERROR;
    }

    if (_nbRefills > ZERO_REFILL && _ressources.getRessource(FOOD) == LAST_FOOD) {
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
        _wait = DROP_WAIT;
    }

    if (_actions.front() == Fork) {
        createQuentin();
    }

    _actions.erase(_actions.begin());

    return true;
}

bool Zappy::Quentin::createQuentin()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);

    if (_nbRefills == ZERO_REFILL) {
        return false;
    }

    fork();

    std::unique_ptr<Quentin> quentin = std::make_unique<Quentin>(_network.getPort(), _nbRefills - 1, team.getName());

    team._players.push_back(std::move(quentin));
    _wait = FORK_WAIT;

    return true;
}
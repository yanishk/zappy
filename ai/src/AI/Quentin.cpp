/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#include "AI/Quentin.hpp"
#include "Team.hpp"

bool Zappy::Quentin::run()
{
    while (true) {

        std::cout << "QUENTIN STEP RUN\n";

        if (_nbRefills > ZERO_REFILL && _ressources[FOOD] == LAST_FOOD) {
            _actions.push_back(Fork);
            return true;
        }

        if (_ressources[FOOD]) {
            _actions.push_back(Drop);
        }

        executeAction();

    }

    return true;
}

bool Zappy::Quentin::executeAction()
{
    if (_actions.empty()) {
        return false;
    }

    if (_actions.front() == Drop) {
        setObject(FOOD);
        _ressources[FOOD] -= ONE_COUNT;
        std::cout << QUENTIN_DROP;
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

    if (!fork()) {
        return false;
    }

    team._players.push_back(std::make_shared<Quentin>(_network.getPort(), team.getName(), _nbRefills - 1));

    std::cout << QUENTIN_FORK;

    return true;
}

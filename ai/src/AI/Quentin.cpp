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
        std::cout << "test quentin forward\n";
        if (!this->forward()) {
            std::cout << "Quentin can't go forward\n";
        }
    }
    // if (_network.getInfoFromServer() == DEAD) {
        // return false;
    // }
// 
    // if (_nbRefills > ZERO_REFILL && _ressources.getRessource(FOOD) == LAST_FOOD) {
        // _actions.push_back(Fork);
        // return true;
    // }
// 
    // if (_ressources.getRessource(FOOD)) {
        // _actions.push_back(Drop);
    // }
// 
    // executeAction();

    return true;
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
        createQuentin();
    }

    _actions.erase(_actions.begin());
    forward();
    return true;
}

bool Zappy::Quentin::createQuentin()
{
    // Zappy::Team &team = Zappy::Team::getTeam(GET);

    if (_nbRefills == ZERO_REFILL) {
        return false;
    }

    fork();

    // Quentin quentin(_network.getPort(), team.getName(), _nbRefills - 1);
// 
    // team._players.push_back(std::make_shared<Quentin>(quentin));

    return true;
}

/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Team.hpp"
#include "AI/Queen.hpp"
#include "AI/Quentin.hpp"

bool Zappy::Queen::run()
{
    initialize();

    while (true) {

        _look = look();

        checkFood();
        checkIncantation();
        execute();

    }

    return true;
}

bool Zappy::Queen::initialize()
{
    const std::size_t value = connectNumber();

    for (std::size_t i = 0; i < value; ++i) {
        Queen(_network.getPort(), _name);
    }

    return true;
}

bool Zappy::Queen::checkFood()
{
    _stock = countRessources(_look[HERE], FOOD);

    while (_ressources[FOOD] < CRITICAL_FOOD && _stock) {
        _actions.push_back(TakeFood);
    }

    if (_stock < CRITICAL_STOCK) {
        _actions.push_back(ForkFood);
    }

    return true;
}

bool Zappy::Queen::checkIncantation()
{
    return true;
}

bool Zappy::Queen::execute()
{
    while (_actions.size()) {

        for (const auto &task : _execute) {

            if (_actions.front() == task.first) {
                task.second();
            }

        }

        _actions.erase(_actions.begin());

    }

    return true;
}

bool Zappy::Queen::takeFood()
{
    if (!takeObject(FOOD)) {
        return false;
    }

    _ressources[FOOD] += ONE_FOOD;
    _stock -= ONE_FOOD;

    return true;
}

bool Zappy::Queen::forkFood()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);

    if (!fork()) {
        return false;
    }

    team._players.push_back(std::make_unique<Quentin>(_network.getPort(), _name, INFINY));

    return true;
}

std::size_t Zappy::Queen::countRessources(const std::string &ressources, const std::string &index)
{
    if (!index.length()) {
        return NONE;
    }

    std::size_t count = 0;
    std::size_t offset = ressources.find(index);

    while (offset != std::string::npos) {
        count += 1;
        offset = ressources.find(index, offset + index.length());
    }

    return count;
}

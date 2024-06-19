/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Team.hpp"
#include "Order.hpp"
#include "AI/Queen.hpp"
#include "AI/Quentin.hpp"
#include "AI/Searcher.hpp"

bool Zappy::Queen::run()
{
    initialize();

    while (true) {

        std::cout << QUEEN_START;

        _look = look();

        if (_look[HERE] == DEAD) {
            std::cout << QUEEN_DEAD;
            return false;
        }

        std::cout << QUEEN_LOOK;
        
        for (std::size_t i = 0; i < _look.size(); i++) {
            std::cout << QUEEN_LOOK_ITEM(_look[i]);
        }

        _nbTours += NB_TOURS_LOOK;

        if (_nbTours > NB_TOURS_MAX) {
            _ressources[FOOD] -= ONE_COUNT;
            _nbTours = INITIAL_COUNT;
        }

        std::cout << QUEEN_CHECK_FOOD;
        checkFood();

        std::cout << QUEEN_CHECK_INCANTATION;
        checkIncantation();

        std::cout << QUEEN_EXECUTE;
        execute();

    }

    return true;
}

bool Zappy::Queen::initialize()
{
    const std::size_t value = connectNumber();

    std::cout << QUEEN_INITIALIZE(value);

    for (std::size_t i = 0; i < value; ++i) {
        Queen(_network.getPort(), _name, false);
    }

    return true;
}

bool Zappy::Queen::checkFood()
{
    _stock = countRessources(_look[HERE], FOOD);

    std::cout << QUEEN_FOOD(_ressources[FOOD]);
    std::cout << QUEEN_FOOD_STOCK(_stock);

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
    if (!checkPlayers() || !checkRessources()) {
        _actions.push_back(ForkSearcher);
        return false;
    }

    _actions.push_back(Incantation);

    return true;
}

bool Zappy::Queen::checkRessources()
{
    const std::vector<std::string> ressources = { LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME };

    for (std::size_t i = 0; i < ressources.size(); i++) {

        std::size_t ressourcesCount = countRessources(_look[HERE], ressources[i]);
        std::size_t ressourcesNeed = _incatation[_level - LEVEL_INDEX].second[ressources[i]];

        if (ressourcesCount < ressourcesNeed) {
            return false;
        }

    }

    return true;
}

bool Zappy::Queen::checkPlayers()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);
    std::size_t count = INITIAL_COUNT;

    for (auto &player: team._players) {

        bool checkLevel = (player.get()->getLevel() == _level);
        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));

        if (checkLevel && checkPosition) {
            count += ONE_COUNT;
        }

    }

    if (count < _incatation[_level - LEVEL_INDEX].first) {
        return false;
    }

    return true;
}

bool Zappy::Queen::execute()
{
    for (std::size_t i = 0; i < _actions.size(); i++) {

        for (const auto &task : _execute) {

            if (_actions[i] == task.first) {
                task.second();
                break;
            }

        }

    }

    _actions.clear();

    return true;
}

bool Zappy::Queen::takeFood()
{
    if (!takeObject(FOOD)) {
        return false;
    }

    std::cout << QUEEN_TAKE_FOOD;

    _ressources[FOOD] += ONE_FOOD;
    _stock -= ONE_FOOD;
    
    _nbTours += NB_TOURS_FOOD;

    return true;
}

bool Zappy::Queen::forkFood()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);

    if (!fork()) {
        return false;
    }

    std::cout << QUEEN_FORK_FOOD;

    team._players.push_back(std::make_shared<Quentin>(_network.getPort(), _name, INFINY));

    _nbTours += NB_TOURS_FORK;

    return true;
}

Zappy::Ressources Zappy::Queen::getCommand(bool already)
{
    const std::vector<std::string> ressources = { LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME };
    double start = _nbCommands * MAX_ORDER;
    std::size_t count = INITIAL_COUNT;

    Zappy::Ressources command;

    for (std::size_t i = 0; i < ressources.size(); i++) {

        std::size_t ressourcesCount = countRessources(_look[HERE], ressources[i]);
        std::size_t ressourcesNeed = _incatation[_level - LEVEL_INDEX].second[ressources[i]];

        std::size_t ressourcesToSearch = ressourcesNeed - ressourcesCount;

        while ((already || start > POSITIVE) && ressourcesToSearch) {

            start -= ONE_COUNT;
            ressourcesToSearch -= ONE_COUNT;

        }

        if (!already && start > POSITIVE) {
            continue;
        }

        while (ressourcesToSearch && count < MAX_ORDER) {

            command[ressources[i]] += ONE_COUNT;
            ressourcesToSearch += ONE_COUNT;

        }

    }

    if (!count) {
        return getCommand(true);
    }

    return command;

}

bool Zappy::Queen::forkSearcher()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);

    Zappy::Ressources command = getCommand(false);
    std::size_t levelToReach = START_LEVEL;

    if (_nbCommands > LONG_COMMAND) {
        levelToReach = _incatation[_level - LEVEL_INDEX].first;
    }

    if (_nbCommands < _incatation[_level - LEVEL_INDEX].first) {
        levelToReach = _incatation[_level - LEVEL_INDEX].first;
    }

    command[FOOD] -= FOOD_START_VALUE;
    _nbCommands += ONE_COUNT;

    Order order(levelToReach, command);

    if (!fork()) {
        return false;
    }

    std::cout << QUEEN_FORK_SEARCHER;
    std::cout << SEARCHER_LEVEL(order.getLevel());
    order.getRessources().dump();

    team._players.push_back(std::make_shared<Searcher>(_network.getPort(), _name, order));

    _nbTours += NB_TOURS_FORK;

    return true;
}

bool Zappy::Queen::setIncantation()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);
    std::size_t count = _incatation[_level - LEVEL_INDEX].first;

    for (auto &player: team._players) {

        bool checkLevel = (player.get()->getLevel() == _level);
        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));

        if (count && checkLevel && checkPosition) {
            count -= ONE_COUNT;
            player.get()->setIsIncantation(true);
        }

    }

    return true;
}

bool Zappy::Queen::removeIncantation()
{
    Zappy::Team &team = Zappy::Team::getTeam(GET);
    std::size_t count = _incatation[_level - LEVEL_INDEX].first;

    std::size_t level = _level;

    for (auto &player: team._players) {

        bool checkLevel = (player.get()->getLevel() == level);
        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));
        bool isIncantation = player.get()->getIsIncantation();

        if (count && checkLevel && checkPosition && isIncantation) {
            count -= ONE_COUNT;
            player.get()->setIsIncantation(false);
            player.get()->setLevel(player.get()->getLevel() + ONE_LEVEL);
        }

    }

    return true;
}

bool Zappy::Queen::makeIncantation()
{
    setIncantation();

    if (!incantation()) {
        return false;
    }

    std::cout << QUEEN_INCANTATION;

    _nbCommands = INITIAL_COUNT;
    _nbTours += NB_TOURS_INCANTATION;

    removeIncantation();

    return true;
}

std::size_t Zappy::Queen::countRessources(const std::string &ressources, const std::string &index)
{
    if (!index.length()) {
        return NONE;
    }

    std::size_t count = INITIAL_COUNT;
    std::size_t offset = ressources.find(index);

    while (offset != std::string::npos) {
        count += ONE_COUNT;
        offset = ressources.find(index, offset + index.length());
    }

    return count;
}

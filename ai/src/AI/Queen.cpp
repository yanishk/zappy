/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Run.hpp"
#include "CreateAI.hpp"
#include "AI/Queen.hpp"

bool Zappy::Queen::run(Network::Network &network)
{
    std::cout << QUEEN_WELCOME;

    if (!initialize(network)) {
        return false;
    }

    std::cout << QUEEN_START;

    while (true) {

        if (!updateInventory(network)) {
            break;
        }

        std::cout << QUEEN_UPDATE_INVENTORY;

        _look = look(network);

        std::cout << QUEEN_LOOK;

        for (const auto &items: _look) {
            std::cout << QUEEN_LOOK_ITEM(items);
        }

        checkFood();

        if (!execute(network)) {
            break;
        };

    }

    std::cout << QUEEN_DEAD;

    return false;
}

bool Zappy::Queen::initialize(Network::Network &network)
{
    const std::size_t value = connectNumber(network);

    std::cout << QUEEN_INITIALIZE(value);

    for (std::size_t i = 0; i < value; ++i) {

        Network::Network child(network.getPort(), network.getName(), network.getHome());

        child.getInfoFromServer();
        child.sendInformationToServer(FORMAT_NAME(child.getName()));

        if (child.getInfoFromServer() == KO) {
            return false;
        }

    }

    return true;
}

bool Zappy::Queen::checkFood()
{
    _stock = countRessources(_look[HERE], FOOD);

    std::cout << QUEEN_FOOD(_ressources[FOOD]);
    std::cout << QUEEN_FOOD_STOCK(_stock);

    while (_ressources[FOOD] < CRITICAL_FOOD && _stock) {
        _actions.push_back(Take);
        _ressources[FOOD] += ONE_COUNT;
        _stock -= ONE_COUNT;
    }

    if (_stock < CRITICAL_STOCK) {
        _actions.push_back(ForkQueen);
    }

    return true;
}

//bool Zappy::Queen::checkIncantation()
//{
//    if (!checkPlayers() || !checkRessources()) {
//        _actions.push_back(ForkSearcher);
//        return false;
//    }
//
//    _actions.push_back(Incantation);
//
//    return true;
//}

//bool Zappy::Queen::checkRessources()
//{
//    const std::vector<std::string> ressources = { LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME };
//
//    for (std::size_t i = 0; i < ressources.size(); i++) {
//
//        std::size_t ressourcesCount = countRessources(_look[HERE], ressources[i]);
//        std::size_t ressourcesNeed = _incatation[_level - LEVEL_INDEX].second[ressources[i]];
//
//        if (ressourcesCount < ressourcesNeed) {
//            return false;
//        }
//
//    }
//
//    return true;
//}

//bool Zappy::Queen::checkPlayers()
//{
//    Zappy::Team &team = Zappy::Team::getTeam(GET);
//    std::size_t count = INITIAL_COUNT;
//
//    for (auto &player: team._players) {
//
//        bool checkLevel = (player.get()->getLevel() == _level);
//        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));
//
//        if (checkLevel && checkPosition) {
//            count += ONE_COUNT;
//        }
//
//    }
//
//    if (count < _incatation[_level - LEVEL_INDEX].first) {
//        return false;
//    }
//
//    return true;
//}

bool Zappy::Queen::execute(Network::Network &network)
{
    for (const auto &action: _actions) {

        for (const auto &task : _execute) {

            if (action == task.first) {

                if (!task.second(network)) {
                    return false;
                }

                break;

            }

        }

    }

    _actions.clear();

    return true;
}

bool Zappy::Queen::take(Network::Network &network)
{
    if (takeObject(network, FOOD) != Response::Ok) {
        return false;
    }

    std::cout << QUEEN_TAKE_FOOD;

    return true;
}

bool Zappy::Queen::forkQueen(Network::Network &network)
{
    if (fork(network) != Response::Ok) {
        return false;
    }

    std::cout << QUEEN_FORK;

    Zappy::createAI(network.getName(), network.getPort(), network.getHome());

    if (broadcastText(network, BROADCAST_QUEEN_LEVEL(_level)) != Response::Ok) {
        return false;
    }

    std::cout << QUEEN_LEVEL(_level);

    return true;
}

//Zappy::Ressources Zappy::Queen::getCommand(bool already)
//{
//    const std::vector<std::string> ressources = { LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME };
//    double start = _nbCommands * MAX_ORDER;
//    std::size_t count = INITIAL_COUNT;
//
//    Zappy::Ressources command;
//
//    for (std::size_t i = 0; i < ressources.size(); i++) {
//
//        std::size_t ressourcesCount = countRessources(_look[HERE], ressources[i]);
//        std::size_t ressourcesNeed = _incatation[_level - LEVEL_INDEX].second[ressources[i]];
//
//        std::size_t ressourcesToSearch = ressourcesNeed - ressourcesCount;
//
//        while ((already || start > POSITIVE) && ressourcesToSearch) {
//
//            start -= ONE_COUNT;
//            ressourcesToSearch -= ONE_COUNT;
//
//        }
//
//        if (!already && start > POSITIVE) {
//            continue;
//        }
//
//        while (ressourcesToSearch && count < MAX_ORDER) {
//
//            command[ressources[i]] += ONE_COUNT;
//            ressourcesToSearch += ONE_COUNT;
//
//        }
//
//    }
//
//    if (!count) {
//        return getCommand(true);
//    }
//
//    return command;
//
//}
//
//bool Zappy::Queen::forkSearcher()
//{
//    Zappy::Team &team = Zappy::Team::getTeam(GET);
//
//    Zappy::Ressources command = getCommand(false);
//    std::size_t levelToReach = START_LEVEL;
//
//    if (_nbCommands > LONG_COMMAND) {
//        levelToReach = _incatation[_level - LEVEL_INDEX].first;
//    }
//
//    if (_nbCommands < _incatation[_level - LEVEL_INDEX].first) {
//        levelToReach = _incatation[_level - LEVEL_INDEX].first;
//    }
//
//    command[FOOD] -= FOOD_START_VALUE;
//    _nbCommands += ONE_COUNT;
//
//    Order order(levelToReach, command);
//
//    if (!fork()) {
//        return false;
//    }
//
//    std::cout << QUEEN_FORK_SEARCHER;
//    std::cout << SEARCHER_LEVEL(order.getLevel());
//    order.getRessources().dump();
//
//    team._players.push_back(std::make_shared<Searcher>(_network.getPort(), _name, order));
//
//    _nbTours += NB_TOURS_FORK;
//
//    return true;
//}
//
//bool Zappy::Queen::setIncantation()
//{
//    Zappy::Team &team = Zappy::Team::getTeam(GET);
//    std::size_t count = _incatation[_level - LEVEL_INDEX].first;
//
//    for (auto &player: team._players) {
//
//        bool checkLevel = (player.get()->getLevel() == _level);
//        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));
//
//        if (count && checkLevel && checkPosition) {
//            count -= ONE_COUNT;
//            player.get()->setIsIncantation(true);
//        }
//
//    }
//
//    return true;
//}
//
//bool Zappy::Queen::removeIncantation()
//{
//    Zappy::Team &team = Zappy::Team::getTeam(GET);
//    std::size_t count = _incatation[_level - LEVEL_INDEX].first;
//
//    std::size_t level = _level;
//
//    for (auto &player: team._players) {
//
//        bool checkLevel = (player.get()->getLevel() == level);
//        bool checkPosition = (player.get()->getPosition() == POSITION(0.0,0.0));
//        bool isIncantation = player.get()->getIsIncantation();
//
//        if (count && checkLevel && checkPosition && isIncantation) {
//            count -= ONE_COUNT;
//            player.get()->setIsIncantation(false);
//            player.get()->setLevel(player.get()->getLevel() + ONE_LEVEL);
//        }
//
//    }
//
//    return true;
//}
//
//bool Zappy::Queen::makeIncantation()
//{
//    setIncantation();
//
//    if (!incantation()) {
//        return false;
//    }
//
//    std::cout << QUEEN_INCANTATION;
//
//    _nbCommands = INITIAL_COUNT;
//    _nbTours += NB_TOURS_INCANTATION;
//
//    removeIncantation();
//
//    return true;
//}

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

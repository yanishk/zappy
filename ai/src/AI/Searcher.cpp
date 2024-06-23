/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#include "Zappy.hpp"
#include "AI/Searcher.hpp"

void Zappy::Searcher::updateOrder()
{
    std::vector<int> valueOfOrderRessources = _order.getRessources().getAllValueRessources();
    std::vector<int> valueOfMyRessources = _ressources.getAllValueRessources();

    for (std::size_t i = 0; i < valueOfMyRessources.size(); ++i) {

        if ((valueOfMyRessources[i] == valueOfOrderRessources[i]) || (valueOfMyRessources[i] <= valueOfOrderRessources[i])) {

            _order.removeRessources(_ressources.indexToRessource(i), valueOfMyRessources[i]);

        }

    }
}

void Zappy::Searcher::searchFood(Network::Network &network)
{
    std::vector<std::string> lookForFood = look(network);
    std::size_t priority = 0;
    int index = 0;

    for (const auto &i: lookForFood) {

        if (i == FOOD) {
            priority = index;
        }
        index++;
    }

    whereIsThePriority(priority);
}


Zappy::Response Zappy::Searcher::dropItem(Network::Network &network)
{
    std::unordered_map<std::string, int> ressource = _ressources.getRessources();

    for (const auto &i: ressource) {

        if (i.first == FOOD) {
            continue;
        }

        for (int j = 0; j < i.second; ++j) {
            Zappy::Response rep = setObject(network, i.first);
            if (rep == Response::Dead) {
                return Response::Dead;
            } else if (rep == Response::Ko) {
                continue;
            }
            std::cerr << std::string("Searcher : " + std::to_string(_id) + " Set " + i.first + "\n");
        }
        _goBackToQueen = false;

    }

    return Response::Ok;
}

int Zappy::Searcher::checkQueenLevel()
{
    int size = 0;

    for (const auto &i: _messages) {
        if (size > MAX_CHECK_MESSAGE) {
            break;
        }
        std::istringstream stream(i.first);
        std::string otherId("");
        std::string message("");
        std::string value("");
        std::getline(stream, otherId, ':');
        std::getline(stream, message, ':');
        std::getline(stream, value, ':');

        if (otherId == QUEEN && message == LEVEL) {
            return std::atoi(value.c_str());
        }

    }

    return ERROR;
}

bool Zappy::Searcher::checkComingIsGood()
{
    for (const auto &i: _messages) {
        std::istringstream stream(i.first);
        std::string otherId("");
        std::string message("");
        std::string value("");
        std::getline(stream, otherId, ':');
        std::getline(stream, message, ':');
        std::getline(stream, value, ':');

        if (otherId == QUEEN && message == HERE_BROADCAST && std::atoi(value.c_str()) == _id) {
            return true;
        }

    }

    return false;
}

void Zappy::Searcher::checkQueenLevel(Network::Network &network)
{
    std::string response = network.getInfoFromServer();
    std::istringstream stream(response);
    std::string otherId("");
    std::string message("");
    std::string value("");

    std::getline(stream, otherId, ',');
    std::getline(stream, otherId, ':');
    std::getline(stream, message, ':');
    std::getline(stream, value, ':');
    std::cerr << "\t\tMESSAGE: " << message << "\n";
    std::cerr << "\t\tid: " << otherId << "\n";
    std::cerr << "\t\tvalue: " << value << "\n";

    if (otherId == QUEEN && message == LEVEL) {
        _queenLevel = std::atoi(value.c_str());
        _order.setRessources(_order.getLevelRessources(std::atoi(value.c_str())));
        _order.setLevel(std::atoi(value.c_str()));
        _inDelivery = true;
    }
}

bool Zappy::Searcher::run(Network::Network &network)
{

    if (_id > 0) {
        return false;
    }
    checkQueenLevel(network);

    while (true) {

        if (_goBackToQueen) {
            move(network);
            if (_nextMouvment.empty()) {
                dropItem(network);
            }
            dumpMovement();
            continue;
        }

        if (_ressources[FOOD] < MIN_FOOD) {
            searchFood(network);
        }


        if (_goBackToQueen && !backToQueen(network, true)) {
            break;
        }

        if (_nextMouvment.empty()) {
            _lastLook = look(network);
            std::cerr << "Searcher : " << _id << " Look: {\n";
            for (const auto &i: _lastLook) {
                std::cerr << "\t" << i << "\n";
            }
            std::cerr << "}\n";

            std::vector<int> priority = estimatePriority();

            whereShouldIGo(priority);
        }

        if (_nextMouvment.empty()) {
            if (_howManySameMove < NB_SAME_MOVE_MAX) {
                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
                _howManySameMove += 1;
            } else {
                _howManySameMove = 0;
                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
            }
            continue;
        }

        dumpMovement();

        Response rep = move(network);
        if (rep == Response::Ko) {
            _nextMouvment.clear();
            updateInventory(network);
            continue;
        } else if (rep == Response::Dead) {
            break;
        }

        if (_order.empty() && _nextMouvment.empty()) {
            _moveToStarter.emplace(_moveToStarter.begin(), Left);
            _moveToStarter.emplace(_moveToStarter.begin(), Left);
            _moveToStarter.emplace(_moveToStarter.begin(), Forward);
            _nextMouvment.clear();
            _nextMouvment = _moveToStarter;
            _goBackToQueen = true;
        }
        updateInventory(network);
    }
    std::cerr << "Searcher : " << _id << " is dead\n";
    return true;
}

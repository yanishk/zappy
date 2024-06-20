/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#include "Zappy.hpp"
#include "Broadcast.hpp"
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

void Zappy::Searcher::searchFood()
{
    std::vector<std::string> lookForFood = look();
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


Zappy::Response Zappy::Searcher::dropItem()
{
    std::unordered_map<std::string, int> ressource = _ressources.getRessources();

    std::cerr << "Give {\n";
    for (const auto &i: ressource) {

        if (i.first == FOOD) {
            continue;
        }

        for (int j = 0; j < i.second; ++j) {
            Zappy::Response rep = setObject(i.first);
            if (rep == Response::Dead) {
                return Response::Dead;
            } else if (rep == Response::Ko) {
                continue;
            }
            std::cerr << "\nSet " << i.first << "\n";
        }
    }
    std::cerr << "}\n";

    incantation();
    return Response::Ok;
}

bool Zappy::Searcher::runUntilLevelWanted()
{
    if (_order.empty()) {
        _order.setRessources(_order.getLevelRessources(_level));
    }
    if ((int)_level == _order.getLevel()) {
        return false;
    }

    if (_ressources.getRessource(FOOD) < MIN_FOOD) {
        searchFood();
    }

    if (_nextMouvment.empty()) {
        _lastLook = look();
        std::cout << "look {\n";
        for (const auto &i: _lastLook) {
            std::cout << "\t" + i << "\n";
        }
        std::cout << "}\n";

        std::vector<int> priority = estimatePriority();
        whereShouldIGo(priority);
        if (_nextMouvment.size() == 0 && _howManySameMove != NB_SAME_MOVE_MAX) {
            _nextMouvment.push_back(Left);
            _howManySameMove++;
        } else if (_howManySameMove == NB_SAME_MOVE_MAX) {
            _nextMouvment.push_back(Forward);
        }
        dumpMovement();
    }

    Response rep = move();
    if (rep == Response::Ko) {
        std::cout << "Unable to move\n";
    } else if (rep == Response::Dead) {
        std::cout << "Player is Dead\n";
        return false;
    }

    updateOrder();

    return true;
}

bool Zappy::Searcher::run()
{
    while (true) {

        if (_isGoingToBroadcast) {
            goToBroadcast();
            dropItem();
            std::stringstream myId;
            myId << std::this_thread::get_id();

            Broadcast broadcastHandler(_name, myId.str());

            broadcastHandler.letsIncantate(_network, _idToReach);

            _isGoingToBroadcast = false;
            continue;
        }

        if ((int)_level != _order.getLevel()) {

            _order.setRessources(_order.getLevelRessources(_level));
            if (runUntilLevelWanted()) {
                continue;
            }

        }

        if (_nextMouvment.empty() && !_order.empty()) {

            _lastLook = look();
            std::cerr << "look {\n";
            for (const auto &i: _lastLook) {
                std::cerr << "\t" + i << "\n";
            }
            std::cerr << "}\n";

            std::vector<int> priority = estimatePriority();

            whereShouldIGo(priority);

            if (_nextMouvment.size() == 0 && _howManySameMove != NB_SAME_MOVE_MAX) {

                _nextMouvment.push_back(Left);
                _howManySameMove++;

            } else if (_howManySameMove == NB_SAME_MOVE_MAX) {

                _nextMouvment.push_back(Forward);

            }
            dumpMovement();
        }

        Response rep = move();
        if (rep == Response::Ko) {
            std::cout << "Unable to move\n";
        } else if (rep == Response::Dead) {
            std::cout << "Player is Dead\n";
            break;
        }

        if (_ressources.getRessource(FOOD) < MIN_FOOD) {
            searchFood();
        }

        updateOrder();
        updateInventory();

    }

    return true;
}
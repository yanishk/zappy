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

    std::cerr << "Give {\n";
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
            std::cerr << "\nSet " << i.first << "\n";
        }
    }
    std::cerr << "}\n";

    return Response::Ok;
}

bool Zappy::Searcher::run(Network::Network &network)
{
    while (true) {

        if (_order.empty()) {
            dropItem(network);
            if (incantation(network) == Response::Ok) {
                _order.setRessources(_order.getLevelRessources(_level));
            }
        }

        if (_isGoingToBroadcast) {
            goToBroadcast(network);
            dropItem(network);

            _isGoingToBroadcast = false;
            continue;
        }

        if (_nextMouvment.empty() && !_order.empty()) {

            _lastLook = look(network);
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

        Response rep = move(network);

        if (rep == Response::Ko) {
            std::cout << "Unable to move\n";

            if (_nextMouvment.size() == 0 && _howManySameMove != NB_SAME_MOVE_MAX) {

                _nextMouvment.push_back(Left);
                _howManySameMove++;

            } else if (_howManySameMove == NB_SAME_MOVE_MAX) {

                _nextMouvment.push_back(Forward);

            }
            dumpMovement();

        } else if (rep == Response::Dead) {
            std::cout << "Player is Dead\n";
            break;
        }

        if (_order.empty()) {
            dropItem(network);
            incantation(network);
        }

        if (_ressources.getRessource(FOOD) < MIN_FOOD) {
            searchFood(network);
        }

        updateOrder();
        updateInventory(network);

    }

    return true;
}
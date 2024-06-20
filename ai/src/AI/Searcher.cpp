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

Zappy::Orientation Zappy::Searcher::checkAskingAssistant(Network::Network &network)
{
    int size = 0;

    for (auto &i: _messages) {
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

        if (otherId == QUEEN && _order.getLevel() == std::atoi(value.c_str()) - 1 && _order.empty()
        &&  message == ASK_ASSISTANT) {
            broadcastText(network, COMING + std::to_string(_id));
            return i.second;
        }
        size += 1;
    }

    return Orientation::UNDEFINED;
}

bool Zappy::Searcher::run(Network::Network &network)
{
    while (true) {

        Zappy::Orientation orientation = checkAskingAssistant(network);

        if (orientation != UNDEFINED && checkComingIsGood() && _order.empty()) {
            goToBroadcast(network);
            dropItem(network);
            _queenLevel = checkQueenLevel();
        }

        if (_order.empty() && orientation == UNDEFINED) {
            dropItem(network);
            if (incantation(network) == Response::Ok) {
                _order.setRessources(_order.getLevelRessources(_level));
            }
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

        if (_ressources.getRessource(FOOD) < MIN_FOOD) {
            searchFood(network);
        }

        updateOrder();
        updateInventory(network);

    }

    return true;
}

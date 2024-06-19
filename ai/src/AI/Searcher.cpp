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

bool Zappy::Searcher::haveIToTake(const std::string &item, std::unique_ptr<double> lastDensityObject)
{
    if (item == FOOD && _ressources.getRessource(FOOD) < MIN_FOOD) {
        return true;
    } else if (item == FOOD || item == PLAYER) {
        return false;
    }

    std::vector<double> density = {
        DERAUMERE_DENSITY,
        SIBUR_DENSITY,
        MENDIANE_DENSITY,
        PHIRAS_DENSITY,
        THYSTAME_DENSITY
    };

    for (const auto &i: density) {
        if (_order[item] > _ressources[item] && *lastDensityObject > density[i]) {
            *lastDensityObject = density[i];
            return true;
        }

    }

    return false;
}

std::vector<int> Zappy::Searcher::estimatePriority()
{
    std::vector <int> priority;
    double objectDensity(1.0);

    for (std::size_t i = 0; i < _lastLook.size(); ++i) {

        int itemPriority = 0;

        for (std::size_t j = 0; j < _lastLook.size(); ++j) {

            if (j == i) {
                continue;
            }

            if (_lastLook[i].find(" ")) {
                std::string temp(_lastLook[i]);
                while (temp.size()) {
                    std::string actualItem(temp, 0, temp.find(" "));

                    if (actualItem.size() == 0) {
                        break;
                    }

                    if (actualItem.size() == temp.size()) {
                        temp.erase(temp.begin(), temp.begin() + actualItem.size());
                    } else {
                        temp.erase(temp.begin(), temp.begin() + actualItem.size() + 1);
                    }
                    if (haveIToTake(actualItem, std::make_unique<double>(objectDensity)) &&
                       !haveIToTake(_lastLook[j], std::make_unique<double>(objectDensity))) {
                        _objectToTake.push_back(actualItem);
                        itemPriority++;
                    }

                }
            }

            if (haveIToTake(_lastLook[i], std::make_unique<double>(objectDensity)) &&
               !haveIToTake(_lastLook[j], std::make_unique<double>(objectDensity))) {
                _objectToTake.push_back(_lastLook[i]);
                itemPriority++;
            }

        }

        priority.push_back(itemPriority);

    }

    return priority;
}

void Zappy::Searcher::whereIsThePriority(int index)
{
    std::map<int, int> lookMap {
        {FIRST_LEVEL_RANGE},
        {SECOND_LEVEL_RANGE},
        {THISRT_LEVEL_RANGE},
        {FOURTH_LEVEL_RANGE},
        {FIVE_LEVEL_RANGE},
        {SIX_LEVEL_RANGE},
        {SEVEN_LEVEL_RANGE},
    };
    std::vector<int> sides {
        MIDDLE_FIRST_LEVEL,
        MIDDLE_SECOND_LEVEL,
        MIDDLE_THIRST_LEVEL,
        MIDDLE_FOURTH_LEVEL,
        MIDDLE_FIVE_LEVEL,
        MIDDLE_SIX_LEVEL,
        MIDDLE_SEVEN_LEVEL
    };

    int upper = 0;

    for (const auto &i: lookMap) {

        if (sides[upper] == index) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
        }

        if (index >= i.first && index <= i.second) {

            if (sides[upper] > index) {

                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
                for (int j = sides[upper]; j > index; --j) {
                    _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
                }

            }

            if (sides[upper] < index) {

                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
                _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Right);
                for (int j = sides[upper]; j < index; ++j) {
                    _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
                }

            }

        }

        upper++;
    }

    _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Take);

}

void Zappy::Searcher::whereShouldIGo(std::vector<int> priority)
{
    int biggestPriority = ERROR;
    int index = 0;
    int allValue = 0;

    for (const auto &i:priority) {
        allValue += i;

        if (i > biggestPriority) {
            biggestPriority = index;
        }

        if (i > biggestPriority && index == 0) {
            biggestPriority = 0;
            break;
        }
        index++;
    }

    if (biggestPriority == ERROR || allValue == 0) {
        return;
    }

    whereIsThePriority(biggestPriority);

    if (biggestPriority == 0) {
        return;
    }
    priority.erase(priority.begin() + biggestPriority);

    whereShouldIGo(priority);
}

void Zappy::Searcher::dumpMovement()
{
    std::cerr << "Mouvement {\n";

    for (const auto &i: _nextMouvment) {
        if (i == Zappy::Mouvement::Forward) {
            std::cerr << "\tForward,\n";
        }
        if (i == Zappy::Mouvement::Left) {
            std::cerr << "\tLeft,\n";
        }
        if (i == Zappy::Mouvement::Right) {
            std::cerr << "\tRight,\n";
        }
        if (i == Zappy::Mouvement::Back) {
            std::cerr << "\tBack,\n";
        }
        if (i == Zappy::Mouvement::Take) {
            std::cerr << "\tTake,\n";
        }
    }

    std::cerr << "}\n";
}

Zappy::Response Zappy::Searcher::move()
{
    Mouvement nextMove = _nextMouvment.back();
    Zappy::Response rep;
    std::string object;
    std::vector<std::string> temp;

    switch (nextMove) {
        case Forward:
            std::cerr << "Forward\n";
            rep = forward();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _nextMouvment.pop_back();
            _position.first -= 1;
            break;

        case Left:
            std::cerr << "Left\n";
            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _nextMouvment.pop_back();
            _position.second -= 1;
            break;

        case Right:
            std::cerr << "Right\n";
            rep = right();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            _nextMouvment.pop_back();
            _position.second += 1;
            break;

        case Back:
            std::cerr << "Back\n";
            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = forward();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            _nextMouvment.pop_back();
            _nextMouvment.pop_back();
            _nextMouvment.pop_back();
            _position.first += 1;
            break;

        case Take:

            object = _objectToTake.front();
            temp = look();
            std::cerr << "Look {\n";
            for (const auto &i: temp) {
                std::cerr << "\t" + i << "\n";
            }
            std::cerr << "}\n";
            if (takeObject(object) == Response::Ok) {
                std::cerr << "Take " << object << "\n";
                _order.removeRessources(object, 1);
            } else {
                return Response::Ko;
            }

            _objectToTake.erase(_objectToTake.begin());
            _nextMouvment.pop_back();
            updateOrder();
            break;

        default:
            break;
    }

    if (_order.empty()) {
        _nextMouvment.clear();
        _isGoingToQueen = true;
        std::cerr << "Go back to queen\n";
    }

    return Response::Ok;
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

void Zappy::Searcher::showMustGoOn()
{
    double x = _position.first;
    double y = _position.second;

    if (x < 0) {
        for (double i = 0; i > x; --i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
        }
    } else {
        _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Back);
        for (; x > 0; --x) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
        }
    }

    if (y < 0) {
        for (double i = 0; i > y; --i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Right);
        }
    } else {
        for (; y > 0; --y) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
        }
    }

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

    if (_nextMouvment.empty() && _isGoingToQueen) {
        showMustGoOn();
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

        if ((int)_level != _order.getLevel()) {
            _order.setRessources(_order.getLevelRessources(_level));
            if (runUntilLevelWanted()) {
                continue;
            }

        }

        if (_position == std::make_pair<double, double>(0.0, 0.0)
        &&  _isGoingToQueen == true) {

            if (dropItem() == Response::Dead) {
                break;
            }

        }

        if (_nextMouvment.empty() && !_isGoingToQueen) {
            _lastLook.clear();
        } else if (_nextMouvment.empty() && _isGoingToQueen) {
            showMustGoOn();
        }

        if (_nextMouvment.empty() && !_isGoingToQueen && _order.empty()) {
            _isGoingToQueen = true;
        } else if (_nextMouvment.empty() && !_isGoingToQueen && !_order.empty()) {

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
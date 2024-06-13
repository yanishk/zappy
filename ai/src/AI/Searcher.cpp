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
    } else if (item == FOOD) {
        return false;
    }

    std::vector<std::string> itemDesired = {
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };
    std::vector<RessourceType> itemType = {
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };
    std::vector<double> itemDensity = {
        DERAUMERE_DENSITY,
        SIBUR_DENSITY,
        MENDIANE_DENSITY,
        PHIRAS_DENSITY,
        THYSTAME_DENSITY
    };

    for (std::size_t i = 0; i < itemDesired.size() && i < itemType.size() && i < itemDensity.size(); ++i) {

        if (_order.getRessources().getAllValueRessources()[itemType[i]] > _ressources.getRessource(itemDesired[i])
         && *lastDensityObject > itemDensity[i]) {
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

            if (haveIToTake(_lastLook[i], std::make_unique<double>(objectDensity)) &&
               !haveIToTake(_lastLook[j], std::make_unique<double>(objectDensity))) {
                itemPriority++;
            }

        }

        priority.push_back(itemPriority);

    }

    return priority;
}

std::pair<int, int> Zappy::Searcher::whereIsThePriority(int index)
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

    std::pair<int, int> where(ERROR, ERROR);
    int upper = 0;

    for (const auto &i: lookMap) {

        if (index >= i.first && index <= i.second) {
            where.first = index + 1;
            if (sides[upper] > index) {
                int sidesGoing = 0;

                for (int j = sides[upper]; j > index; --j) {
                    sidesGoing -= 1;
                }

                where.second = sidesGoing;
            }

            if (sides[upper] < index) {
                int sidesGoing = 0;

                for (int j = sides[upper]; j < index; ++j) {
                    sidesGoing += 1;
                }

                where.second = sidesGoing;
            }

        }

        upper++;
    }

    return where;
}

void Zappy::Searcher::updateMove(std::pair<int, int> pos)
{
    if (pos == std::make_pair<int, int>(ERROR, ERROR)) {
        return;
    }

    if (pos.second < 0) {

        for (int i = 0; i > pos.second; --i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Left);
        }

    } else {
        for (int i = 0; i < pos.second; ++i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Right);
        }
    }

    for (int i = 0; i < pos.first; ++i) {
        _nextMouvment.emplace(_nextMouvment.begin(), Forward);
    }

    _nextMouvment.emplace(_nextMouvment.begin(), Take);
}

void Zappy::Searcher::whereShouldIGo(std::vector<int> priority)
{
    std::size_t biggestPriority = 0;
    int index = 0;

    for (const auto &i:priority) {

        if (i > (int)biggestPriority) {
            biggestPriority = index;
        }
        index++;
    }

    if (biggestPriority == 0) {
        return;
    }

    _objectToTake.push_back(_lastLook[biggestPriority]);

    std::pair<int, int> pos = whereIsThePriority(index);

    updateMove(pos);

    priority.erase(priority.begin() + biggestPriority);

    whereShouldIGo(priority);
}

void Zappy::Searcher::move()
{
    Mouvement nextMove = _nextMouvment.front();

    switch (nextMove) {
        case Forward:
            forward();
            _nextMouvment.erase(_nextMouvment.begin());
            break;

        case Left:
            left();
            _nextMouvment.erase(_nextMouvment.begin());
            break;

        case Right:
            right();
            _nextMouvment.erase(_nextMouvment.begin());
            break;

        case Back:
            left();
            left();
            forward();
            _nextMouvment.erase(_nextMouvment.begin());
            _nextMouvment.erase(_nextMouvment.begin());
            _nextMouvment.erase(_nextMouvment.begin());
            break;

        default:
            takeObject(_objectToTake.front());
            _objectToTake.erase(_objectToTake.begin());
            break;
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

    std::pair<int, int> pos = whereIsThePriority(priority);
    updateMove(pos);
}

void Zappy::Searcher::showMustGoOn()
{
    double x = _position.first;
    double y = _position.second;

    if (x < 0) {
        for (double i = 0; i > x; --i) {
            _nextMouvment.push_back(Forward);
        }
    } else {
        _nextMouvment.push_back(Back);
        for (; x > 0; --x) {
            _nextMouvment.push_back(Forward);
        }
    }

    if (y < 0) {
        for (double i = 0; i > y; --i) {
            _nextMouvment.push_back(Right);
        }
    } else {
        for (; y > 0; --y) {
            _nextMouvment.push_back(Left);
        }
    }

}

bool Zappy::Searcher::run()
{
    if (_network.getInfoFromServer() == "dead") {
        return false;
    }
    updateOrder();
    if (_nextMouvment.empty() && !_isGoingToQueen && _order.empty()) {
        _isGoingToQueen = true;
    } else if (_nextMouvment.empty() && !_isGoingToQueen && !_order.empty()) {
        _lastLook = look();
        auto priority = estimatePriority();
        whereShouldIGo(priority);
    }

    move();

    if (_ressources.getRessource(FOOD) < MIN_FOOD) {
        searchFood();
    }

    updateOrder();
    if (_nextMouvment.empty() && !_isGoingToQueen) {
        _lastLook.clear();
    } else if (_nextMouvment.empty() && _isGoingToQueen) {
        showMustGoOn();
    }

    return true;
}
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

    if (item == DERAUMERE &&
            _order.getRessources().getAllValueRessources()[Deraumere] > _ressources.getRessource(DERAUMERE)
            && *lastDensityObject > DERAUMERE_DENSITY) {
        return true;
    } else {
        return false;
    }

    if (item == SIBUR &&
            _order.getRessources().getAllValueRessources()[Sibur] > _ressources.getRessource(SIBUR)
            && *lastDensityObject > SIBUR_DENSITY) {
        return true;
    } else {
        return false;
    }

    if (item == MENDIANE &&
            _order.getRessources().getAllValueRessources()[Mendiane] > _ressources.getRessource(MENDIANE)
            && *lastDensityObject > MENDIANE_DENSITY) {
        return true;
    } else {
        return false;
    }

    if (item == PHIRAS &&
            _order.getRessources().getAllValueRessources()[Phiras] > _ressources.getRessource(PHIRAS)
            && *lastDensityObject > PHIRAS_DENSITY) {
        return true;
    } else {
        return false;
    }

    if (item == THYSTAME &&
            _order.getRessources().getAllValueRessources()[Thystame] > _ressources.getRessource(THYSTAME)
            && *lastDensityObject > THYSTAME_DENSITY) {
        return true;
    } else {
        return false;
    }

    return false;
}

std::vector<std::vector<bool>> Zappy::Searcher::estimatePriority()
{
    std::vector <std::vector<bool>> priority;
    double objectDensity(1.0);

    for (std::size_t i = 0; i < _lastLook.size(); ++i) {

        std::vector <bool> itemPriority;
        for (std::size_t j = 0; j < _lastLook.size(); ++j) {

            if (j == i) {
                continue;
            }

            if (haveIToTake(_lastLook[i], std::make_unique<double>(objectDensity)) &&
               !haveIToTake(_lastLook[j], std::make_unique<double>(objectDensity))) {
                itemPriority.push_back(haveIToTake(_lastLook[i], std::make_unique<double>(objectDensity)));
            }

        }

        priority.push_back(itemPriority);

    }
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

void Zappy::Searcher::whereShouldIGo(std::vector<std::vector<bool>> priority)
{
    std::size_t biggestPriority = 0;
    int index = 0;

    for (const auto &i:priority) {

        if (i.size() > biggestPriority) {
            biggestPriority = index;
        }
        index++;
    }
    std::pair<int, int> multiplicator = whereIsThePriority(index);

    if (multiplicator == std::make_pair<int, int>(ERROR, ERROR)) {
        return;
    }

    if (multiplicator.second < 0) {

        for (int i = 0; i > multiplicator.second; --i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Left);
        }

    } else {
        for (int i = 0; i < multiplicator.second; ++i) {
            _nextMouvment.emplace(_nextMouvment.begin(), Right);
        }
    }

    for (int i = 0; i < multiplicator.first; ++i) {
        _nextMouvment.emplace(_nextMouvment.begin(), Up);
    }

}

int Zappy::Searcher::run()
{
    updateOrder();
    if (_lastLook.empty()) {
        _lastLook = look();
    }

    auto priority = estimatePriority();
    whereShouldIGo(priority);

    updateOrder();
    if (_nextMouvment.empty()) {
        _lastLook.clear();
    }
    return EXIT_SUCCESS;
}

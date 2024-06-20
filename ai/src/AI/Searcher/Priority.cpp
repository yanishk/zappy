/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Priority
*/

#include "AI/Searcher.hpp"


std::vector<int> Zappy::Searcher::estimatePriority()
{
    std::vector <int> priority;

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

                    if (actualItem != FOOD && _order[actualItem] > 0) {
                        itemPriority++;
                    }

                }
            }

            if (_lastLook[i] != FOOD && _order[_lastLook[i]] > 0) {
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

}

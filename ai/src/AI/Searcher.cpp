/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

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

bool Zappy::Searcher::isPriority(const std::string &item)
{
    if (item == FOOD && _ressources.getRessource(FOOD) < MIN_FOOD) {
        return true;
    } else if (item == FOOD) {
        return false;
    }

}

void Zappy::Searcher::whereShouldIGo()
{

}

int Zappy::Searcher::run()
{
    updateOrder();
    if (_lastLook.empty()) {
        _lastLook = look();
    }



    updateOrder();
    return EXIT_SUCCESS;
}

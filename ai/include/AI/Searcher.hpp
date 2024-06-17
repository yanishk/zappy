/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#ifndef SEARCHER_HPP_
    #define SEARCHER_HPP_

    #define FIRST_LEVEL_RANGE       1, 3
    #define SECOND_LEVEL_RANGE      4, 8
    #define THISRT_LEVEL_RANGE      9, 15
    #define FOURTH_LEVEL_RANGE      16, 24
    #define FIVE_LEVEL_RANGE        25, 35
    #define SIX_LEVEL_RANGE         36, 48
    #define SEVEN_LEVEL_RANGE       49, 63

    #define MIDDLE_FIRST_LEVEL      2
    #define MIDDLE_SECOND_LEVEL     6
    #define MIDDLE_THIRST_LEVEL     12
    #define MIDDLE_FOURTH_LEVEL     20
    #define MIDDLE_FIVE_LEVEL       30
    #define MIDDLE_SIX_LEVEL        42
    #define MIDDLE_SEVEN_LEVEL      56

    #define NB_SAME_MOVE_MAX        4

    #define MIN_FOOD                10

    #include <map>
    #include "AAi.hpp"
    #include "Order.hpp"

namespace Zappy
{
    enum Mouvement{
        Forward,
        Left,
        Right,
        Back,
        Take
    };

    class Searcher : public AAi {
        public:
            Searcher(const std::string &port, const std::string &name, Order order):
                AAi(port, name),
                _order(order),
                _isGoingToQueen(false)
                {
                    _network.sendInformationToServer(_name);
                    if (_network.getInfoFromServer() == "none") {
                        return;
                    }
                    if (_network.getInfoFromServer() == "none") {
                        return;
                    }
                    _thread = std::thread(&Searcher::run, this);
                    _thread.join();
            };

            bool run();

            bool addOrder(Order order) {
                if (!_order.empty()) {
                    return false;
                }
                _order = order;
                return true;
            }

        private:
            Order _order;
            std::vector<std::string> _lastLook;
            std::vector<Mouvement> _nextMouvment;
            std::vector<std::string> _objectToTake;
            int _howManySameMove;
            bool _isGoingToQueen;
            std::thread _thread;


            Zappy::Response move();
            void printMovement();

            bool haveIToTake(const std::string &item, std::unique_ptr<double> lastDensityObject);
            void whereShouldIGo(std::vector<int> priority);

            std::vector<int> estimatePriority();
            void whereIsThePriority(int index);

            Zappy::Response dropItem();

            void updateOrder();
            void searchFood();
            void showMustGoOn();
    };

}

#endif /* !SEARCHER_HPP_ */
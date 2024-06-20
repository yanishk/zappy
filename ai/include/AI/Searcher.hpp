/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#ifndef SEARCHER_HPP_
    #define SEARCHER_HPP_

    #define SEARCHER_WELCOME "Searcher initialized.\n"

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
    #include <iostream>
    #include <thread>
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
            Searcher():
                AAi(),
                _order(Order(1, Ressources(1, 0, 0, 0, 0, 0))),
                _isGoingToBroadcast(false)
                {
                    static int id = 0;
                    _id = id++;

                }

            bool run(Network::Network &network);


        private:

            Order _order;
            std::vector<std::string> _lastLook;
            std::vector<Mouvement> _nextMouvment;
            int _howManySameMove;
            bool _isGoingToBroadcast;
            std::thread _thread;
            std::string _idToReach;
            int _id;

            Zappy::Response move(Network::Network &network);
            void dumpMovement();

            void goToBroadcast(Network::Network &network);

            void whereShouldIGo(std::vector<int> priority);

            std::vector<int> estimatePriority();
            void whereIsThePriority(int index);

            std::string takeThis(std::string tiled);
            Zappy::Response dropItem(Network::Network &network);

            void updateOrder();
            void searchFood(Network::Network &network);

    };

}

#endif /* !SEARCHER_HPP_ */
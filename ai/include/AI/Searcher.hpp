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

    #define MIN_FOOD 10

    #include <map>
    #include "AAi.hpp"
    #include "Order.hpp"

namespace Zappy
{
    enum Mouvement{
        Up,
        Left,
        Right,
        Back,
        Take
    };

    class Searcher : public AAi {
        public:
            Searcher(const std::string &port, Order order): AAi(port, INITIALIZE_MODE), _order(order) {};

            int run();

        protected:

            Network::Network _network;
            Ressources _ressources;

            std::pair<double, double> _position;
            Orientation _orientation;
            std::size_t _level;

        private:
            Order _order;
            std::vector<std::string> _lastLook;
            std::vector<Mouvement> _nextMouvment;
            std::vector<std::string> _objectToTake;

            void move();

            bool haveIToTake(const std::string &item, std::unique_ptr<double> lastDensityObject);
            void whereShouldIGo(std::vector<std::vector<bool>> priority);
            void updateMove(std::pair<int, int> pos);

            std::vector<std::vector<bool>> estimatePriority();
            std::pair<int, int> whereIsThePriority(int index);

            void updateOrder();
            void searchFood();
    };

}

#endif /* !SEARCHER_HPP_ */

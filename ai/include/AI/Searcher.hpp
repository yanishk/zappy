/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#ifndef SEARCHER_HPP_
    #define SEARCHER_HPP_

    #define MIN_FOOD 20

    #include <map>
    #include "AAi.hpp"
    #include "Order.hpp"

namespace Zappy
{
    enum Mouvement{
        Up,
        Left,
        Right,
        Back
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
            std::vector <Mouvement> _nextMouvment;

            void updateOrder();
            bool isPriority(const std::string &item);
            void whereShouldIGo();

    };

}

#endif /* !SEARCHER_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#ifndef QUENTIN_HPP_
    #define QUENTIN_HPP_

    #define INFINY 10000

    #define QUENTIN_WELCOME(x) "Quentin " << x << " welcome.\n"
    #define QUENTIN_DEAD(x) "Quentin " << x << " is dead.\n"
    #define QUENTIN_FORK(x) "Quentin " << x << " fork.\n"
    #define QUENTIN_DROP(x) "Quentin " << x << " drop food.\n"

    #define LAST_FOOD 1
    #define ONE_COUNT 1

    #include "AAi.hpp"

namespace Zappy {

    class Quentin : public AAi {

        public:

            Quentin(): AAi() {

                static int id = 0;

                _id = id++;

            };

            bool run(Network::Network &network);

        private:

            bool forkQuentin(Network::Network &network);

            std::size_t _id;

    };

};

#endif /* !QUENTIN_HPP_ */
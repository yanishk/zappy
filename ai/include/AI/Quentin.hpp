/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#ifndef QUENTIN_HPP_
    #define QUENTIN_HPP_

    #define LAST_FOOD 1
    #define LAST_REFILL 1

    #include "AAi.hpp"

namespace Zappy {

    class Quentin : public AAi {

        public:

            Quentin(const std::string &port, const size_t nbRefills): AAi(port), _nbRefills(nbRefills) {};

            int run();

        private:

            bool executeAction();

            size_t _nbRefills;
            std::vector<Action> _actions;

    };

};

#endif /* !QUENTIN_HPP_ */

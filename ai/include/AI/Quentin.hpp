/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#ifndef QUENTIN_HPP_
    #define QUENTIN_HPP_

    #define LAST_FOOD 1
    #define ZERO_REFILL 0

    #define FORK_WAIT 42
    #define DROP_WAIT 7

    #include "AAi.hpp"

namespace Zappy {

    class Quentin : public AAi {

        public:

            Quentin(const std::string &port, const size_t nbRefills, const std::string &name): AAi(port, name), _nbRefills(nbRefills) {
                _network.sendInformationToServer(_name);
                _network.getInfoFromServer();
                _network.getInfoFromServer();
            };

            int run();

        private:

            bool executeAction();
            bool createQuentin();

            size_t _nbRefills;
            std::vector<Action> _actions;

    };

};

#endif /* !QUENTIN_HPP_ */
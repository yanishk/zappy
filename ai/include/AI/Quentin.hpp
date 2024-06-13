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

            Quentin(const std::string &port, const std::string &name, const size_t nbRefills): AAi(port, name), _nbRefills(nbRefills) {
                std::cout << "Quentin init\n";
                _network.sendInformationToServer(_name);
                if (_network.getInfoFromServer() == RESPONSE_KO) {
                    std::cout << "a non\n";
                    return;
                }
                _network.getInfoFromServer();
                _thread = std::thread(&Quentin::run, this);
            };

            ~Quentin() {
                _thread.join();
            }

            bool run();

        private:

            bool executeAction();
            bool createQuentin();

            size_t _nbRefills;
            std::vector<Action> _actions;
            std::thread _thread;

    };

};

#endif /* !QUENTIN_HPP_ */
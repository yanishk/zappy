/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

namespace Zappy {
    
    class Queen : public AAi {

        public:

            Queen(const std::string &port, const std::string &name): AAi(port, name) {
                std::cout << "Queen initialized\n";
                _network.sendInformationToServer(_name);
                if (_network.getInfoFromServer() == RESPONSE_KO) {
                    return;
                }
                _network.getInfoFromServer();
                _thread = std::thread(&Queen::run, this);
                _thread.join();
            };

            bool run();

        private:

            bool initialize();
            std::thread _thread;
    };

};

#endif /* !SEARCHERAI_HPP_ */

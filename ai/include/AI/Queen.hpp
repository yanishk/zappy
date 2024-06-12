/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define INITIALIZE_MODE 0
    #define FIRST_LEVEL 1

namespace Zappy {
    
    class Queen : public AAi {

        public:

            Queen(const std::string &port, const std::string &name): AAi(port, name, INITIALIZE_MODE) {
                _network.sendInformationToServer(_name);
                _network.getInfoFromServer();
                _network.getInfoFromServer();
            };

            int run();

        private:

            bool initialize();

    };

};

#endif /* !SEARCHERAI_HPP_ */

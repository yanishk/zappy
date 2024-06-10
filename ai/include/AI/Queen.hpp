/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define FIRST_LEVEL 1

namespace Zappy {
    
    class Queen : public AAi {

        public:

            Queen(const std::string &port, const std::string &name): AAi(port, INITIALIZE_MODE), _isConnected(true) ,_name(name) {
                if (_network.getInfoFromServer() != WELCOME) {
                    _isConnected = false;
                }
                _network.sendInformationToServer(name);
                std::string mapSize = _network.getInfoFromServer();
                _mapSize.first = std::atoi(mapSize.c_str());
                mapSize.erase(mapSize.begin(), mapSize.begin() + 3);
                _mapSize.second = std::atoi(mapSize.c_str());
            };

            int run();

        private:

            bool _isConnected;
            std::string _name;
            bool initialize();
            std::pair<int, int> _mapSize;
    };

};

#endif /* !SEARCHERAI_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define WELCOME_QUEEN "Queen initialized\n"

    #define CRITICAL_FOOD 10
    #define CRITICAL_STOCK 20

    #define ONE_FOOD 1

    #define NONE 0
    #define HERE 0

namespace Zappy {
    
    class Queen : public AAi {

        using Ressources = std::vector<std::string>;

        enum Action {

            Look,
            TakeFood,
            ForkFood,
            ForkSearcher,
            Incantation

        };

        

        enum RessourceType {
            Food,
            Linemate,
            Deraumere,
            Sibur,
            Mendiane,
            Phiras,
            Thystame
        };



        public:

            Queen(const std::string &port, const std::string &name): AAi(port, name) {

                std::cout << WELCOME_QUEEN;

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

            bool checkFood();
            bool checkIncantation();
            bool execute();

            std::size_t countRessources(const std::string &ressources, const std::string &index);

            Ressources _look;

            std::size_t _stock;
            std::thread _thread;
            std::vector<Action> _actions;

            std::vector<std::pair<size_t, Zappy::Ressources>> _incatation = {
                { 1, Zappy::Ressources(1, 0, 0, 0, 0, 0) }
            };

    };

};

#endif /* !SEARCHERAI_HPP_ */

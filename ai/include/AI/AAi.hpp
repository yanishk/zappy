/*
** EPITECH PROJECT, 2024
** ai
** File description:
** AAi
*/

#ifndef AAI_HPP_
    #define AAI_HPP_

    #include <utility>

    #include "IAi.hpp"
    #include "Network.hpp"
    #include "Ressources.hpp"

    #define START_POSITION {0, 0}
    #define START_LEVEL 1
    #define START_WAIT 0

namespace Zappy {

    enum Orientation {
        NORTH,
        SOUTH,
        WEST,
        EST
    };

    enum Action {
        Look,
        Eat,
        Drop,
        Elevation,
        Fork
    };

    class AAi : public IAi {

        public:

            AAi(const std::string &port, const std::size_t level = START_LEVEL): 
                _network(Network::Network(port)),
                _ressources(Ressources()),
                _position(START_POSITION),
                _level(level),
                _wait(START_WAIT)
            {};

            virtual int run() = 0;

            bool forward();
            bool right();
            bool left();

            std::vector<std::string> look();
            bool inventory();
            bool broadcastText(const std::string &text);

            std::size_t connectNumber();
            bool fork();
            bool eject();

            bool takeObject(const std::string &object);
            bool setObject(const std::string &object);
            bool incantation();

            std::size_t countObject(const std::string &objects, const std::string &type);
    
        protected:


            Network::Network _network;
            Ressources _ressources;

            std::pair<double, double> _position;
            Orientation _orientation;
            std::size_t _level;

            std::size_t _wait;

        private:
            std::size_t countMember(const std::string &line) const;
            bool checkRessources(const std::vector<std::string> &newRessources);

    };

};

#endif /* !AAI_HPP_ */

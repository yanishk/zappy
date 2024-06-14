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

    #define INITIALIZE_MODE 0
    #define START_POSITION {0.0, 0.0}
    #define START_LEVEL 1
    #define START_WAIT 0

    #define FORWARD_CMD "Forward\n"
    #define RIGHT_CMD "Right\n"
    #define LEFT_CMD "Left\n"
    #define LOOK_CMD "Look\n"
    #define INVENTORY_CMD "Inventory\n"
    #define BROADCAST_CMD "Broadcast "
    #define CONNECT_NBR_CMD "Connect_nbr\n"
    #define FORK_CMD "Fork\n"
    #define EJECT_CMD "Eject\n"
    #define TAKE_CMD "Take "
    #define SET_CMD "Set "
    #define INCANTATION_CMD "Incantation\n"

    #define RESPONSE_OK "ok"
    #define RESPONSE_KO "ko"

    #define ERROR -1
    #define DEAD "dead"

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

            AAi(const std::string &port, const std::string &name): 
                _network(Network::Network(port)),
                _ressources(Ressources()),
                _position(START_POSITION),
                _level(START_LEVEL),
                _name(name)
            {};

            virtual bool run() = 0;

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

        protected:

            Network::Network _network;
            Ressources _ressources;

            std::pair<double, double> _position;
            Orientation _orientation;
            std::size_t _level;

            std::string _name;

        private:
            std::size_t countMember(const std::string &line) const;
            bool checkRessources(const std::vector<std::string> &newRessources);

    };

};

#endif /* !AAI_HPP_ */

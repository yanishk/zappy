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
    #define START 0

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

    #define ELEVATION_UNDERWAY "Elevation underway"
    #define PREFIX_LEVEL "Current level:"
    #define RESPONSE_OK "ok"
    #define RESPONSE_KO "ko"
    #define MESSAGE "message"
    #define MESSAGE_LEN 7

    #define ERROR -1
    #define DEAD "dead"

namespace Zappy {

    enum Action {
        Look,
        Eat,
        Drop,
        Elevation,
        Fork
    };

    class AAi : public IAi {

        public:

            AAi():
                _ressources(Ressources()),
                _position(START_POSITION),
                _level(START_LEVEL)
            {};

            virtual bool run(Network::Network &network) = 0;

            Response forward(Network::Network &network);
            Response right(Network::Network &network);
            Response left(Network::Network &network);

            std::vector<std::string> look(Network::Network &network);
            std::vector<std::string> inventory(Network::Network &network);
            bool updateInventory(Network::Network &network);

            Response broadcastText(Network::Network &network, const std::string &text);
            std::string handlingMessage(Network::Network &network);

            std::size_t connectNumber(Network::Network &network);
            Response fork(Network::Network &network);
            Response eject(Network::Network &network);

            Response takeObject(Network::Network &network, const std::string &object);
            Response setObject(Network::Network &network, const std::string &object);
            Response incantation(Network::Network &network);

            Orientation getOrientation(int value);

        protected:

            Ressources _ressources;

            std::pair<double, double> _position;
            std::size_t _level;

            std::vector<std::pair<std::string, Orientation>> _messages;

    };

};

#endif /* !AAI_HPP_ */

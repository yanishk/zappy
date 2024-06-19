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
        FRONT = 1,
        FRONT_LEFT,
        LEFT,
        BACK_LEFT,
        BACK,
        BACK_RIGHT,
        RIGHT,
        FRONT_RIGHT,
        UNDEFINED
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
                _isIncantation(false),
                _network(Network::Network(port)),
                _ressources(Ressources()),
                _position(START_POSITION),
                _level(START_LEVEL),
                _name(name)
            {};

            virtual bool run() = 0;

            Response forward();
            Response right();
            Response left();

            std::vector<std::string> look();
            bool inventory();
            Response broadcastText(const std::string &text);

            std::string handlingMessage();

            std::size_t connectNumber();
            Response fork();
            Response eject();

            Response takeObject(const std::string &object);
            Response setObject(const std::string &object);
            Response incantation();

            std::pair<double, double> getPosition() const { return _position; };

            std::size_t getLevel() const { return _level; };
            void setLevel(std::size_t level) { _level = level; };

            bool getIsIncantation() const { return _isIncantation; };
            void setIsIncantation(bool isIncantation) { _isIncantation = isIncantation; };

        protected:

            bool _isIncantation;

            Network::Network _network;
            Ressources _ressources;

            std::pair<double, double> _position;
            Orientation _orientation;
            std::size_t _level;

            std::string _name;

            std::string _message;

        private:

            Orientation getOrientation(int value);
            bool checkRessources(const std::vector<std::string> &newRessources);

    };

};

#endif /* !AAI_HPP_ */

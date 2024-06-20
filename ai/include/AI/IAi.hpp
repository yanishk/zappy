/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ai
*/

#ifndef IAI_HPP_
    #define IAI_HPP_

    #include <vector>
    #include <string>

    #include "Network.hpp"

namespace Zappy {

    enum Orientation {
        IN_CASE,
        FRONT,
        FRONT_LEFT,
        LEFT,
        BACK_LEFT,
        BACK,
        BACK_RIGHT,
        RIGHT,
        FRONT_RIGHT,
        UNDEFINED
    };

    enum Response {
        Ok,
        Ko,
        Dead
    };

    class IAi {

        public:

            IAi() = default;

            virtual bool run(Network::Network &network) = 0;

            virtual Response forward(Network::Network &network) = 0;
            virtual Response right(Network::Network &network) = 0;
            virtual Response left(Network::Network &network) = 0;

            virtual std::vector<std::string> look(Network::Network &network) = 0;
            virtual std::vector<std::string> inventory(Network::Network &network) = 0;
            virtual bool updateInventory(Network::Network &network) = 0;

            virtual Response broadcastText(Network::Network &network, const std::string &text) = 0;
            virtual std::string handlingMessage(Network::Network &network) = 0;

            virtual std::size_t connectNumber(Network::Network &network) = 0;
            virtual Response fork(Network::Network &network) = 0;
            virtual Response eject(Network::Network &network) = 0;

            virtual Response takeObject(Network::Network &network, const std::string &object) = 0;
            virtual Response setObject(Network::Network &network, const std::string &object) = 0;
            virtual Response incantation(Network::Network &network) = 0;

            virtual Orientation getOrientation(int value) = 0;

    };

};

#endif /* !IAI_HPP_ */

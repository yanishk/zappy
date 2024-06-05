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

namespace Zappy {

    class AAi : public IAi {

        public:

            AAi(const std::string &port, const std::size_t level = START_LEVEL): 
                _network(Network::Network(port)),
                _ressources(Ressources()),
                _position(START_POSITION),
                _level(level)
            {};

            virtual int run() = 0;

            bool forward() const;
            bool right() const;
            bool left() const;

            std::vector<std::string> look() const;
            std::vector<std::string> inventory() const;
            bool broadcastText() const;

            std::size_t connectNumber() const;
            bool fork() const;
            bool eject() const;

            bool takeObject() const;
            bool setObject() const;
            bool incantation() const;

        protected:

            Network::Network _network;
            Ressources _ressources;

            std::pair<std::size_t, std::size_t> _position;
            std::size_t _level;

    };

};

#endif /* !AAI_HPP_ */

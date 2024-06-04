/*
** EPITECH PROJECT, 2024
** ai
** File description:
** AAi
*/

#ifndef AAI_HPP_
    #define AAI_HPP_

    #define LOOK "look\n"

    #include <vector>

    #include "IAi.hpp"
    #include "Network.hpp"
    #include "Ressources.hpp"

namespace Zappy {

    class AAi : public IAi {

        public:

            AAi() = default;

            virtual bool run() = 0;

            virtual bool forward() const = 0;
            virtual bool right() const = 0;
            virtual bool left() const = 0;

            virtual std::vector<std::string> look() const = 0;
            virtual std::vector<std::string> inventory() const = 0;
            virtual bool broadcastText() const = 0;

            virtual size_t connectNumber() const = 0;
            virtual bool fork() const = 0;
            virtual bool eject() const = 0;

            virtual bool takeObject() const = 0;
            virtual bool setObject() const = 0;
            virtual bool incantation() const = 0;

    };

};

#endif /* !AAI_HPP_ */

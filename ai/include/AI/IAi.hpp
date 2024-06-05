/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ai
*/

#ifndef IAI_HPP_
    #define IAI_HPP_

    #define LOOK "look\n"

    #include <vector>
    #include <string>

namespace Zappy {

    class IAi {

        public:

            IAi() = default;

            virtual int run() = 0;

            virtual bool forward() const = 0;
            virtual bool right() const = 0;
            virtual bool left() const = 0;

            virtual std::vector<std::string> look() const = 0;
            virtual std::vector<std::string> inventory() const = 0;
            virtual bool broadcastText() const = 0;

            virtual std::size_t connectNumber() const = 0;
            virtual bool fork() const = 0;
            virtual bool eject() const = 0;

            virtual bool takeObject() const = 0;
            virtual bool setObject() const = 0;
            virtual bool incantation() const = 0;

    };

};

#endif /* !IAI_HPP_ */

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

            virtual bool forward() = 0;
            virtual bool right() = 0;
            virtual bool left() = 0;

            virtual std::vector<std::string> look() = 0;
            virtual bool inventory() = 0;
            virtual bool broadcastText(const std::string &text) = 0;

            virtual std::size_t connectNumber() = 0;
            virtual bool fork() = 0;
            virtual bool eject() = 0;

            virtual bool takeObject(const std::string &object) = 0;
            virtual bool setObject(const std::string &object) = 0;
            virtual bool incantation() = 0;

            virtual std::size_t countObject(const std::string &objects, const std::string &type) = 0;

    };

};

#endif /* !IAI_HPP_ */

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

    enum Response {
        Ok,
        Ko,
        Dead
    };

    class IAi {

        public:

            IAi() = default;

            virtual bool run() = 0;

            virtual Response forward() = 0;
            virtual Response right() = 0;
            virtual Response left() = 0;

            virtual std::vector<std::string> look() = 0;
            virtual bool inventory() = 0;
            virtual Response broadcastText(const std::string &text) = 0;

            virtual std::size_t connectNumber() = 0;
            virtual Response fork() = 0;
            virtual Response eject() = 0;

            virtual Response takeObject(const std::string &object) = 0;
            virtual Response setObject(const std::string &object) = 0;
            virtual Response incantation() = 0;

    };

};

#endif /* !IAI_HPP_ */

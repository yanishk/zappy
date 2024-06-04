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
    #include "Network.hpp"
    #include "Ressources.hpp"

namespace Zappy
{

    class IAi {

        public:
            IAi() {}

            virtual std::vector<std::string> look() const;

    };

}

#endif /* !IAI_HPP_ */

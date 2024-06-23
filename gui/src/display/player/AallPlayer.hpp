/*
** EPITECH PROJECT, 2024
** Abstract Class Player
** File description:
** zappy Proj
*/

#ifndef AALLPLAYER_HPP_
    #define AALLPLAYER_HPP_

    #include "AllObj.hpp"
    #include "raylib.h"

namespace Zappy {

    class AAllPlayerObj : public IAllObj {

        public:

            AAllPlayerObj() = default;
            virtual ~AAllPlayerObj() = default;

            virtual void renderAllElements(Vector3 vec) = 0;
            using IAllObj::renderAllElements;
    };
}

#endif /* !AALLPLAYER_HPP_ */

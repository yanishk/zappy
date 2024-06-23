/*
** EPITECH PROJECT, 2024
** sky obj Class
** File description:
** zappy Proj
*/

#ifndef SKY_HPP_
    #define SKY_HPP_

    #include <string>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>
    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"
    #include "Utils.hpp"
    #define SKY_SIZE 10

    #include "Render.hpp"

namespace Zappy {

    class Sky : public ILoadAndRenderObj {

        public:

            void render() override;
            void setModel(std::pair<Model, float> model) override;
            void setSkyPos(Vector3 pos);

        private:

            Model _skyModel;
            Vector3 _skyPosition;
            float _skySize;

    };
}

#endif /* !SKY_HPP_ */
/*
** EPITECH PROJECT, 2024
** zappy_gui_try2
** File description:
** Island
*/

#ifndef ISLAND_HPP_
    #define ISLAND_HPP_

    #include <string>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>
    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"

    #include "Render.hpp"
    #include "Commands.hpp"

    #define ISLAND_ALTITUDE -4

namespace Zappy {

    class Island : public ILoadAndRenderObj {

        public:

            void render() override;
            void setModel(std::pair<Model, float> model) override;
            void setIslandPos(Vector3 pos);

        private:

            Model _islandModel;
            Vector3 _islandPosition;
            float _islandSize;
    };
}

#endif /* !ISLAND_HPP_ */

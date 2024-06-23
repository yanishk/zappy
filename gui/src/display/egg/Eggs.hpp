/*
** EPITECH PROJECT, 2024
** Eggs Class
** File description:
** zappy proj
*/

#ifndef EGGS_HPP_
    #define EGGS_HPP_
    #include <string>
    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include <map>
    #include "Utils.hpp"
    #include "Render.hpp"
    #include "Commands.hpp"

    #define ROTATE_RAND_RANGE (210 - 159 + 1) + 159
    #define DEFAULT_EGG_INCLIN 80

namespace Zappy {

    class Egg : public ILoadAndRenderObj {

        public:

            void render() override;
            void setModel(std::pair<Model, float> model) override;
            void setEggPosAndID(Vector2 pos, int eggId);

            int getEggId();
            Vector2 getEggRealPos();
            Vector3 get3DEggPos();

        private:

            Vector2 _eggRealPos;
            Vector3 _egg3DPosition;
            Model _eggModel;

            float _eggHight;
            float _eggSize;

            int _eggID;
    };
}

#endif /* !EGGS_HPP_ */

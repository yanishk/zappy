/*
** EPITECH PROJECT, 2024
** Sea Class
** File description:
** Zappy proj
*/

#ifndef SEA_HPP_
    #define SEA_HPP_

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
    #include "Render.hpp"
    #define SEA_SIZE 1000
    #define SEA_RESXZ 2
    #define SEA_ALTITUDE -2
    #define SUB_SEA_ALTITUDE -2.3
    #define SEA_TEXTURE "./gui/assets/image/water_texture.png"
    #define SEA_SHADER "./gui/assets/shaders/water.fs"
    #define SHADER_FORMAT 330
    #define SHADER_SECONDS "seconds"
    #define SHADER_FREQX "freqX"
    #define SHADER_FREQY "freqY"
    #define SHADER_AMPX "ampX"
    #define SHADER_AMPY "ampY"
    #define SHADER_SPEEDX "speedX"
    #define SHADER_SPEEDY "speedY"
    #define SHADER_SIZE "size"

    #define VALUE_SHADER_FREQX 25.0
    #define VALUE_SHADER_FREQY 25.0
    #define VALUE_SHADER_AMPX 5.0
    #define VALUE_SHADER_AMPY 5.0
    #define VALUE_SHADER_SPEEDY 8.0
    #define VALUE_SHADER_SPEEDX 8.0

namespace Zappy {

    class Sea : public ILoadAndRenderObj {

        public:

            Sea();

            void render() override;
            void setModel(std::pair<Model, float>) override;
            void setSeaPos(Vector3 pos, std::pair<int, int> mapSize);

        private:

            Model _seaModel;
            Shader _seaShader;

            Vector3 _subSeaPosition;
            Vector3 _seaPosition;

            float _seaSize;
            float _seconds;

            int _seaSecondLoc;
    };
}

#endif /* !SEA_HPP_ */
